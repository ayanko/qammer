#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void toggle();

private slots:
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);

private:
    Ui::MainWindow *ui;
    QSystemTrayIcon *m_pTrayIcon;
    QMenu *m_pTrayMenu;
    QAction *m_pToggleAction;
    QAction *m_pQuitAction;

    void createTrayActions();
    void createTrayMenu();
    void createTrayIcon();
};

#endif // MAINWINDOW_H
