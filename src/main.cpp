#include <QApplication>
#include <QMessageBox>
#include <QSettings>

#include "mainwindow.h"

MainWindow* gMainWindow;

class LoginDialog;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("qammer");
    QCoreApplication::setApplicationName("qammer");

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0,
                              QObject::tr("Systray"),
                              QObject::tr("I couldn't detect any system tray "
                                          "on this system."));
        return 1;
    }

    QApplication::setQuitOnLastWindowClosed(false);

    MainWindow w;
    gMainWindow = &w;
    w.show();

    QSettings settings;

    if (!settings.contains("access_token")) {
      w.login();
    }

    return a.exec();
}
