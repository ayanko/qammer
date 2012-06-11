#include "messagewidget.h"
#include "ui_messagewidget.h"

MessageWidget::MessageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageWidget)
{
    ui->setupUi(this);
    //ui->listWidgetMessages->setMovement(QListView::Static);
    //ui->listWidgetMessages->setResizeMode(QListView::Adjust);
    ui->listWidgetMessages->hide();
}

MessageWidget::~MessageWidget()
{
    delete ui;
}

void MessageWidget::addChild(MessageWidget* widget) {
    QListWidgetItem* item = new QListWidgetItem(ui->listWidgetMessages);
    ui->listWidgetMessages->setItemWidget(item, widget);
    item->setSizeHint(widget->size());
}

void MessageWidget::showChildren()
{
    ui->listWidgetMessages->show();
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
