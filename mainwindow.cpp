#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "logobj.h"
#include <qboxlayout.h>
#include "qgridlayout.h"
#include "qpushbutton.h"

string MainWindow::tabNames[]={"PlaneControl"};
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    create_list(); //initialzation of FUNC MAP & LOGOBJ MAP

    //----------------Initialization Of PlaneControl
    QWidget *ctlWidget = new QWidget;
    QVBoxLayout *vBoxLayout = new QVBoxLayout;
    ctlWidget->setLayout( vBoxLayout );
    LOGOBJ_MAP::iterator it= logObjMap.find(tabNames[0]);
    //LogObj *pLog1 = new LogObj;
    LogObj *pLog1 = it->second;
    QHBoxLayout *hBoxLayout = new QHBoxLayout;
    QWidget *ctlPaneWidget = new QWidget;
    ctlPaneWidget->setLayout( hBoxLayout);

    vBoxLayout->addWidget( ctlPaneWidget );
    vBoxLayout->addWidget( pLog1->getWidget() );
    QPushButton *btn_left = new QPushButton(QWidget::tr("left"), this);
    QPushButton *btn_right = new QPushButton(QWidget::tr("right"), this);
    QPushButton *btn_up = new QPushButton(QWidget::tr("up"), this);
    QPushButton *btn_down = new QPushButton(QWidget::tr("down"), this);
    QWidget *direction = new QWidget;
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->setSpacing(2);
    gridLayout->setMargin(2);
    gridLayout->addWidget(btn_left,1,0);
    gridLayout->addWidget(btn_right,1,2);
    gridLayout->addWidget(btn_up,0,1);
    gridLayout->addWidget(btn_down,2,1);
    direction->setLayout( gridLayout );
    hBoxLayout->addWidget( direction );
    QObject::connect(btn_left, SIGNAL(clicked()),this, SLOT(leftOn()));
    QObject::connect(btn_right, SIGNAL(clicked()),this, SLOT(RightOn()));
    QObject::connect(btn_up, SIGNAL(clicked()),this, SLOT(UpOn()));
    QObject::connect(btn_down, SIGNAL(clicked()),this, SLOT(DownOn()));

    QPushButton *btn_forward = new QPushButton(QWidget::tr("forward"), this);
    QPushButton *btn_backward = new QPushButton(QWidget::tr("backward"), this);
    QPushButton *btn_straight = new QPushButton(QWidget::tr("straight"), this);
    QPushButton *btn_reverse = new QPushButton(QWidget::tr("reverse"), this);
    QWidget *direction2 = new QWidget;
    QGridLayout *gridLayout2 = new QGridLayout;
    gridLayout2->setSpacing(2);
    gridLayout2->setMargin(2);
    gridLayout2->addWidget(btn_straight,1,0);
    gridLayout2->addWidget(btn_reverse,1,2);
    gridLayout2->addWidget(btn_forward,0,1);
    gridLayout2->addWidget(btn_backward,2,1);
    direction2->setLayout( gridLayout2 );
    hBoxLayout->addWidget( direction2 );

    ui->tabWidget->addTab( ctlWidget, QString::fromStdString(tabNames[0]));
    ui->tabWidget->removeTab( 0 );
    ui->tabWidget->removeTab( 0 );
    //----------------End of Initialization Of PlaneControl
    int i = 0;
    i++;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::leftOn() {
    invoke("Left");
}

void MainWindow::RightOn() {
    invoke("Right");
}

void MainWindow::UpOn() {
    invoke("Up");
}

void MainWindow::DownOn() {
    invoke("Down");
}

void MainWindow::invoke( string operation  ) {
    FUNC_MAP::iterator it= funcMap.find(operation);

    if(it == funcMap.end()) {
        return;
    }
    else {
        int (*func)(FuncParam*) = it->second.first;
        FuncParam *param = it->second.second;
        func( param );
    }
}

int flyUp( FuncParam *param) {
    param->getLogObj()->addLog("Up");
}

int flyDown( FuncParam *param) {
    param->getLogObj()->addLog("Down");
}

int flyLeft( FuncParam *param) {
    param->getLogObj()->addLog("Left");
}

int flyRight( FuncParam *param) {
    param->getLogObj()->addLog("Right");
}

void MainWindow::create_list() {
    for( int i; i < sizeof(tabNames)/sizeof(string); ++i ) {
        LogObj *pLogObj = new LogObj;
        logObjMap.insert(pair<string,LogObj *>(tabNames[i],pLogObj));
    }
    LOGOBJ_MAP::iterator it= logObjMap.find(tabNames[0]);
    addFunc( "Up",flyUp, NULL, it->second );
    addFunc( "Down",flyDown, NULL,it->second );
    addFunc( "Left",flyLeft, NULL, it->second );
    addFunc( "Right",flyRight, NULL, it->second );

    return;
}

void MainWindow::addFunc( string operationName, int(*func)(FuncParam*), void *data, LogObj *pLogObj ) {
    FuncParam *Param = new FuncParam;
    Param->setData( data );
    Param->setLogObj( pLogObj );
    funcMap.insert(pair<string,pair<int(*)(FuncParam*), FuncParam*> >(operationName,pair<int(*)(FuncParam*), FuncParam*>(func, Param)));
}



