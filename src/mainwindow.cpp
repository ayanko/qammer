#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QList>
#include <QMovie>
#include <QSettings>

#include "client.h"
#include "logindialog.h"
#include "messagewidget.h"
#include "message.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->createTrayActions();
    this->createTrayMenu();
    this->createTrayIcon();

    connect(m_pTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));

    m_pTrayIcon->show();

    createLoginDialog();
    connect(m_pLoginDialog, SIGNAL(loggedIn()), this, SLOT(loggedIn()));

    m_pClient = new Client(this);
    connect(m_pClient, SIGNAL(messagesReceived()), this, SLOT(updateMessageList()));
    connect(m_pClient, SIGNAL(messagesReceived()), this, SLOT(popupMessages()));

    m_pTimer = new QTimer(this);
    m_pTimer->start(60000);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(timeOut()));
    timeOut();

    QMovie *movie = new QMovie(":images/spinner.gif");
    ui->labelSpinner->setMovie(movie);
    movie->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createTrayActions()
{
    m_pToggleAction = new QAction(tr("&Toggle"), this);
    m_pQuitAction = new QAction(tr("&Quit"), this);

    connect(m_pToggleAction, SIGNAL(triggered()), this, SLOT(toggle()));
    connect(m_pQuitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MainWindow::createTrayMenu()
{
    m_pTrayMenu = new QMenu(this);
    m_pTrayMenu->addAction(m_pToggleAction);
    m_pTrayMenu->addSeparator();
    m_pTrayMenu->addAction(m_pQuitAction);
}

void MainWindow::createTrayIcon()
{
    m_pTrayIcon = new QSystemTrayIcon(this);

    m_pTrayIcon->setIcon(QIcon(":/images/yammer_logo.png"));
    m_pTrayIcon->setContextMenu(m_pTrayMenu);
}

void MainWindow::toggle() {
    this->isHidden() ? this->show() : this->hide();
}

void MainWindow::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger) this->toggle();
    m_pTrayIcon->setIcon(QIcon(":/images/yammer_logo.png"));
}

void MainWindow::createLoginDialog()
{
    m_pLoginDialog = new LoginDialog(this);
}

void MainWindow::login()
{
    m_pLoginDialog->show();
    m_pLoginDialog->login();
}

void MainWindow::loggedIn()
{
    m_pTrayIcon->showMessage(tr("Congrats!"), tr("Successfully logged into Yammer!"));
}

void MainWindow::on_pushButton_clicked()
{
    timeOut();
}

void MainWindow::updateMessageList()
{
    ui->listWidgetMessages->clear();

    foreach(Message* message, m_pClient->messages()) {
        QString title;
        title.append("<b>");
        title.append(QString::number(message->senderId()));
        title.append("</b>");
        title.append(" id(");
        title.append(QString::number(message->id()));
        title.append(")");
        title.append(" thread(");
        title.append(QString::number(message->threadId()));
        title.append(")");

        QString status;
        status.append("<i>");
        status.append(message->createdAt());
        status.append("</i>");

        MessageWidget* messageWidget = new MessageWidget(this);
        messageWidget->setTitle(title);
        messageWidget->setContent(message->bodyRich());
        messageWidget->setStatus(status);

        if(!message->children().empty()) {
            foreach(Message* child, message->children()) {
                MessageWidget* messageChildWidget = new MessageWidget(messageWidget);
                //messageChildWidget->setTitle(title);
                messageChildWidget->setContent(child->bodyRich());
                //messageChildWidget->setStatus(status);
                messageChildWidget->adjustSize();
                messageWidget->addChild(messageChildWidget);
            }
            messageWidget->showChildren();
        }
        messageWidget->adjustSize();

        QListWidgetItem* item = new QListWidgetItem(ui->listWidgetMessages);
        ui->listWidgetMessages->setItemWidget(item, messageWidget);
        item->setSizeHint(messageWidget->size());
    }
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::popupMessages()
{
    QSettings settings;
    qint32 last_message_id = settings.value("last_message_id").toInt();

    Message* message = m_pClient->messages().first();
    if (message->id() > last_message_id) {
        m_pTrayIcon->setIcon(QIcon(":/images/yammer_notify.png"));
        m_pTrayIcon->showMessage(message->createdAt(), message->bodyPlain());
        settings.setValue("last_message_id", QString::number(message->id()));
    }
}

void MainWindow::timeOut()
{
      ui->stackedWidget->setCurrentIndex(0);
      m_pClient->fetchMessages();
}
