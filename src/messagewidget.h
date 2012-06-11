#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <QWidget>

namespace Ui {
class MessageWidget;
}

class Message;

class MessageWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MessageWidget(QWidget *parent = 0);
    ~MessageWidget();

    void clearMessageWidgets();

    void setMugshot(const QPixmap &pixmap);
    void setTitle(const QString &text);
    void setContent(const QString &text);
    void setStatus(const QString &text);
    void showChildren();
    void addChild(MessageWidget* widget);
    void setMessage(Message* message);
    
private:
    Ui::MessageWidget *ui;
};

#endif // MESSAGEWIDGET_H
