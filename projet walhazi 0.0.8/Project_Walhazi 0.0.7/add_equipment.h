#ifndef ADD_EQUIPMENT_H
#define ADD_EQUIPMENT_H

#include <QDialog>

namespace Ui {
class add_equipment;
}

class add_equipment : public QDialog
{
    Q_OBJECT

public:
    explicit add_equipment(QWidget *parent = nullptr);
    ~add_equipment();

private slots:
    void on_add_clicked();

private:
    Ui::add_equipment *ui;
};

#endif // ADD_EQUIPMENT_H
