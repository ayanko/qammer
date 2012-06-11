#include "messagewidget.h"
#include "ui_messagewidget.h"
#include "message.h"
#include "user.h"

MessageWidget::MessageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageWidget)
{
    ui->setupUi(this);
    //ui->listWidgetMessages->setMovement(QListView::Static);
    //ui->listWidgetMessages->setResizeMode(QListView::Adjust);
    //ui->listWidgetMessages->hide();
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
    //QListWidgetItem* item = new QListWidgetItem(ui->listWidgetMessages);
    //ui->listWidgetMessages->setItemWidget(item, widget);
    //item->setSizeHint(widget->size());
    ui->verticalLayout2->addWidget(widget);
}

void MessageWidget::showChildren()
{
    //ui->listWidgetMessages->show();
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
