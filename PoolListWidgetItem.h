#ifndef POOLLISTWIDGETITEM_H
#define POOLLISTWIDGETITEM_H

#include <QWidget>
#include "src/Utilities/Utilities.hpp"

namespace Ui {
class PoolListWidgetItem;
}

class PoolListWidgetItem : public QWidget
{
    Q_OBJECT

public:
    explicit PoolListWidgetItem(QWidget *parent = nullptr, PoolInterface *pool = nullptr);
    ~PoolListWidgetItem();
    PoolInterface *pool() const;

private slots:
    void on_comboBox_spotPrice_activated(int index);

private:
    Ui::PoolListWidgetItem *ui;
    PoolInterface *pool_;
};

#endif // POOLLISTWIDGETITEM_H
