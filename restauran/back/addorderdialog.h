#ifndef ADDORDERDIALOG_H
#define ADDORDERDIALOG_H

#include <QDialog>
#include <QSpinBox>
#include <QComboBox>
#include <vector>
#include "MenuItem.h"
#include "Order.h"

class AddOrderDialog : public QDialog {
    Q_OBJECT

public:
    AddOrderDialog(const std::vector<MenuItem>& menu, QWidget* parent = nullptr);

    Order getOrder() const;

private:
    QSpinBox* spinId;
    QSpinBox* spinTable;
    QSpinBox* spinCount;
    QComboBox* comboDish;
};

#endif