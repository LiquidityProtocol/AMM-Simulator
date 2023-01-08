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
    explicit PoolListWidgetItem(QWidget *parent = nullptr, PoolInterface *pool = nullptr, const std::unordered_map<Token *, double> &input_quantities = {}, const std::unordered_map<Token *, std::unordered_map<Token *, double>> &input_spot_prices = {});
    ~PoolListWidgetItem();
    PoolInterface *pool() const;
    std::unordered_map<Token *, double> curr_quantities() const;
    std::unordered_map<Token *, std::unordered_map<Token *, double>> curr_spot_prices() const;
    int get_comboBox_spotPrice_index() const;
    int get_comboBox_secondToken_index() const;
    void set_comboBox_spotPrice_index(int index);
    void set_comboBox_secondToken_index(int index);

private slots:
    void on_comboBox_spotPrice_currentIndexChanged(int index);
    void on_comboBox_secondToken_currentIndexChanged(int index);

private:
    Ui::PoolListWidgetItem *ui;
    PoolInterface *pool_;
    std::unordered_map<Token *, double> last_quantities_, curr_quantities_;
    std::unordered_map<Token *, std::unordered_map<Token *, double>> last_spot_prices_, curr_spot_prices_;
};

#endif // POOLLISTWIDGETITEM_H
