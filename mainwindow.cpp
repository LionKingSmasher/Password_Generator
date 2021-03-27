#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "site_setting.h"
#include "rand_gen.h"

#include <QMessageBox>
#include <QStringList>
#include <QFile>
#include <QDate>
#include <QTextStream>
#include <QBitArray>
#include <QDebug>

#include <iostream>#include <string.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList Header;
    Header << "Site" << "password";
    ui->password_database->setColumnCount(2);
    ui->password_database->setHorizontalHeaderLabels(Header);
    ui->password_database->horizontalHeader()->setStretchLastSection(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_GenButton_clicked()
{
    ui->GenDataBase->clear();
    register unsigned __i = 0;
    QString past=""; //past
    while(__i < 100){
        QString ran = Generate_Random(ui->_textEdit->toPlainText(), __i);
//        QMessageBox::information(this, "Test", ran);
//        printf("test: %d\n", __i);
        if(!QString::compare(past, ran, Qt::CaseSensitive)) continue;
        past = ran;
        ui->GenDataBase->addItem(ran);
        __i++;
    }
//    int row = ui->GenDataBase->currentIndex().row();
}

void MainWindow::on_GenDataBase_itemClicked(QListWidgetItem *item)
{
//    QMessageBox::information(this, "test", item->text());
    QString __name;
    site_setting PasswordSiteSetting(this);
    int res = PasswordSiteSetting.exec();
    if(res==QDialog::Rejected) return;
    __name = PasswordSiteSetting.site_name();

    ui->password_database->insertRow(ui->password_database->rowCount());
    int index = ui->password_database->rowCount()-1;
    ui->password_database->setItem(index, NAME, new QTableWidgetItem(__name));
    ui->password_database->setItem(index, PASSWORD, new QTableWidgetItem(item->text()));
}

void MainWindow::on_password_database_itemClicked(QTableWidgetItem *item)
{
    QString webSiteName = ui->password_database->item(item->row(), 0)->text();
    QString webSitePassword = ui->password_database->item(item->row(), 1)->text();
    QString filename = webSiteName + "@"
                     + QString::number(QDate::currentDate().year())
                     + QString::number(QDate::currentDate().month())
                     + QString::number(QDate::currentDate().day())
                     + QString::number(QTime::currentTime().hour())
                     + QString::number(QTime::currentTime().minute())
                     + QString::number(QTime::currentTime().second())
                     + QString::number(QTime::currentTime().msec());
    QFile save_file("/home/shinpc/Documents/"+filename);
    if(ui->cryptCheck->isChecked()){
        if(!QString::compare(ui->keyInput->text(), "", Qt::CaseSensitive)) {
            QMessageBox::information(this, "Fail...", "You don't write key");
            return;
        }
        if(!save_file.open(QIODevice::WriteOnly)){
            QMessageBox::information(this, "Fail...", "File open error...");
            return;
        }
        std::string key = ui->keyInput->text().toStdString();
        QString contents = "website: " + webSiteName +
                           "\nPassword: " + webSitePassword;
        std::string contents_str = contents.toStdString();
        char* result = new char[1024];
        for(int i = 0; i < contents.size(); i++){
            result[i] = contents_str[i] ^ key[i % key.size()];
            key[i % key.size()] ^= key[i + 1 % key.size()];
//          std::cout << std::hex << (int)result[i] << std::endl;
        }
        save_file.write(result, contents.size());
        delete[] result;
        save_file.close();
    }
    else{
        if(!save_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::information(this, "Fail...", "file write fail...");
            return;
        }
        QTextStream out(&save_file);
        QString contents = "website: " + webSiteName +
                           "\nPassword: " + webSitePassword;
        out << contents;

        QMessageBox::information(this, "Complete!!", "Done!");
        save_file.close();
    }
//    QMessageBox::information(this, "test", filename);
//    QMessageBox::information(this, "Test!", ui->password_database->item(item->row(), (item->column()+1)%2)->text());

}
