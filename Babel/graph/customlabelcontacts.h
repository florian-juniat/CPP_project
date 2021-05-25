#ifndef CUSTOMLABELCONTACTS_H
#define CUSTOMLABELCONTACTS_H

#include <QObject>
#include <QWidget>
#include <QLabel>

class CustomLabelContacts : public QLabel
{
public:
    CustomLabelContacts();

protected:
    void paintEvent(QPaintEvent* event);
};

#endif // CUSTOMLABELCONTACTS_H
