#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_GenButton_clicked();

    void on_GenDataBase_itemClicked(QListWidgetItem *item);

    void on_password_database_itemClicked(QTableWidgetItem *item);

    void on_decryptNowButton_clicked();

private:
    Ui::MainWindow *ui;

    enum Column{
        NAME,
        PASSWORD
    };
};
#endif // MAINWINDOW_H
