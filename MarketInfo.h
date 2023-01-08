#ifndef MARKETINFO_H
#define MARKETINFO_H

#include <QWidget>

namespace Ui {
class MarketInfo;
}

class MarketInfo : public QWidget
{
    Q_OBJECT

public:
    explicit MarketInfo(QWidget *parent = nullptr);
    ~MarketInfo();

private:
    Ui::MarketInfo *ui;
};

#endif // MARKETINFO_H
