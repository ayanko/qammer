#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "logindialog.h"

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
