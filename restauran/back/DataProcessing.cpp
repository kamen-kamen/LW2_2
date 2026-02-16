#include "DataProcessing.h"
#include <algorithm>
#include <QMap>

void sortMenuByPrice(std::vector<MenuItem>& menu) {
    std::sort(menu.begin(), menu.end(),
              [](const MenuItem& a, const MenuItem& b) {
                  return a.getPrice() < b.getPrice();
              });
}

double calculateOrderTotal(int orderId,
                           const std::vector<Order>& orders,
                           const std::vector<MenuItem>& menu) {
    double total = 0;

    for (const auto& ord : orders) {
        if (ord.getId() == orderId) {
            for (const auto& item : menu) {
                if (item.getName() == ord.getDishName()) {
                    total += item.getPrice() * ord.getCount();
                    break;
                }
            }
        }
    }

    return total;
}

QStringList getPopularDishes(const std::vector<Order>& orders) {
    QMap<QString, int> counts;

    for (const auto& o : orders)
        counts[o.getDishName()] += o.getCount();

    int maxVal = 0;
    for (int v : counts.values())
        if (v > maxVal) maxVal = v;

    QStringList result;

    for (auto it = counts.begin(); it != counts.end(); ++it)
        if (it.value() == maxVal && maxVal > 0)
            result << it.key();

    return result;
}
