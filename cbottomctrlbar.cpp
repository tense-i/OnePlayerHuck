#include "cbottomctrlbar.h"

CBottomCtrlBar::CBottomCtrlBar(QWidget *parent)
    : QWidget{parent}
{
    //禁止父窗口影响子窗口样式
    setAttribute(Qt::WA_StyledBackground);
    setMouseTracking(true);

    this->setFixedHeight(80);

    setStyleSheet("background-color:rgb(67,67,67)");

}

CBottomCtrlBar::~CBottomCtrlBar()
{

}
