#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "site_setting.h"
#include <QMessageBox>
#include <QStringList>
#include "rand_gen.h"

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
