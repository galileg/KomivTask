#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"secondwindow.h"
#include"mypainter.h"
#include<string>
#include<vector>
#include<iostream>
#include <QPainter>
#include <QGridLayout>
#include <QPushButton>
#include "myglwidget.h"
#include<QMessageBox>
using namespace std;



MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent),ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    myGLWidget *openGLW=new myGLWidget(this);
    QGridLayout *grid=new QGridLayout();

    grid->addWidget(openGLW,0,0);
    grid->addWidget(ui->pushButton,5,0);
    ui->centralwidget->setLayout(grid);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Secondwindow window;
    window.setModal(true);
    window.exec();
}





