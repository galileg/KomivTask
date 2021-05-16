#include "mypainter.h"
#include <QPaintEvent>
#include <QPainter>
#include <QWidget>
#include <QtCore/qmath.h>
#include<vector>
#include <QFile>
#include <QTextStream>
#include <QProcess>
#include<algorithm>
#include<fstream>
#include<string>

using namespace std;


int len = 6;
int R=300;        //радиус графа
int r=40;         //радиус узла
double pi=3.1415;
int HeightText=23;
int xa=600;       //отступ от вертикали
int ya=400;       //отступ от горизонтали
double angle=pi/8;//угол раствора стрелки
int ls=30;        //длина кончика стрелки
int disp=40;      //разброс подписей ребер
vector<vector<int>> mat={ {0 ,12 ,18,5,0 ,34 },
                   {0 ,0 ,16 ,0 ,53 ,45 },
                   {0 ,0 ,0 ,3 ,21,0 },
                   {0 ,0 ,0 ,0 ,0 ,0 },
                   {0 ,0,0 ,0,0 ,0 },
                   {0,0 ,0 ,0 ,0 ,0 } };





myPainter::myPainter()
{
    front=QBrush(QColor(255,0,50));
    back=QBrush(QColor(247, 0, 255));
    textPen=QPen(QColor(33,33,33));
    glFont.setPixelSize(HeightText);
}
void myPainter::draw(QPainter *painter, QPaintEvent *event)
{
    painter->fillRect(event->rect(),back);
    painter->setBrush(front);
    painter->setPen(textPen);
    painter->setFont(glFont);
    textPen.setWidth(4);

    for (int i=0;i<len;i++)
    {
        double a=pi*3/2+pi*2/len*i; //угол в полярных координатах (узел)
        int xc=cos(a)*R+xa;         //декартовы координата узла
        int yc=sin(a)*R+ya;
        int c1=xc-20;               //координаты текста
        int c2=yc-HeightText/2;
        int c3=40;
        int c4=HeightText;
        QString text; text.setNum(i+1);
        painter->drawEllipse(QRectF(xc-r,yc-r,2*r,2*r));
        painter->drawText(QRect(c1,c2,c3,c4),Qt::AlignCenter,text);

        for (int k=0;k<len;k++)
        {
            if (mat[i][k]!=0)
            {
                //линия
                double a2=pi*3/2+pi*2/len*k;
                double xc2=cos(a2)*R+xa;
                double yc2=sin(a2)*R+ya;
                double l=sqrt((xc2-xc)*(xc2-xc)+(yc2-yc)*(yc2-yc));
                int xl1=(xc2-xc)/l*r+xc;
                int yl1=(yc2-yc)/l*r+yc;
                int xl2=xc2-(xc2-xc)/l*r;
                int yl2=yc2-(yc2-yc)/l*r;
                painter->drawLine(xl1,yl1,xl2,yl2);
                painter->drawLine(0,0,0,0);
                painter->drawLine(0,0,0,0);

                //текст
                c1=(xl2+xl1)/2-30+qrand()%disp-disp/2;
                c2=(yl2+yl1)/2-HeightText/2+qrand()%disp-disp/2;
                c3=40;
                c4=HeightText;
                text.setNum(mat[i][k]);
                painter->drawText(QRect(c1,c2,c3,c4),Qt::AlignCenter, text);


            }
        }
    }
}
