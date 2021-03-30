#ifndef VIEWER_H
#define VIEWER_H

#include <QDialog>

namespace Ui {
class viewer;
}

class viewer : public QDialog
{
    Q_OBJECT

public:
    explicit viewer(QWidget *parent = nullptr);
    ~viewer();

private slots:
    void on_pushButton_clicked();

private:
    Ui::viewer *ui;
};

#endif // VIEWER_H
