#include "widget.h"
#include "videowidget.h"
#include "cbottomctrlbar.h"
#include "titlebar.h"

#include "framelesswidgetbase.h"

#include <QVBoxLayout>
#include <QHBoxLayout>


Widget::Widget(QWidget *parent)
    : FrameLessWidgetBase(parent)
{
    initUI();
    //关闭按钮
    connect(m_pTitleBar,&TitleBar::sig_close,[=](){
        this->close();
    });
}

Widget::~Widget()
{

}

void Widget::initUI()
{

    setStyleSheet("background-color:rgb(251,252,253)");

    m_pTitleBar=new TitleBar(this);
    m_pVideoWidget=new VideoWidget(this);
    m_pBottomCtrlBar=new CBottomCtrlBar(this);
    m_pRightPlayList=new CRightPlayList(this);
    //隐藏右侧按钮
    m_pRightPlayList->hide();
    QVBoxLayout *pMainVlayout=new QVBoxLayout(this);
    pMainVlayout->addWidget(m_pTitleBar);
    pMainVlayout->setSpacing(0);
    QHBoxLayout*pHLayout=new QHBoxLayout;
    pHLayout->addWidget(m_pVideoWidget);
    pHLayout->addWidget(m_pRightPlayList);
    pHLayout->setContentsMargins(0,0,0,0);
    pMainVlayout->addLayout(pHLayout);
    pMainVlayout->addWidget(m_pBottomCtrlBar);
    pMainVlayout->setContentsMargins(0,0,0,0);

}
