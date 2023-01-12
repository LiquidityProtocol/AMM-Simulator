#include <QApplication>
#include <QtCharts>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Initialize chart and chart view
    QtCharts::QChart *chart = new QtCharts::QChart();
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);

    // Set axis labels
    QtCharts::QValueAxis *axisX = new QtCharts::QValueAxis();
    axisX->setTitleText("Iteration");
    axisX->setTickCount(10);
    chart->addAxis(axisX, Qt::AlignBottom);

    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();
    axisY->setTitleText("LP Token Quantity");
    axisY->setTickCount(10);
    chart->addAxis(axisY, Qt::AlignLeft);

    // Add data series for token1 and token2 quantities
    QtCharts::QLineSeries *series1 = new QtCharts::QLineSeries();
    series1->setName("Token1 Quantity");
    chart->addSeries(series1);
    series1->attachAxis(axisX);
    series1->attachAxis(axisY);

    QtCharts::QLineSeries *series2 = new QtCharts::QLineSeries();
    series2->setName("Token2 Quantity");
    chart->addSeries(series2);
    series2->attachAxis(axisX);
    series2->attachAxis(axisY);

    // Iterate through the function and add data points
    for (int i = 0; i < iteration_counter; i++) {
        Token *token1 = Token::GetToken("token1");
        Token *token2 = Token::GetToken("token2");
        UniswapV2Pool pool1({{token1, 1000}, {token2, 1000}});
        UniswapV2Pool pool2({{token1, 900}, {token2, 1111}});
        Account *LP = Account::GetAccount("LP");
        LP -> Deposit(token1, 20);
        LP -> Deposit(token2, 20);

        LP -> Provide(&pool1, {{token1, 20}, {token2, 20}});

        LP -> Withdraw(&pool2, LP -> GetQuantity(pool1.pool_token()));

        // Add data points for token1 and token2 quantities
        series1->append(i, LP->GetQuantity(token1));
        series2->append(i, LP->GetQuantity(token2));
    }

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    // Show chart in a QMainWindow


