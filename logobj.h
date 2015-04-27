#ifndef LOGOBJ_H
#define LOGOBJ_H
#include <qlineedit.h>
#include <qtextedit.h>
#include <string>
using namespace std;

class LogObj : public QWidget
{
public:
    LogObj();
    ~LogObj();
    QWidget *getWidget();
    void addLog( string msg );
private:
    QWidget *pLogWidget;
    QLineEdit *pLatestLog;
    QTextEdit *pUpdatingLog;
};

#endif // LOGOBJ_H
