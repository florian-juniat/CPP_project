#include "customlabelcontacts.h"
#include <QPainter>

CustomLabelContacts::CustomLabelContacts()
{

}

void CustomLabelContacts::paintEvent(QPaintEvent *event)
{
    QPainter device(this);

    device.setPen(Qt::white);
    device.setBrush(Qt::gray);
    device.drawRoundedRect(0, 0, this->width() / 2, this->height(), 0, 0);
}
