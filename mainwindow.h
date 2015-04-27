#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "funcparam.h"
#include "logobj.h"
#include <map>
using namespace std;

typedef map<string, pair<int(*)(FuncParam*), FuncParam*> > FUNC_MAP;
typedef map<string, LogObj*> LOGOBJ_MAP;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void create_list();
    void addFunc( string operation, int(*func)(FuncParam*), void *data, LogObj *pLogObj );


private slots:
    void leftOn();
    void RightOn();
    void UpOn();
    void DownOn();

private:
    Ui::MainWindow *ui;
    static string tabNames[];
    LOGOBJ_MAP logObjMap;
    FUNC_MAP funcMap;
    void invoke( string operation  );
    /*int flyLeft( FuncParam * );
    int flyRight( FuncParam * );
    int flyUp( FuncParam * );
    int flyDown( FuncParam * );*/

};

#endif // MAINWINDOW_H
