#include "AddOrderDialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QDialogButtonBox>

AddOrderDialog::AddOrderDialog(const std::vector<MenuItem>& menu, QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("Создать заказ");

    spinId = new QSpinBox;
    spinId->setRange(1, 10000);

    spinTable = new QSpinBox;
    spinTable->setRange(1, 100);

    spinCount = new QSpinBox;
    spinCount->setRange(1, 50);

    comboDish = new QComboBox;
    for (const auto& item : menu)
        comboDish->addItem(item.getName());

    QFormLayout* form = new QFormLayout;
    form->addRow("Номер заказа:", spinId);
    form->addRow("Стол:", spinTable);
    form->addRow("Блюдо:", comboDish);
    form->addRow("Количество:", spinCount);

    QDialogButtonBox* buttons =
        new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(form);
    mainLayout->addWidget(buttons);

    setLayout(mainLayout);
}

Order AddOrderDialog::getOrder() const {
    return Order(
        spinId->value(),
        spinTable->value(),
        comboDish->currentText(),
        spinCount->value()
    );
}