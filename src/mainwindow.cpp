#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "logindialog.h"
#include "messagewidget.h"

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

    ui->listWidgetMessages->clear();

    MessageWidget* message1 = new MessageWidget(this);
    MessageWidget* message2 = new MessageWidget(this);
    message1->setTitle("<b>Jack Daniels</b>");
    
    message1->setContent("If you are doing something custom, you could override QLabel::sizeHint() and return appropriate size for the widget (or maybe just set minimumSize). You may call QWidget::updateGeometry() to notify the layout system about the geometry change. (2) If you are doing something custom, you could override QLabel::sizeHint() and return appropriate size for the widget (or maybe just set minimumSize). You may call QWidget::updateGeometry() to notify the layout system about the geometry change (/2)");
    message1->adjustSize();

    QListWidgetItem* item1 = new QListWidgetItem(ui->listWidgetMessages);
    QListWidgetItem* item2 = new QListWidgetItem(ui->listWidgetMessages);

    ui->listWidgetMessages->setItemWidget(item1, message1);
    ui->listWidgetMessages->setItemWidget(item2, message2);

    item1->setSizeHint(message1->size());
    item2->setSizeHint(message2->size());
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
