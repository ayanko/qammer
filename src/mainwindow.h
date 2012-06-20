#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QTimer>
#include <QIcon>
#include <QKeyEvent>

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
    Client *client() { return m_pClient; }
    void login();

protected:
    void restoreSettings();
    void closeEvent(QCloseEvent *event);
    void clearMessageWidgets();
    void keyPressEvent(QKeyEvent* event);

public slots:
    void toggle();
    void updateMessageList();
    void popupMessages();
    void startTrayIconBlinking();
    void stopTrayIconBlinking();

private slots:
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void loggedIn();
    void timeOut();
    void trayIconTimeOut();

    void on_pushButtonUpdateMessages_clicked();

private:
    Ui::MainWindow *ui;
    QSystemTrayIcon *m_pTrayIcon;
    QMenu *m_pTrayMenu;
    QAction *m_pToggleAction;
    QAction *m_pQuitAction;
    QTimer *m_pTimer;
    QTimer *m_pTrayIconTimer;
    QIcon m_IconNormal;
    QIcon m_IconBlank;
    bool m_bBlink;

    Client* m_pClient;
    LoginDialog *m_pLoginDialog;

    void createTrayActions();
    void createTrayMenu();
    void createTrayIcon();

    void createLoginDialog();
};

#endif // MAINWINDOW_H
