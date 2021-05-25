#ifndef CUSTOMCALLBUTTON_H
#define CUSTOMCALLBUTTON_H

#include <QObject>
#include <QPushButton>

class CustomCallButton : public QPushButton
{
    Q_OBJECT

public slots:
    void ButtonAction(QString name);

public:
    CustomCallButton(QWidget *parent = 0);
    ~CustomCallButton();
};

#endif // CUSTOMCALLBUTTON_H
