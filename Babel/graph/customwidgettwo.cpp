#include "customwidgettwo.h"
#include <QPainter>

CustomWidgetTwo::CustomWidgetTwo(QWidget *parent) : QWidget(parent)
{

}

void CustomWidgetTwo::paintEvent(QPaintEvent *event)
{
    QPainter device(this);

    device.setPen(Qt::white);
    device.setBrush(Qt::red);
    device.drawRoundedRect(0, 0, this->width(), this->height() / 2, 0, 0);
}
