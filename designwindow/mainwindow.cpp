#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMainWindow>
#include <QAction>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    textEdit = ui->textEdit;

    connect(ui->actionCopy, &QAction::triggered, this, &MainWindow::on_actionCopy_triggered);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionCopy_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text Files (*.txt);;All Files (*)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << textEdit->toPlainText();
            file.close();
            QMessageBox::information(this, tr("Success"), tr("File saved successfully!"));
        } else {
            QMessageBox::warning(this, tr("Error"), tr("Could not save the file."));
        }
    }
}
