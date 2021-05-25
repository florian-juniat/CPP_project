#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QObject>
#include <QWidget>

class CustomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event);

signals:

public slots:
};

#endif // CUSTOMWIDGET_H
