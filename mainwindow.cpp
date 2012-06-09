#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSystemTrayIcon *m_pTrayIcon = new QSystemTrayIcon(this);
    m_pTrayIcon->setIcon(QIcon(":/images/yammer_logo.png"));
    m_pTrayIcon->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
