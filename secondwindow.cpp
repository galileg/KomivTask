#include "secondwindow.h"
#include "ui_secondwindow.h"
#include"graph.h"

Secondwindow::Secondwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Secondwindow)
{
    ui->setupUi(this);
    string str1 = Kommivoyajer();
    int way = WAY_LONG();
    ui->lineEdit->setText(QString::fromStdString(str1));
    ui->lineEdit_2 ->setText(QString::number(way));
}

Secondwindow::~Secondwindow()
{
    delete ui;
}
