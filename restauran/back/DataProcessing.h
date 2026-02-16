#ifndef DATAPROCESSING_H
#define DATAPROCESSING_H

#include <vector>
#include <QStringList>
#include "MenuItem.h"
#include "Order.h"

void sortMenuByPrice(std::vector<MenuItem>& menu);
double calculateOrderTotal(int orderId,
                           const std::vector<Order>& orders,
                           const std::vector<MenuItem>& menu);
QStringList getPopularDishes(const std::vector<Order>& orders);

#endif
