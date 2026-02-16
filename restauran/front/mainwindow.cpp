#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QTableWidgetItem>

#include "../back/DataProcessing.h"
#include "../back/FileManager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainwindow)
{
    ui->setupUi(this);

    // Хардкод меню (по заданию)
    menuList = {
        MenuItem("Борщ", "Свежий, с чесноком", 350.0),
        MenuItem("Плов", "Узбекский с бараниной", 450.0),
        MenuItem("Цезарь", "С курицей", 380.0),
        MenuItem("Кофе", "Арабика", 150.0)
    };

    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(
        {"Блюдо", "Описание", "Цена"});

    ui->tableOrders->setColumnCount(4);
    ui->tableOrders->setHorizontalHeaderLabels(
        {"Заказ №", "Стол", "Блюдо", "Кол-во"});

    for (const auto& item : menuList)
        ui->comboDish->addItem(item.getName());

    updateMenuTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//////////////////////////////////////////////////////////////

void MainWindow::updateMenuTable() {
    ui->tableWidget->setRowCount(0);

    for (int i = 0; i < (int)menuList.size(); ++i) {
        ui->tableWidget->insertRow(i);

        ui->tableWidget->setItem(i, 0,
            new QTableWidgetItem(menuList[i].getName()));
        ui->tableWidget->setItem(i, 1,
            new QTableWidgetItem(menuList[i].getDescription()));
        ui->tableWidget->setItem(i, 2,
            new QTableWidgetItem(QString::number(menuList[i].getPrice())));
    }
}

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
// ДОБАВЛЕНИЕ

void MainWindow::on_btnAddOrder_clicked() {
    int id = ui->editOrderNum->text().toInt();
    int table = ui->editTableNum->text().toInt();
    QString dish = ui->comboDish->currentText();
    int count = ui->editCount->text().toInt();

    if (count <= 0) return;

    ordersList.push_back(Order(id, table, dish, count));
    updateOrdersTable();

    ui->memoLog->append("Заказ добавлен.");
}

//////////////////////////////////////////////////////////////
// УДАЛЕНИЕ

void MainWindow::on_btnDeleteOrder_clicked() {
    int id = ui->editOrderNum->text().toInt();

    ordersList.erase(
        std::remove_if(ordersList.begin(), ordersList.end(),
                       [id](const Order& o) {
                           return o.getId() == id;
                       }),
        ordersList.end()
    );

    updateOrdersTable();
    ui->memoLog->append("Заказ удалён.");
}

//////////////////////////////////////////////////////////////
// РЕДАКТИРОВАНИЕ

void MainWindow::on_btnEditOrder_clicked() {
    int id = ui->editOrderNum->text().toInt();
    int newCount = ui->editCount->text().toInt();

    for (auto& o : ordersList) {
        if (o.getId() == id) {
            o.setCount(newCount);
            break;
        }
    }

    updateOrdersTable();
    ui->memoLog->append("Заказ изменён.");
}

//////////////////////////////////////////////////////////////
// СЧЕТ

void MainWindow::on_btnCalculateBill_clicked() {
    int id = ui->editOrderNum->text().toInt();

    double total = calculateOrderTotal(id, ordersList, menuList);

    ui->memoLog->append(
        "\nСчёт по заказу №" +
        QString::number(id) +
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
