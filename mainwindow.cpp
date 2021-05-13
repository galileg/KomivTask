#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"mypainter.h"
#include"graph.h"
#include<string>
#include<vector>
#include<iostream>
#include <QPainter>
#include <QGridLayout>
#include <QPushButton>
#include "myglwidget.h"
using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    string str;
    ui->setupUi(this);
    vector<int>a = Kommivoyajer();
    for (int i=0; i<a.size();i++)
    {
        str+=to_string(a[i])+" ";
    }
    ui->lineEdit->setText(QString::fromStdString(str));
    myGLWidget *openGLW=new myGLWidget(this);
    QGridLayout *grid=new QGridLayout();
    QPushButton *btn=new QPushButton();
    grid->addWidget(openGLW,0,0);
    grid->addWidget(btn,1,0);
    ui->centralwidget->setLayout(grid);
    connect(btn,&QPushButton::clicked,openGLW,&myGLWidget::redraw);



}

MainWindow::~MainWindow()
{
    delete ui;
}

