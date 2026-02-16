#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include <QString>
#include "Order.h"

class FileManager {
public:
    static void saveOrders(const QString& fileName,
                           const std::vector<Order>& orders);

    static void loadOrders(const QString& fileName,
                           std::vector<Order>& orders);
};

#endif
