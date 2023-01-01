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
    void set_last_quantities(std::unordered_map<Token *, double> input_quantities);
    void set_last_spot_prices(std::unordered_map<Token *, std::unordered_map<Token *, double>> input_spots);

private slots:
    void on_comboBox_spotPrice_activated(int index);

    void on_comboBox_secondToken_activated(int index);

private:
    void TokenGraph(Token* input_token, Token* output_token);
    Ui::PoolListWidgetItem *ui;
    PoolInterface *pool_;
    std::unordered_map<Token *, double> last_quantities;
    std::unordered_map<Token *, std::unordered_map<Token *, double>> last_spot_prices;
};

#endif // POOLLISTWIDGETITEM_H
