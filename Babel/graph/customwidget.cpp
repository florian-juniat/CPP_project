#include "customwidget.h"
#include <QPainter>

CustomWidget::CustomWidget(QWidget *parent) : QWidget(parent)
{

}

void CustomWidget::paintEvent(QPaintEvent *event)
{
    QPainter device(this);

    device.setPen(Qt::white);
    device.setBrush(Qt::gray);
    //device.drawRoundedRect(0, 0, this->width() / 2, this->height(), 0, 0);
}
