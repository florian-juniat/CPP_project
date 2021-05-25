#include "customcallbutton.h"
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include "mainwindow.h"

void CustomCallButton::ButtonAction(QString name)
{
    name = name;
    //MainWindow.addList.append(name);
}

CustomCallButton::CustomCallButton(QWidget *parent)
    :QPushButton(parent)
{
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}

CustomCallButton::~CustomCallButton()
{

}
