#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QWidgetMapper>
#include <QLabel>
#include <QPainter>
#include <QFont>
#include "customlabelcontacts.h"
#include <QStringList>
#include <QWidget>
#include <QSignalMapper>
#include <map>
#include "labelcontactlist.h"
#include <QTextEdit>
#include <QLineEdit>
#include <QPlainTextEdit>

#include <thread>
#include <vector>
#include <string>

#include <iostream>


using std::string;
using ip::tcp;
using namespace boost::asio;


void send_(boost::shared_ptr<tcp::socket> sok, std::string message);
std::string read_(boost::shared_ptr<tcp::socket> sok);

std::vector<std::string> split(std::string str, char c);













MainWindow::MainWindow(QWidget *parent, boost::shared_ptr<tcp::socket> sokk, std::string *rr, bool *st) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    start = st;
    recv_go = rr;
    sok = sokk;
    ui->setupUi(this);
    setWindowTitle("BABEL");

    recv = read_(sok);

    if (connexionStatut == 1) {
        InConnect();
    } else {
        Connexion();
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::Connexion()
{
    myCustomWidget = new CustomWidget(this); 
    my_w_Layout = new QVBoxLayout(this);
    myCustomWidget->setLayout(my_w_Layout);
    my_w_Layout->addWidget(myCustomWidget);

    QLineEdit *myPseudo= new QLineEdit;
    my_w_Layout->addWidget(myPseudo);
    pseudo = myPseudo->text();
    QString rec = myPseudo->text();
    QPushButton* co = new QPushButton("Connexion");
    my_w_Layout->addWidget(co);

    connect(myPseudo, SIGNAL(textChanged(const QString &)), this, SLOT(changePseudo(const QString &)));

    setCentralWidget(myCustomWidget);
}


void MainWindow::quit()
{
    *start = false;
    send_(sok, "quit end\n");
    while (*start != true);
    exit(0);
}

void MainWindow::InConnect()
{
    *start = true;
    myCustomWidget = new CustomWidget(this);
    my_w_Layout = new QVBoxLayout(this);
    my_h_Layout = new QVBoxLayout(this);
    myCall = new QHBoxLayout(this);
    myLabel = new QLabel(this);
    myCustomWidget->setLayout(my_w_Layout);
    c = new QWidget(this);
    c->setLayout(my_h_Layout);

    my_h_Layout->addWidget(c);
    my_w_Layout->addWidget(c);
    my_w_Layout->addSpacing(20);
    my_h_Layout->addLayout(my_w_Layout);




    LabelContactList* lab = new LabelContactList(this);
    my_w_Layout->addWidget(lab);
    for (int i = 0; i < listContact.size(); i++) {
        this->name.append(listContact[i]);
        if (listContact[i] != pseudo) {
            LabelContactList* btn = new LabelContactList(this);
            btn->setText(listContact[i]);
            my_w_Layout->addWidget(btn);

            CustomCallButton* call = new CustomCallButton(this);
            call->setPalette(Qt::green);
            call->setText("Call");
            if (soloCall == 2 && inCall == i) {
                call->setPalette(Qt::red);
                call->setText("End");
            }
            if (soloCall == 1 && inCall == i) {
                call->setPalette(Qt::yellow);
                call->setText("Not connected");
            }
            if (soloCall == 3 && inCall == i) {
                call->setPalette(Qt::cyan);
                call->setText("Reply");
            }
            my_w_Layout->addWidget(call);


            if (i == 0) {
                my_w_Layout->addSpacing(0);
            }


            QSignalMapper* signalMapperTwo = new QSignalMapper (this);
            connect(call, SIGNAL(clicked(bool)), signalMapperTwo, SLOT(map()));
            signalMapperTwo->setMapping(call, i);
            connect(signalMapperTwo, SIGNAL(mapped(int)), this, SLOT(clicktoCallSolo(int)));
        }
    }

    for (int j = 0; j < addList.size(); j++) {
        LabelContactList* groupName = new LabelContactList(this);
        groupName->setText(addList[j]);
        my_h_Layout->addWidget(groupName);
    }

    QPushButton* co = new QPushButton("QUIT");
    co->setPalette(Qt::red);
    my_w_Layout->addWidget(co);

    connect(co, SIGNAL(clicked(bool)), this, SLOT(quit()));

    setCentralWidget(myCustomWidget);
}



void MainWindow::clicktoCallSolo(int test)
{
    currentCall = name[test];
    inCall = test;
    soloCall = 2;
    std::string ps = (this->name[test]).toStdString();

    std::cout << "Ask server to call : " << ps << std::endl;

    *recv_go = "";
    send_(sok, "call " + ps + " end\n");
    while ((*recv_go) == "");
    std::cout << "//  " << *recv_go << std::endl;
    if ((*recv_go)[0] == '2') {
        inCall = test;
        soloCall = 1;
    }
    if ((*recv_go)[0] == '1') {
        inCall = test;
        soloCall = 2;
    }
    InConnect();
}

void test()
{
}

void MainWindow::changePseudo(const QString &rec)
{
    qDebug() << rec << endl;
    pseudo = rec;
    send_(sok, "pseudo " + pseudo.toStdString() + " end\n");
    recv = read_(sok);
    std::cout << recv << std::endl;
    if ((recv)[0] == '2') {
        Connexion();
    } else {
        send_(sok, "contact end\n");
        recv = read_(sok);
        QString str = QString::fromStdString(recv);
        this->listContact = str.split(" ");
        (this->listContact).removeLast();
        InConnect();
    }
}

