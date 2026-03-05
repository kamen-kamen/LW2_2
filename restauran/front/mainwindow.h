#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ui_mainwindow.h>
#include <vector>
#include "../back/MenuItem.h"
#include "../back/Order.h"

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
    void on_btnAddOrder_clicked();
    void on_btnDeleteOrder_clicked();
    void on_btnEditOrder_clicked();
    void on_btnCalculateBill_clicked();
    void on_btnShowPopular_clicked();
    void on_btnSortMenu_clicked();

    void on_btnSave_clicked();
    void on_btnLoad_clicked();

private:
    Ui::MainWindow *ui;

    std::vector<MenuItem> menuList;
    std::vector<Order> ordersList;

    void updateMenuTable();
    void updateOrdersTable();
};

#endif
