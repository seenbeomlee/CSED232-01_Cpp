#include "widgets/mainwindowwidget.h"
#include "ui_mainwindowwidget.h"

using namespace as4::model;

MainWindowWidget::MainWindowWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowWidget)
{
    ui->setupUi(this);

    for(int i = 0; i < 16; i++) // Qtablewidget에 색깔을 넣었다 뺄 수 있도록, QtabelwidgetItem을 넣어준다.
        for(int j = 0; j < 40; j++)
        {
            QTableWidgetItem* a = new QTableWidgetItem;
            a->setBackgroundColor(Qt::white);
            ui->tableWidget->setItem(i,j, a);
        }

    for(int i = 0; i < 16; i++)// Qtablewidget_2에 색깔을 넣었다 뺄 수 있도록, QtabelwidgetItem을 넣어준다.
        for(int j = 0; j < 40; j++)
        {
            QTableWidgetItem* a = new QTableWidgetItem;
            a->setBackgroundColor(Qt::white);
            ui->tableWidget_2->setItem(i,j, a);
        }

    ui->tableWidget->horizontalHeader()->setMinimumSectionSize(10); // Qtablewidget의 크기를 조정한다
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(17); // Qtablewidget의 크기를 조정한다
    ui->tableWidget_2->horizontalHeader()->setMinimumSectionSize(10);
    ui->tableWidget_2->horizontalHeader()->setDefaultSectionSize(17);


}

MainWindowWidget::~MainWindowWidget()
{
    delete ui;
}

void MainWindowWidget::on_tableWidget_cellPressed(int row, int column) // row column 은 맨 위 왼쪽에서부터 0,0으로 시작한다
{
    QTableWidgetItem *w;
    QBrush t(Qt::green);

    w = ui->tableWidget->item(row, column);

    if(t.color() != w->backgroundColor()) // 초록색으로 칠해진 공간이 아닐 때 (note 존재 x)
    {
        if(column == 39)
        {
            for(int i = 0; i < 1; i++)
            {
                QTableWidgetItem* a = new QTableWidgetItem;
                a->setBackgroundColor(Qt::green);
                ui->tableWidget->setItem(row, column+i, a);
            }
            return;
        }

        if(column == 38)
        {
            for(int i = 0; i < 2; i++)
            {
                QTableWidgetItem* a = new QTableWidgetItem;
                a->setBackgroundColor(Qt::green);
                ui->tableWidget->setItem(row, column+i, a);
            }
            return;
        }

        if(column == 37)
        {
            for(int i = 0; i < 3; i++)
            {
                QTableWidgetItem* a = new QTableWidgetItem;
                a->setBackgroundColor(Qt::green);
                ui->tableWidget->setItem(row, column+i, a);
            }
            return;
        }

        else {
            for(int i = 0; i < 4; i++)
            {
                QTableWidgetItem* a = new QTableWidgetItem;
                a->setBackgroundColor(Qt::green);
                ui->tableWidget->setItem(row, column+i, a);
            }
        }
        return;
    }

    if(t.color() == w->backgroundColor()) // 이미 초록색으로 색칠되어진 공간일 때 (note 존재)
    {
        int c1 = 1;
        int c2 = 1;

        QTableWidgetItem* g = new QTableWidgetItem;
        g->setBackgroundColor(Qt::white);
        ui->tableWidget->setItem(row, column, g);

        while(1) // 이어져있는 왼쪽 다 흰색으로 바꿔주기
        {
            if(column - c1 < 0)
                break;

            QTableWidgetItem* cc1;
            cc1 = ui->tableWidget->item(row, column - c1);

            if(t.color() == cc1->backgroundColor()) {
            cc1->setBackgroundColor(Qt::white);
            //ui->tableWidget->setItem(row, column - c1 , cc1); 쓰면안됨

            c1++;
            }

            else
                break;
        }

        while(1) // 이어져있는 오른쪽 다 흰색으로 바꿔주기
        {
            if(column + c2 > 39)
                break;

            QTableWidgetItem* cc2;
            cc2 = ui->tableWidget->item(row, column + c2);

            if(t.color() == cc2->backgroundColor()) {
            cc2->setBackgroundColor(Qt::white);
            // ui->tableWidget->setItem(row, column + c2 , cc2); 쓰면안됨

            c2++;
            }

            else
                break;
        }


        return;
    }
}

void MainWindowWidget::on_tableWidget_2_cellPressed(int row, int column)
{
    QTableWidgetItem *w;
    QBrush t(Qt::green);

    w = ui->tableWidget_2->item(row, column);

    if(t.color() != w->backgroundColor()) // 초록색으로 칠해진 공간이 아닐 때 (note 존재 x)
    {
        if(column == 39)
        {
            for(int i = 0; i < 1; i++)
            {
                QTableWidgetItem* a = new QTableWidgetItem;
                a->setBackgroundColor(Qt::green);
                ui->tableWidget_2->setItem(row, column+i, a);
            }
            return;
        }

        if(column == 38)
        {
            for(int i = 0; i < 2; i++)
            {
                QTableWidgetItem* a = new QTableWidgetItem;
                a->setBackgroundColor(Qt::green);
                ui->tableWidget_2->setItem(row, column+i, a);
            }
            return;
        }

        if(column == 37)
        {
            for(int i = 0; i < 3; i++)
            {
                QTableWidgetItem* a = new QTableWidgetItem;
                a->setBackgroundColor(Qt::green);
                ui->tableWidget_2->setItem(row, column+i, a);
            }
            return;
        }

        else {
            for(int i = 0; i < 4; i++)
            {
                QTableWidgetItem* a = new QTableWidgetItem;
                a->setBackgroundColor(Qt::green);
                ui->tableWidget_2->setItem(row, column+i, a);
            }
        }
        return;
    }

    if(t.color() == w->backgroundColor()) // 이미 초록색으로 색칠되어진 공간일 때 (note 존재)
    {
        int c1 = 1;
        int c2 = 1;

        QTableWidgetItem* g = new QTableWidgetItem;
        g->setBackgroundColor(Qt::white);
        ui->tableWidget_2->setItem(row, column, g);

        while(1) // 이어져있는 왼쪽 다 흰색으로 바꿔주기
        {
            if(column - c1 < 0)
                break;

            QTableWidgetItem* cc1;
            cc1 = ui->tableWidget_2->item(row, column - c1);

            if(t.color() == cc1->backgroundColor()) {
            cc1->setBackgroundColor(Qt::white);
            //ui->tableWidget->setItem(row, column - c1 , cc1); 쓰면안됨

            c1++;
            }

            else
                break;
        }

        while(1) // 이어져있는 오른쪽 다 흰색으로 바꿔주기
        {
            if(column + c2 > 39)
                break;

            QTableWidgetItem* cc2;
            cc2 = ui->tableWidget_2->item(row, column + c2);

            if(t.color() == cc2->backgroundColor()) {
            cc2->setBackgroundColor(Qt::white);
            // ui->tableWidget->setItem(row, column + c2 , cc2); 쓰면안됨

            c2++;
            }

            else
                break;
        }


        return;
    }
}


void MainWindowWidget::on_button_Play1_clicked() // Melodytrack player
{
    QTableWidgetItem* check;
    QBrush t(Qt::green);

    int j = 0;

    Melodytrack* mel = new Melodytrack;

    for(int i = 0; i < 12; i++)
    {
        while(j < 40)
        {
            check = ui->tableWidget->item(i, j);

            if(t.color() == check->backgroundColor())
            {
                (mel->get_melody_seq())->Put({125ULL*j, 500, {i, 4}}); // 초록색으로 칠해져 있는 note의 시작부분을 받으면, Note를 추가한다.
                j += 3;
            } // column이 0 이면 0초, n이면 125n

            j++;
        }
        j = 0;
    }

    for(int i = 12; i < 16; i++)
    {
        while(j < 40)
        {
            check = ui->tableWidget->item(i, j);

            if(t.color() == check->backgroundColor())
            {
                (mel->get_melody_seq())->Put({125ULL*j, 500, {i-12, 5}}); // 초록색으로 칠해져 있는 note의 시작부분을 받으면, Note를 추가한다.
                j += 3;
            } // column이 0 이면 0초, n이면 125n

            j++;
        }
        j = 0;
     }

    //이러면 mel의 ISeq* melody_seq에는 melody table의 모든 note가 들어가있다.
    mel->play();
}

#include <QDebug>
#include <QString>
void MainWindowWidget::on_button_Play2_clicked() // Drumtrack Player
{
    QTableWidgetItem* check;
    QBrush t(Qt::green);

    int j = 0;

    Drumtrack* mel = new Drumtrack;

    for(int i = 0; i < 12; i++)
    {
        while(j < 40)
        {
            check = ui->tableWidget_2->item(i, j);

            if(t.color() == check->backgroundColor())
            {
                (mel->get_Drum_seq())->Put({125ULL*j, 2000, {i, 4}});
                j += 3;
            } // column이 0 이면 0초, n이면 125n

            j++;
        }
        j = 0;
    }

    for(int i = 12; i < 16; i++)
    {
        while(j < 40)
        {
            check = ui->tableWidget_2->item(i, j);

            if(t.color() == check->backgroundColor())
            {
                (mel->get_Drum_seq())->Put({125ULL*j, 2000, {i-12, 5}});
                j += 3;
            } // column이 0 이면 0초, n이면 125n

            j++;
        }
        j = 0;
     }

    //이러면 mel의 ISeq* melody_seq에는 melody table의 모든 note가 들어가있다.
    mel->play();

}
