#ifndef METRICSTABLE_H
#define METRICSTABLE_H

#include <QWidget>
#include "src/Utilities/Utilities.hpp"

namespace Ui {
class MetricsTable;
}

class MetricsTable : public QWidget
    {
        Q_OBJECT
    public:
        explicit MetricsTable(QWidget *parent = nullptr, PoolInterface *pool = nullptr);
        ~MetricsTable();


    private:
        Ui::MetricsTable *ui;
        PoolInterface *pool_;
        //ProvideDialog *provide_dialog;
    };

#endif // METRICSTABLE_H
