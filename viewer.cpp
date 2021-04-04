#include "viewer.h"
#include "ui_viewer.h"

#include <stdio.h>

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
    //std::cout << dir.toStdString() << std::endl;
    QFile open_file(dir);
    std::string key = ui->decryptCode->text().toStdString();
    std::string contents;
    char result[1024] = { 0, };
    if(!open_file.open(QIODevice::ReadOnly)){
        QMessageBox::information(this, "Fail", "File open error");
        return;
    }
    QTextStream in(&open_file);
    for(qint64 i = 0; i < open_file.size(); i++){
        contents += in.read(1).toStdString()[0] ^ key[i % key.size()];
        key[i % key.size()] ^= key[i+1 % key.size()];
        std::cout << contents << std::endl;
    }
    for(int i = 0; i < contents.size(); i++){
        std::cout << std::hex << (int)contents[i] << std::endl;
    }
    //ui->decryptCode->text();
    //ui->decryptViewer->setText(QString(contents.c_str()));
}
