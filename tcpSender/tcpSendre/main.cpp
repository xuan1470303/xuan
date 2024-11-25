#include "tcpsender.h"
#include "tcpserver.h"

#include <QApplication>
#include<QTableWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTabWidget tabWidget;

    tcpSender w1;
    tcpServer w2;

    tabWidget.addTab(&w1, "傳送檔案");
    tabWidget.addTab(&w2, "接收檔案");

    tabWidget.show();
    return a.exec();
}
