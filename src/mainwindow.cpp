#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QList>
#include <QMovie>
#include <QSettings>
#include <QLayoutItem>

#include "client.h"
#include "logindialog.h"
#include "messagewidget.h"
#include "message.h"
#include "user.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButtonUpdateMessages->hide();
    ui->scrollArea->setBackgroundRole(QPalette::Base);

    m_IconNormal.addFile(":/images/yammer_logo.png");

    this->createTrayActions();
    this->createTrayMenu();
    this->createTrayIcon();

    connect(m_pTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));
    connect(m_pTrayIcon, SIGNAL(messageClicked()),
            this, SLOT(updateMessageList()));
    connect(m_pTrayIcon, SIGNAL(messageClicked()), this, SLOT(show()));

    m_pTrayIcon->show();

    createLoginDialog();
    connect(m_pLoginDialog, SIGNAL(loggedIn()), this, SLOT(loggedIn()));

    m_pClient = new Client(this);
    connect(m_pClient, SIGNAL(messagesReceived()), this, SLOT(popupMessages()));
    connect(m_pClient, SIGNAL(usersReceived()), this, SLOT(timeOut()));

    m_pTimer = new QTimer(this);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(timeOut()));

    m_pTimer->setInterval(30000);
    m_pTimer->start();

    m_pTrayIconTimer = new QTimer(this);
    connect(m_pTrayIconTimer, SIGNAL(timeout()), this, SLOT(trayIconTimeOut()));
    m_pTrayIconTimer->setInterval(500);

    //QMovie *movie = new QMovie(":images/spinner.gif");
    //ui->labelSpinner->setMovie(movie);
    //movie->start();

    restoreSettings();
    ui->stackedWidget->setCurrentIndex(1);

    statusBar()->showMessage(tr("Prefetching ..."));
    m_pClient->fetchUsers();
    m_pClient->fetchGroups();
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
    m_pTrayIcon->setIcon(m_IconNormal);
    m_pTrayIcon->setContextMenu(m_pTrayMenu);
}

void MainWindow::toggle() {
    this->isHidden() ? this->show() : this->hide();
}

void MainWindow::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger ||
        reason == QSystemTrayIcon::DoubleClick) {
        this->toggle();
    }
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

void MainWindow::clearMessageWidgets()
{
    QLayoutItem* item;
    while(( item = ui->verticalLayout->takeAt(0)) != 0)
    {
        delete item->widget();
        delete item;
    }
}

void MainWindow::updateMessageList()
{
    ui->pushButtonUpdateMessages->hide();
    stopTrayIconBlinking();

    statusBar()->showMessage(tr("Updating ..."));
    clearMessageWidgets();

    foreach(Message* message, m_pClient->messages()) {
        MessageWidget* messageWidget = new MessageWidget(this);
        messageWidget->setMessage(message);

        if(!message->children().empty()) {
           QListIterator<Message*> i(message->children());
           i.toBack();
           while (i.hasPrevious()) {
              Message* child = i.previous();
              MessageWidget* messageChildWidget = new MessageWidget(messageWidget);
              messageChildWidget->setMessage(child);
              messageChildWidget->adjustSize();
              messageWidget->addChild(messageChildWidget);
           }
        }

        ui->verticalLayout->addWidget(messageWidget);
    }

    statusBar()->clearMessage();
}

void MainWindow::popupMessages()
{
    QSettings settings;
    qint32 last_message_id = settings.value("last_message_id").toInt();

    statusBar()->clearMessage();

    Message* message = m_pClient->recentMessage();
    if (message && message->id() > last_message_id) {
        ui->pushButtonUpdateMessages->show();
        startTrayIconBlinking();
        m_pTrayIcon->showMessage(message->senderName(), message->bodyPlain());
        settings.setValue("last_message_id", QString::number(message->id()));
        settings.sync();
    }
    if (ui->verticalLayout->count() == 0) {
        this->updateMessageList();
    }
}

void MainWindow::timeOut()
{
    statusBar()->showMessage(tr("Fetching data ..."));
    m_pClient->fetchMessages();
}

void MainWindow::startTrayIconBlinking()
{
    m_pTrayIconTimer->start();
}

void MainWindow::stopTrayIconBlinking()
{
    m_pTrayIconTimer->stop();
    m_bBlink = true;
    trayIconTimeOut();
}

void MainWindow::trayIconTimeOut()
{
    if (m_bBlink) {
      m_pTrayIcon->setIcon(m_IconNormal);
      m_bBlink = false;
    } else {
      m_pTrayIcon->setIcon(m_IconBlank);
      m_bBlink = true;
    }
}

void MainWindow::restoreSettings()
{
    QSettings settings;
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings;
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    settings.sync();
    QMainWindow::closeEvent(event);
}

void MainWindow::on_pushButtonUpdateMessages_clicked()
{
    updateMessageList();
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Escape)
    {
        close();
    }
}
