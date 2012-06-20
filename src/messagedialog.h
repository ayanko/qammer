#ifndef MESSAGEDIALOG_H
#define MESSAGEDIALOG_H

#include <QDialog>

namespace Ui {
class MessageDialog;
}

class Client;
class Message;

class MessageDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit MessageDialog(QWidget *parent = 0);
    ~MessageDialog();
    
private slots:
    void on_pushButtonSend_clicked();


private:
    Ui::MessageDialog *ui;
    Message* m_pMessage;

public:
    void setMessage(Message* message) { m_pMessage = message; }
};

#endif // MESSAGEDIALOG_H
