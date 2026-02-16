#ifndef ORDER_H
#define ORDER_H

#include <QString>

class Order {
private:
    int id;
    int table;
    QString dishName;
    int count;

public:
    Order() {}
    Order(int i, int t, QString d, int c)
        : id(i), table(t), dishName(d), count(c) {}

    int getId() const { return id; }
    int getTable() const { return table; }
    QString getDishName() const { return dishName; }
    int getCount() const { return count; }

    void setCount(int c) { count = c; }
};

#endif
