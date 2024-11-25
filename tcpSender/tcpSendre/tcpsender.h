#ifndef TCPSENDER_H
#define TCPSENDER_H

#include <QDialog>
#include <QtNetwork>
#include <QtWidgets>


class tcpSender : public QDialog
{
    Q_OBJECT

public:
    tcpSender(QWidget *parent = nullptr);
    ~tcpSender();

public slots:
    void start();
    void startTransfer();
    void updateClientProgress(qint64 numBytes);
    void openFile();

private:
    QProgressBar     *clientProgressBar;
    QLabel           *clientStatusLabel;
    QLabel           *ipLabel;
    QLabel           *portLabel;
    QLineEdit        *ipLineEdit;
    QLineEdit        *portLineEdit;
    QPushButton      *startButton;
    QPushButton      *quitButton;
    QPushButton      *openButton;
    QDialogButtonBox *buttonBox;
    QTcpSocket       tcpClient;

    qint64           totalBytes;
    qint64           bytesWritten;
    qint64           bytesToWrite;
    qint64           loadSize;
    QString          fileName;
    QFile            *localFile;
    QByteArray       outBlock;

};
#endif // SENDER_H
