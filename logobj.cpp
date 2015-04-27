#include "logobj.h"
#include <qformlayout.h>
LogObj::LogObj()
{
    pLogWidget = new QWidget;
    pLatestLog = new QLineEdit;
    pUpdatingLog = new QTextEdit;
    QFormLayout  *formLayout = new QFormLayout;
    formLayout->addRow( pLatestLog );
    formLayout->addRow( pUpdatingLog );
    pLogWidget->setLayout(formLayout );
}

LogObj::~LogObj()
{
    delete pLogWidget;
    delete pLatestLog;
    delete pUpdatingLog;
}

QWidget *LogObj::getWidget() {
    return pLogWidget;
}

void LogObj::addLog( string msg ) {
    //pLatestLog->setEnabled( false );
    QString qmsg = QString::fromStdString(msg);
    pLatestLog->setText( qmsg );
    pUpdatingLog->append( qmsg );
}

