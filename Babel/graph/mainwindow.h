#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "customcallbutton.h"
#include <QVBoxLayout>
#include "customwidget.h"
#include <QLabel>
#include "customwidgettwo.h"
#include "customlabelcontacts.h"
#include <QWidget>
#include <QString>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <QList>

#include <string>

using namespace boost::asio;
using ip::tcp;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent, boost::shared_ptr<tcp::socket>, std::string *, bool * );

    ~MainWindow();
    QList<QString> addList;
    void Connexion();
    void InConnect();
    std::string *send;
    std::string recv;
    std::string *recv_go;
    bool *start;

public slots:
    void clicktoCallSolo(int test);
    void changePseudo(const QString &rec);
    void quit();

signals:
    void confCall(int test);
    void textChanged(QString rec);

private:
    void handle_async();
    void handle_recv();
    boost::shared_ptr<tcp::socket> sok;
    Ui::MainWindow *ui;
    int connexionStatut = 0;
    QLabel* myLabel;
    QVBoxLayout* my_w_Layout;
    QVBoxLayout* my_h_Layout;
    QHBoxLayout* myCall;
    QWidget* myWidget;
    CustomWidget* myCustomWidget;
    QWidget* c;
    CustomWidgetTwo* myCustomWidgetTwo;
    CustomLabelContacts* myCustomContact;
    QList<QString> name;
    QList<QString> listContact;
    QString currentCall;
    bool groupCalling = false;
    int soloCall = 0;
    int inCall = -1;
    QString pseudo;
    std::string ps;
};

#endif // MAINWINDOW_H
