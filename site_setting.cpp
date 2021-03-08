#include "site_setting.h"
#include "ui_site_setting.h"

site_setting::site_setting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::site_setting)
{
    ui->setupUi(this);
}

site_setting::~site_setting()
{
    delete ui;
}

void site_setting::on_add_button_clicked()
{
    accept();
}

void site_setting::on_cancel_button_clicked()
{
    reject();
}


QString site_setting::site_name() const {
    return ui->textEdit->toPlainText();
}
