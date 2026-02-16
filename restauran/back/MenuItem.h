#ifndef MENUITEM_H
#define MENUITEM_H

#include <QString>

class MenuItem {
private:
    QString name;
    QString description;
    double price;

public:
    MenuItem() {}
    MenuItem(QString n, QString d, double p)
        : name(n), description(d), price(p) {}

    QString getName() const { return name; }
    QString getDescription() const { return description; }
    double getPrice() const { return price; }

    void setName(QString n) { name = n; }
    void setDescription(QString d) { description = d; }
    void setPrice(double p) { price = p; }
};

#endif
