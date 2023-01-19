#ifndef NEWMAINWINDOW_H
#define NEWMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class NewMainWindow;
}

class NewMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewMainWindow(QWidget *parent = nullptr);
    ~NewMainWindow();

private slots:

    void on_pushButton_addManualPlayground_clicked();

    void on_pushButton_addSimulation_clicked();

    void on_tabWidget_tabCloseRequested(int index);

private:
    Ui::NewMainWindow *ui;
    int manualPlaygroundCount = 1;
    int simulationPlaygroundCount = 1;
};

#endif // NEWMAINWINDOW_H
