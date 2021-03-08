#ifndef SITE_SETTING_H
#define SITE_SETTING_H

#include <QDialog>

namespace Ui {
class site_setting;
}

class site_setting : public QDialog
{
    Q_OBJECT

public:
    explicit site_setting(QWidget *parent = nullptr);
    ~site_setting();

    QString site_name() const;

private slots:

    void on_add_button_clicked();

    void on_cancel_button_clicked();

private:
    Ui::site_setting *ui;
};

#endif // SITE_SETTING_H
