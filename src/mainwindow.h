#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>

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
    void login();

public slots:
    void toggle();

private slots:
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void loggedIn();

private:
    Ui::MainWindow *ui;
    QSystemTrayIcon *m_pTrayIcon;
    QMenu *m_pTrayMenu;
    QAction *m_pToggleAction;
    QAction *m_pQuitAction;

    LoginDialog *m_pLoginDialog;

    void createTrayActions();
    void createTrayMenu();
    void createTrayIcon();

    void createLoginDialog();
};

#endif // MAINWINDOW_H
