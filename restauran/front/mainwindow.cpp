#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QTableWidgetItem>
#include <QMessageBox>

#include "../back/DataProcessing.h"
#include "../back/FileManager.h"
#include "../back/AddOrderDialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Меню
    menuList = {
        MenuItem("Борщ", "Свежий, с чесноком", 350.0),
        MenuItem("Плов", "Узбекский с бараниной", 450.0),
        MenuItem("Цезарь", "С курицей", 380.0),
        MenuItem("Кофе", "Арабика", 150.0)
    };

    // Таблица заказов
    ui->tableOrders->setColumnCount(4);
    ui->tableOrders->setHorizontalHeaderLabels(
        {"Заказ №", "Стол", "Блюдо", "Кол-во"});
    ui->tableOrders->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableOrders->setSelectionMode(QAbstractItemView::SingleSelection);

    // Таблица меню
    ui->tableMenu->setColumnCount(3);
    ui->tableMenu->setHorizontalHeaderLabels(
        {"Блюдо", "Описание", "Цена"});

    updateMenuTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//////////////////////////////////////////////////////////////
// ОБНОВЛЕНИЕ МЕНЮ

void MainWindow::updateMenuTable() {
    ui->tableMenu->setRowCount(0);

    for (int i = 0; i < (int)menuList.size(); ++i) {
        ui->tableMenu->insertRow(i);

        ui->tableMenu->setItem(i, 0,
            new QTableWidgetItem(menuList[i].getName()));
        ui->tableMenu->setItem(i, 1,
            new QTableWidgetItem(menuList[i].getDescription()));
        ui->tableMenu->setItem(i, 2,
            new QTableWidgetItem(QString::number(menuList[i].getPrice())));
    }
}

//////////////////////////////////////////////////////////////
// ОБНОВЛЕНИЕ ЗАКАЗОВ

void MainWindow::updateOrdersTable() {
    ui->tableOrders->setRowCount(0);

    for (int i = 0; i < (int)ordersList.size(); ++i) {
        ui->tableOrders->insertRow(i);

        ui->tableOrders->setItem(i, 0,
            new QTableWidgetItem(QString::number(ordersList[i].getId())));
        ui->tableOrders->setItem(i, 1,
            new QTableWidgetItem(QString::number(ordersList[i].getTable())));
        ui->tableOrders->setItem(i, 2,
            new QTableWidgetItem(ordersList[i].getDishName()));
        ui->tableOrders->setItem(i, 3,
            new QTableWidgetItem(QString::number(ordersList[i].getCount())));
    }
}

//////////////////////////////////////////////////////////////
// СОЗДАНИЕ

void MainWindow::on_btnAddOrder_clicked() {
    AddOrderDialog dlg(menuList, this);

    if (dlg.exec() == QDialog::Accepted) {

        Order newOrder = dlg.getOrder();

        // Проверка уникальности ID
        for (const auto& o : ordersList) {
            if (o.getId() == newOrder.getId()) {
                QMessageBox::warning(this,
                    "Ошибка",
                    "Заказ с таким номером уже существует!");
                return;
            }
        }

        ordersList.push_back(newOrder);
        updateOrdersTable();
        ui->memoLog->append("Заказ создан.");
    }
}

//////////////////////////////////////////////////////////////
// УДАЛЕНИЕ

void MainWindow::on_btnDeleteOrder_clicked() {
    int row = ui->tableOrders->currentRow();

    if (row < 0) return;

    auto reply = QMessageBox::question(this,
        "Удаление",
        "Удалить выбранный заказ?");

    if (reply == QMessageBox::Yes) {
        ordersList.erase(ordersList.begin() + row);
        updateOrdersTable();
        ui->memoLog->append("Заказ удалён.");
    }
}

//////////////////////////////////////////////////////////////
// РЕДАКТИРОВАНИЕ

void MainWindow::on_btnEditOrder_clicked() {
    int row = ui->tableOrders->currentRow();

    if (row < 0) return;

    AddOrderDialog dlg(menuList, this);

    if (dlg.exec() == QDialog::Accepted) {
        ordersList[row] = dlg.getOrder();
        updateOrdersTable();
        ui->memoLog->append("Заказ изменён.");
    }
}

//////////////////////////////////////////////////////////////
// СЧЁТ

void MainWindow::on_btnCalculateBill_clicked() {

    int row = ui->tableOrders->currentRow();

    if (row < 0)
        return;

    int tableNumber = ordersList[row].getTable();

    double total =
        calculateTableTotal(tableNumber, ordersList, menuList);

    ui->memoLog->append(
        "\nСчёт по столику №" +
        QString::number(tableNumber) +
        ": " +
        QString::number(total) +
        " руб."
    );
}

//////////////////////////////////////////////////////////////
// ПОПУЛЯРНОЕ

void MainWindow::on_btnShowPopular_clicked() {

    QStringList popular = getPopularDishes(ordersList);

    ui->memoLog->append("\nПопулярные блюда:");

    for (const auto& name : popular)
        ui->memoLog->append("- " + name);
}

//////////////////////////////////////////////////////////////
// СОРТИРОВКА

void MainWindow::on_btnSortMenu_clicked() {
    sortMenuByPrice(menuList);
    updateMenuTable();
    ui->memoLog->append("Меню отсортировано по цене.");
}

//////////////////////////////////////////////////////////////
// СОХРАНЕНИЕ

void MainWindow::on_btnSave_clicked() {
    QString fileName =
        QFileDialog::getSaveFileName(this,
            "Сохранить файл", "", "Text Files (*.txt)");

    if (!fileName.isEmpty()) {
        FileManager::saveOrders(fileName, ordersList);
        ui->memoLog->append("Файл сохранён.");
    }
}

//////////////////////////////////////////////////////////////
// ЗАГРУЗКА

void MainWindow::on_btnLoad_clicked() {
    QString fileName =
        QFileDialog::getOpenFileName(this,
            "Открыть файл", "", "Text Files (*.txt)");

    if (!fileName.isEmpty()) {
        FileManager::loadOrders(fileName, ordersList);
        updateOrdersTable();
        ui->memoLog->append("Файл загружен.");
    }
}