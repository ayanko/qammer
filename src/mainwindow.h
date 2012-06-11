#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QTimer>

class Client;
class LoginDialog;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Client *client();
    void login();

public slots:
    void toggle();
    void updateMessageList();
    void popupMessages();

private slots:
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void loggedIn();
    void timeOut();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QSystemTrayIcon *m_pTrayIcon;
    QMenu *m_pTrayMenu;
    QAction *m_pToggleAction;
    QAction *m_pQuitAction;
    QTimer *m_pTimer;

    Client* m_pClient;
    LoginDialog *m_pLoginDialog;

    void createTrayActions();
    void createTrayMenu();
    void createTrayIcon();

    void createLoginDialog();
};

#endif // MAINWINDOW_H
