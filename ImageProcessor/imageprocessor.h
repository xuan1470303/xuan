#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QMainWindow>
#include<QAction>
#include<QMenu>
#include<QToolBar>
#include<QImage>
#include<QLabel>
#include <QFileDialog>
#include <QDialog>

class ImageProcessor : public QMainWindow
{
    Q_OBJECT

public:
    ImageProcessor(QWidget *parent = nullptr);
    ~ImageProcessor();
    void createActions();
    void createMemus();
    void creatToolBar();
    void loadFile(QString filename);

private slots:
    void showOpenFile();
    void zoomIn();
    void zoomOut();

private:
    QWidget   *central;
    QMenu     *fileMenu;
    QMenu     *toolMenu;
    QToolBar  *fileTool;
    QToolBar  *zoomTool;
    QImage    img;
    QString   filename;
    QLabel    *imgWin;
    QAction   *openFileAction;
    QAction   *exitAction;
    QAction   *zoomInAction;
    QAction   *zoomOutAction;
    QLabel    another;
    double zoomFactor;
};
#endif // IMAGEPROCESSOR_H
