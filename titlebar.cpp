#include "titlebar.h"

#include <QHBoxLayout>
#include <QMenu>
#include <QPushButton>
#include <QLabel>
#include <qaction.h>

#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#include "myqss.h"



TitleBar::TitleBar(QWidget* p):
    QWidget(p)
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    initUI();
}

TitleBar::~TitleBar()
{

}

void TitleBar::initUI()
{
    //禁止父窗口影响子窗口样式
    setAttribute(Qt::WA_StyledBackground);
    this->setFixedHeight(32 + 5 * 2);
    this->setStyleSheet("background-color:rgb(54,54,54)");

    m_pLogoBtn = new QPushButton(this);
    m_pLogoBtn->setText("OnePlayerHuck");

    m_pLogoBtn->setFixedSize(145, 32);
    m_pLogoBtn->setStyleSheet(QString::fromStdString(logo_button_qss));

    QMenu*pMenu=new QMenu(this);
    pMenu->setStyleSheet(QString::fromStdString(menu_qss));

    QAction*pActOpenFile=new QAction(u8"打开文件",this);
    QAction*pActOpenDir=new QAction(u8"打开文件夹",this);
    QAction*pActSpecification=new QAction("开发说明",this);
    QAction *pActQuit=new QAction("退出",this);

    pMenu->addAction(pActOpenFile);
    pMenu->addAction(pActOpenDir);
    pMenu->addAction(pActSpecification);
    pMenu->addAction(pActQuit);

    m_pLogoBtn->setMenu(pMenu);

    m_pMinimodeBtn=new QPushButton(this);
    m_pMinimodeBtn->setFixedSize(32,32);
    m_pMinimodeBtn->setStyleSheet(QString::fromStdString(minimode_qss));

    m_pSetBtn = new QPushButton(this);
    m_pSetBtn->setFixedSize(32, 32);
    m_pSetBtn->setStyleSheet(QString::fromStdString(settop_qss));


    m_pMinBtn = new QPushButton(this);
    m_pMinBtn->setFixedSize(32, 32);
    m_pMinBtn->setStyleSheet(QString::fromStdString(min_qss));

    m_pMaxBtn = new QPushButton(this);
    m_pMaxBtn->setFixedSize(32, 32);
    m_pMaxBtn->setStyleSheet(QString::fromStdString(max_qss));

    m_pCloseBtn = new QPushButton(this);
    m_pCloseBtn->setFixedSize(32, 32);
    m_pCloseBtn->setStyleSheet(QString::fromStdString(close_qss));

    QHBoxLayout* pHlay = new QHBoxLayout(this);
    pHlay->addWidget(m_pLogoBtn);

    pHlay->addStretch();
    pHlay->addWidget(m_pMinimodeBtn);
    QSpacerItem*pItem=new QSpacerItem(20,20,QSizePolicy::Fixed,QSizePolicy::Fixed);
    pHlay->addSpacerItem(pItem);

    pHlay->addWidget(m_pSetBtn);
    QSpacerItem* pItem1 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
    pHlay->addSpacerItem(pItem1);

    pHlay->addWidget(m_pMinBtn);
    QSpacerItem* pItem2 = new QSpacerItem(18, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
    pHlay->addSpacerItem(pItem2);
    pHlay->addWidget(m_pMaxBtn);

    QSpacerItem* pItem3 = new QSpacerItem(18, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
    pHlay->addSpacerItem(pItem3);   // 弹簧每次使用时得new出来，不能重复使用
    pHlay->addWidget(m_pCloseBtn);

    pHlay->setContentsMargins(5, 5, 5, 5);

    connect(m_pMinBtn, &QPushButton::clicked, this, &TitleBar::onClicked);
    connect(m_pMaxBtn, &QPushButton::clicked, this, &TitleBar::onClicked);
    connect(m_pCloseBtn, &QPushButton::clicked, this, &TitleBar::onClicked);
}

void TitleBar::mousePressEvent(QMouseEvent* event)
{
    if (ReleaseCapture())
    {
        QWidget* pWindow = this->window();
        if (pWindow->isTopLevel())
        {
            SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
        }
    }
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent* event)
{
    emit m_pMaxBtn->clicked();
}

void TitleBar::onClicked()
{
     QPushButton* pButton = qobject_cast<QPushButton*>(sender());

     QWidget* pWindow = this->window();

     if (pButton == m_pMinBtn)
     {
         pWindow->showMinimized();
     }
     else if (pButton == m_pMaxBtn)
     {
         if (pWindow->isMaximized())
         {
             pWindow->showNormal();
             m_pMaxBtn->setStyleSheet("QPushButton{background-image:url(:/titleBar/resources/titleBar/normal.svg);border:none}" \
                 "QPushButton:hover{" \
                 "background-color:rgb(99, 99, 99);" \
                 "background-image:url(:/LessWidgetPro/resources/titlebar/normal_hover.svg);border:none;}");
         }
         else
         {
             pWindow->showMaximized();
             m_pMaxBtn->setStyleSheet("QPushButton{background-image:url(:/titleBar/resources/titleBar/max.svg}" \
                 "QPushButton:hover{" \
                 "background-color:rgb(99, 99, 99);" \
                 "background-image:url(:/titleBar/resources/titleBar/max_hover.svg);border:none;}");
         }
     }
     else if (pButton == m_pCloseBtn)
     {
         emit sig_close();
     }
}

