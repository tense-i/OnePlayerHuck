#include "videowidget.h"

VideoWidget::VideoWidget(QWidget *parent)
    : QWidget{parent}
{
    //禁止父窗口影响子窗口样式
    setAttribute(Qt::WA_StyledBackground);
    this->setMinimumSize(800,450);
    setStyleSheet("background-color:rgb(17,17,17)");
}

VideoWidget::~VideoWidget()
{

}
