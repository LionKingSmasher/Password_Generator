#include "viewer.h"
#include "ui_viewer.h"

#include <QFileDialog>
#include <QIODevice>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

#include <iostream>

viewer::viewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::viewer)
{
    ui->setupUi(this);
}

viewer::~viewer()
{
    delete ui;
}

void viewer::on_pushButton_clicked()
{
    ui->decryptViewer->clear(); //clear on viewer
    QString dir = QFileDialog::getOpenFileName(this, "File Selection", "/home/shinpc/Documents/shincrypt", "Files (*)");
    std::cout << dir.toStdString() << std::endl;
    QFile open_file(dir);
    QString contents;
    char result[1024] = { 0, };
    if(!open_file.open(QIODevice::ReadOnly)){
        QMessageBox::information(this, "Fail", "File open error");
        return;
    }
    QTextStream in(&open_file);
    for(qint64 i = 0; i < open_file.size(); i++){
        contents += in.read(1).toStdString().c_str();
        std::cout << contents.toStdString() << std::endl;
    }
    ui->decryptViewer->setText(contents);
}
