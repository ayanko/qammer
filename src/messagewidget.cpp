#include "messagewidget.h"
#include "ui_messagewidget.h"

#include "messagedialog.h"
#include "message.h"
#include "user.h"

#include <QDebug>

MessageWidget::MessageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageWidget)
{
    ui->setupUi(this);
}

MessageWidget::~MessageWidget()
{
    delete ui;
}

void MessageWidget::clearMessageWidgets()
{
    QLayoutItem* item;
    while(( item = ui->verticalLayout2->takeAt(0)) != 0)
    {
        delete item->widget();
        delete item;
    }
}

void MessageWidget::addChild(MessageWidget* widget) {
    ui->verticalLayout2->addWidget(widget);
}

void MessageWidget::setMugshot(const QPixmap &pixmap)
{
    ui->labelMugshot->setPixmap(pixmap);
}

void MessageWidget::setTitle(const QString &text)
{
    ui->labelTitle->setText(text);
}

void MessageWidget::setContent(const QString &text)
{
    ui->labelContent->setText(text);
}

void MessageWidget::setStatus(const QString &text)
{
    ui->labelStatus->setText(text);
}

void MessageWidget::setMessage(Message* message)
{
    m_pMessage = message;

    QString title;

    if (message->user()) {
      title.append("<b>");
      title.append(message->user()->fullName());
      title.append("</b>");
    }

    QString status;
    status.append("<i>");
    status.append(message->createdAt());
    status.append("</i> ");
    status.append("from <a href=\"");
    status.append(message->clientUrl());
    status.append("\">");
    status.append(message->clientType());
    status.append("</a>   ");
    status.append("<a href=\"");
    status.append(message->webUrl()); 
    status.append("\">View</a>");

    if (message->user()) {
        setMugshot(message->user()->mugshot());
    }
    setTitle(title);
    setContent(message->bodyRich());
    setStatus(status);
}


void MessageWidget::on_toolButtonReply_clicked()
{
    MessageDialog dialog(this);
    dialog.setMessage(m_pMessage);
    dialog.exec();
}
