#ifndef CUSTOMWIDGETTWO_H
#define CUSTOMWIDGETTWO_H

#include <QObject>
#include <QWidget>

class CustomWidgetTwo : public QWidget
{
    Q_OBJECT
public:
    explicit CustomWidgetTwo(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event);

signals:

public slots:
};

#endif // CUSTOMWIDGETTWO_H
