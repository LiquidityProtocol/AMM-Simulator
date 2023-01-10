#include "PoolGraphItem.h"
#include "ui_PoolGraphItem.h"

QColor random_color(){
      int rgb[3];
      for(int i=0;i<3;i++)
      {
        rgb[i]=rand()%256;
      }
      QColor color(rgb[0], rgb[1], rgb[2]);
      return color;
}


PoolGraphItem::PoolGraphItem(QWidget *parent, PoolInterface *pool) :
    QWidget(parent),
    pool_(pool),
    ui(new Ui::PoolGraphItem)

{
    ui->setupUi(this);
    epochs = QVector<double>(0);
    inventory_quantities = std::unordered_map<Token*, QVector<double> >();
    token_to_graph = std::unordered_map< Token*, QCPGraph* > ();
    for (auto token: pool_->tokens()){
        token_to_graph[token] = ui->widget->addGraph();
        token_to_graph[token]->setName(QString::fromStdString(token->name()));
        token_to_graph[token]->setPen(QPen(QBrush(QColor(random_color())), 2));
    }
    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);


}

void PoolGraphItem::UpdateGraph(){
    epochs.push_back(epochs.size());
    for(auto [token, quantity]: pool_->quantities()){
        inventory_quantities[token].push_back(quantity);
        token_to_graph[token]->setData(epochs, inventory_quantities[token]);
        token_to_graph[token]->rescaleAxes(true);
    }

    // give the axes some labels:
    ui->widget->xAxis->setLabel("Epochs");
    ui->widget->yAxis->setLabel("Quantity");
    ui->widget->legend->setVisible(true);
    ui->widget->replot();
}

PoolGraphItem::~PoolGraphItem()
{
    delete ui;
}
