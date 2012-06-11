#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <QWidget>

namespace Ui {
class MessageWidget;
}

class MessageWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MessageWidget(QWidget *parent = 0);
    ~MessageWidget();

    void setTitle(const QString &text);
    void setContent(const QString &text);
    void setStatus(const QString &text);
    
private:
    Ui::MessageWidget *ui;
};

#endif // MESSAGEWIDGET_H
