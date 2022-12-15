#include "graphs.h"
#include "ui_graphs.h"
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include <QSplineSeries>
#include <sstream>
#include <algorithm>
#include <list>

Graphs::Graphs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Graphs)
{
    ui->setupUi(this);

    QChart *chart = new QChart();
    chart->legend()->hide();

    // Customize chart title
    QFont font;
    font.setPixelSize(18);
    chart->setTitleFont(font);
    chart->setTitleBrush(QBrush(QColorConstants::Svg::orange));
    chart->setTitle("Chart for x*y=k");
    chart->createDefaultAxes();


    // Set X axis, add title
    QValueAxis *axisX = new QValueAxis;
    chart->addAxis(axisX, Qt::AlignBottom);
    axisX->setTitleText("Token A");


    // Function (here cst function)
    QSplineSeries *series = new QSplineSeries();
    double k=1000;
    for (int i=1;i<100;i++) {
        double j=i/1;
        series->append(j,k/j);
    }

    // Add function to chart
    chart->addSeries(series);


    // Create point label (here for x coordinate=12)
    QLineSeries *series2 = new QLineSeries();
    double l=1000;
    for (int i=1;i<100;i++) {
        double j=i/1;
        if (j== 12) {
        series2->append(i,l/i);
    }
}

    // Make point label visible
    series2->setPointsVisible(true);
    //label point with coordinates
    //series2->setPointLabelsFormat("(@xPoint,@yPoint)");
    //label points with name
    series2->setPointLabelsFormat("@xPoint A and @yPoint B");
    series2->setPointLabelsVisible(true);

    // Add point to chart
    chart->addSeries(series2);

    // Customize FUNCTION color
    QPen pen(QRgb(0xfdb157));
    pen.setWidth(5);
    series->setPen(pen);

    // Customize Point color
    QPen pen2(QRgb(0xfdb157));
    pen2.setWidth(5);
    series2->setPen(pen2);

    // Set Y axis, add title
    QValueAxis *axisY = new QValueAxis;
    chart->addAxis(axisY, Qt::AlignLeft);
    axisY->setTitleText("Token B");


    // Attach function to axis
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    // Attach point label to axis
    series2->attachAxis(axisX);
    series2->attachAxis(axisY);


    // Add Chart to widget
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setParent(ui->horizontalFrame);

}

Graphs::~Graphs()
{
    delete ui;
}
