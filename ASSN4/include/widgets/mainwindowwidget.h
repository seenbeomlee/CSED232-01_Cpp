#ifndef MAINWINDOWWIDGET_H
#define MAINWINDOWWIDGET_H

#include <QMainWindow>
#include "model/song.h"

namespace Ui {
class MainWindowWidget;
}

class MainWindowWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowWidget(QWidget *parent = nullptr);
    ~MainWindowWidget();

private slots:

    void on_tableWidget_cellPressed(int row, int column);

    void on_tableWidget_2_cellPressed(int row, int column);

    void on_button_Play1_clicked();

    void on_button_Play2_clicked();

private:
    Ui::MainWindowWidget *ui;

};

#endif
