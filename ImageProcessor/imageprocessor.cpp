#include "imageprocessor.h"
#include<QHBoxLayout>
#include<QMenuBar>
#include<QFileDialog>
#include<QDebug>

ImageProcessor::ImageProcessor(QWidget *parent)
    : QMainWindow(parent),zoomFactor(1.0)
{
    setWindowTitle(QStringLiteral("影像處理"));
    central = new QWidget();
    QHBoxLayout *mainLayout = new QHBoxLayout(central);
    imgWin = new QLabel();
    QPixmap    *initPixmap = new QPixmap(300,200);
    initPixmap->fill(QColor(255,255,255));
    imgWin->resize(300,200);
    imgWin->setScaledContents(true);
    imgWin->setPixmap(*initPixmap);
    mainLayout->addWidget(imgWin);
    setCentralWidget(central);
    createActions();
    createMemus();
    creatToolBar();
}

ImageProcessor::~ImageProcessor()
{}

void ImageProcessor::createActions()
{
    openFileAction = new QAction(QStringLiteral("開啟檔案&O"),this);
    openFileAction->setShortcut(tr("Ctrl+O"));
    openFileAction->setStatusTip(QStringLiteral("開啟影像檔案"));
    connect(openFileAction,SIGNAL(triggered()),this,SLOT(showOpenFile()));

    exitAction = new QAction(QStringLiteral("結束&Q"),this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(QStringLiteral("退出程式"));
    connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));

    zoomInAction = new QAction(QStringLiteral("放大&Z"),this);
    zoomInAction->setShortcut(tr("Ctrl+Z"));
    zoomInAction->setStatusTip(QStringLiteral("放大影像"));
    connect(zoomInAction,SIGNAL(triggered()),this,SLOT(zoomIn()));

    zoomOutAction = new QAction(QStringLiteral("縮小&X"),this);
    zoomOutAction->setShortcut(tr("Ctrl+X"));
    zoomOutAction->setStatusTip(QStringLiteral("縮小影像"));
    connect(zoomOutAction,SIGNAL(triggered()),this,SLOT(zoomOut()));
}

void ImageProcessor::createMemus()
{
    fileMenu = menuBar()->addMenu(QStringLiteral("檔案&F"));
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(exitAction);

    toolMenu = menuBar()->addMenu(QStringLiteral("工具&T"));
    toolMenu->addAction(zoomInAction);
    toolMenu->addAction(zoomOutAction);
}

void ImageProcessor::creatToolBar()
{

}

void ImageProcessor::loadFile(QString filename)
{
    img.load(filename);
    imgWin->setPixmap(QPixmap::fromImage(img));
}

void ImageProcessor::showOpenFile()
{
    filename = QFileDialog::getOpenFileName(this,
                                            QStringLiteral("開啟影像"),
                                            tr("."),
                                            "bmp(*.bmp);;png(*.png)"
                                            ";;Jpeg(*.jpg)");
    if(!filename.isEmpty())
    {

        loadFile(filename);

    }
}

void ImageProcessor::zoomIn()
{
    if (!img.isNull())
    {
        QSize newSize = img.size() * 2;
        QImage enlargedImg = img.scaled(newSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QDialog *zoomDialog = new QDialog(this);
        zoomDialog->setWindowTitle("放大圖像");
        QLabel *zoomLabel = new QLabel(zoomDialog);
        zoomLabel->setPixmap(QPixmap::fromImage(enlargedImg));
        zoomLabel->setAlignment(Qt::AlignCenter);
        QVBoxLayout *layout = new QVBoxLayout(zoomDialog);
        layout->addWidget(zoomLabel);
        zoomDialog->setLayout(layout);
        zoomDialog->resize(600, 400);
        zoomDialog->exec();
    }
}

void ImageProcessor::zoomOut()
{
    if (!img.isNull())
    {
        QSize newSize = img.size() / 2;
        QImage shrunkImg = img.scaled(newSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        QDialog *zoomDialog = new QDialog(this);
        zoomDialog->setWindowTitle("縮小圖像");
        QLabel *zoomLabel = new QLabel(zoomDialog);
        zoomLabel->setPixmap(QPixmap::fromImage(shrunkImg));
        zoomLabel->setAlignment(Qt::AlignCenter);
        QVBoxLayout *layout = new QVBoxLayout(zoomDialog);
        layout->addWidget(zoomLabel);
        zoomDialog->setLayout(layout);
        zoomDialog->resize(600, 400);
        zoomDialog->exec();
    }
}
