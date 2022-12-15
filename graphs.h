#ifndef GRAPHS_H
#define GRAPHS_H

#include <QDialog>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include <QSplineSeries>
#include <sstream>
#include <algorithm>
#include <list>

namespace Ui {
class Graphs;
}

class Graphs : public QDialog
{
    Q_OBJECT

public:
    explicit Graphs(QWidget *parent = nullptr);
    ~Graphs();

private:
    Ui::Graphs *ui;
};

#endif // GRAPHS_H
