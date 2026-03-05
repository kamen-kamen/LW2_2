#pragma once

#include <vector>
#include <QStringList>

#include "MenuItem.h"
#include "Order.h"

void sortMenuByPrice(std::vector<MenuItem>& menu);

double calculateTableTotal(int tableNumber,
                           const std::vector<Order>& orders,
                           const std::vector<MenuItem>& menu);

QStringList getPopularDishes(const std::vector<Order>& orders);