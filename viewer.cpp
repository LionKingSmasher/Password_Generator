#include "viewer.h"
#include "ui_viewer.h"

#include <QFileDialog>
#include <QIODevice>
#include <QMessageBox>

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
    QString dir = QFileDialog::getOpenFileName(this, "File Selection", "/home/shinpc/Documents/shincrypt", "Files (*.*)");
    QFile open_file(dir);
    if(!open_file.open(QIODevice::ReadOnly)){
        QMessageBox::information(this, "Fail", "File open error");
        return;
    }

}
