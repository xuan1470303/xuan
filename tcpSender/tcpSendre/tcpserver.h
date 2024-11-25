#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QDialog>
#include <QtNetwork>
#include <QtWidgets>

class tcpServer : public QDialog
{
    Q_OBJECT

public:
    tcpServer(QWidget *parent = nullptr);
    ~tcpServer();
public slots:
    void start();
    void acceptConnection();
    void updateServerProgress();
    void displayError(QAbstractSocket::SocketError socketError);
private:
    QProgressBar     *serverProgressBar;
    QLabel           *serverStatusLabel;
    QLabel           *ipLabel;
    QLabel           *portLabel;
    QLineEdit        *ipLineEdit;
    QLineEdit        *portLineEdit;
    QPushButton      *startButton;
    QPushButton      *quitButton;
    QDialogButtonBox *buttonBox;

    QTcpServer       tcp_Server;
    QTcpSocket       *tcpServerConnection;
    qint64           totalBytes;
    qint64           byteReceived;
    qint64           fileNameSize;
    QString          fileName;
    QFile            *localFile;
    QByteArray       inBlock;
};
#endif // TCPSERVER_H
