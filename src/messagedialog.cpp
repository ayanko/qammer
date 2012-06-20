#include "messagedialog.h"
#include "ui_messagedialog.h"

#include "mainwindow.h"
#include "client.h"
#include "message.h"

extern MainWindow*  gMainWindow;

MessageDialog::MessageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MessageDialog)
{
    ui->setupUi(this);
}

MessageDialog::~MessageDialog()
{
    delete ui;
}

void MessageDialog::on_pushButtonSend_clicked()
{
    gMainWindow->client()->sendReplyMessage(ui->textEdit->toPlainText(), m_pMessage->id());
    close();
}
