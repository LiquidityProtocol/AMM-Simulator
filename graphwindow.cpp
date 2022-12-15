#include "graphwindow.h"
#include "QtWidgets/qdialog.h"
#include "ui_graphwindow.h"



GraphWindow::GraphWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphWindow)
{
    ui->setupUi(this);
}

GraphWindow::~GraphWindow()
{
    delete ui;
}

void GraphWindow::on_pushButton_clicked()
{
    QDialog aa;
                aa.setDisabled(false);

                //aa.display();

                QPieSeries *series = new QPieSeries();
                            series->append("Token 1", 1);
                            series->append("Token 2", 2);
                            series->append("Token 3", 3);
                            series->append("Token 4", 4);
                            series->append("Token 5", 5);

                        QPieSlice *slice = series->slices().at(1);
                            slice->setExploded();
                            slice->setLabelVisible();
                            slice->setPen(QPen(Qt::darkGreen, 1));
                            slice->setBrush(Qt::green);

                        QPieSlice *slice0 = series->slices().at(0);
                            slice0->setLabelVisible();

                        QPieSlice *slice2 = series->slices().at(2);
                            slice2->setLabelVisible();

                        QPieSlice *slice3 = series->slices().at(3);
                            slice3->setLabelVisible();

                        QPieSlice *slice4 = series->slices().at(4);
                            slice4->setLabelVisible();


                        QChart *chart = new QChart();
                            chart->addSeries(series);
                            chart->setTitle("Tokens in the Pool");
                            chart->legend()->hide();

                        QChartView *chartView = new QChartView(chart);
                            chartView->setRenderHint(QPainter::Antialiasing);

                        QMainWindow window;
                            window.setCentralWidget(chartView);
                            window.resize(600, 500);
                            window.show();


                aa.exec();
}

