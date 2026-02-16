#include "FileManager.h"
#include <QFile>
#include <QTextStream>

void FileManager::saveOrders(const QString& fileName,
                             const std::vector<Order>& orders) {
    QFile file(fileName);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);

        for (const auto& o : orders) {
            out << o.getId() << ";"
                << o.getTable() << ";"
                << o.getDishName() << ";"
                << o.getCount() << "\n";
        }

        file.close();
    }
}

void FileManager::loadOrders(const QString& fileName,
                             std::vector<Order>& orders) {
    QFile file(fileName);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        orders.clear();

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(";");

            if (parts.size() == 4) {
                orders.push_back(
                    Order(parts[0].toInt(),
                          parts[1].toInt(),
                          parts[2],
                          parts[3].toInt())
                );
            }
        }

        file.close();
    }
}
