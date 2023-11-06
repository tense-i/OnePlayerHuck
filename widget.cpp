#include "widget.h"
#include "videowidget.h"
#include "cbottomctrlbar.h"
#include "titlebar.h"

#include "framelesswidgetbase.h"
#include <windows.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "cvlckits.h"
#include <QMessageBox>
#include <QKeyEvent>


BOOL CALLBACK EnumVLC(HWND hwnd,LPARAM lParam)
{
    TCHAR szTitle[1024];
    int nLen= GetWindowTextW(hwnd,szTitle,1024);
    if(nLen>0)
    {
        EnableWindow(hwnd,FALSE);
        KillTimer(hwnd,1);
    }
    return TRUE;
}
void  CALLBACK TimeProc(HWND hwnd, UINT msg, UINT_PTR id, DWORD time)
{
    HWND hwnd2=FindWindowEx(nullptr,nullptr,nullptr,L"vlcMain");
    if(hwnd2)
    {
        EnumChildWindows(hwnd2,EnumVLC,NULL);
    }
}


Widget::Widget(QWidget *parent)
    : FrameLessWidgetBase(parent)
{

    this->setWindowTitle("vlcmain");
    setMouseTracking(true);
    m_pVlc.reset(new cVlcKits());

    int nRet = m_pVlc->initVLC();

    switch (nRet)
    {
    case -1:
        QMessageBox::information(this, u8"提示", u8"libvlc_new failed");
        exit(EXIT_FAILURE);

    case -2:
        QMessageBox::information(this, u8"提示", u8"libvlc_media_player_new failed");
        exit(EXIT_FAILURE);
    }

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

    connect(m_pTitleBar, &TitleBar::sig_close, this, &Widget::on_closed);
    connect(m_pVideoWidget, &VideoWidget::sig_OpenFile, this, &Widget::onOpenFile);
    connect(m_pVideoWidget, &VideoWidget::sig_SliderMoved, this, &Widget::onTimeSliderMoved);
    connect(m_pBottomCtrlBar, &CBottomCtrlBar::sig_play, this, &Widget::onPlay);


}

void Widget::on_closed()
{
    QMessageBox::StandardButton _exit = QMessageBox::warning(this, u8"提示", u8"确定要退出吗",
        QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

    if (_exit == QMessageBox::Yes)
    {
        close();
    }
}

void Widget::onTimeSliderMoved(int value)
{
    m_pVlc->setVideoPos(value);
}

void Widget::onOpenFile(const QStringList &fileList)
{
    if (fileList.isEmpty())
        return;
    void* hwnd=(void*)m_pVideoWidget->winId();
    if( m_pVlc->play(fileList,hwnd)==-1)
    {
        QMessageBox::information(this,"提示","播放失败");
        exit(EXIT_FAILURE);
    }

    SetTimer(nullptr,1,300,TimeProc);
    m_pVideoWidget->setPlayStatus(true);
    m_isPlay=true;

}

void Widget::onPlay()
{
    m_pVlc->playing();
}

void Widget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (this->isFullScreen())
    {
        this->showNormal();
    }
    else
    {
        this->showFullScreen();
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    // 获取视频窗口的绝对位置
    QPoint p1 = m_pVideoWidget->mapToGlobal(QPoint(0, 0));
    QRect rect = m_pVideoWidget->rect();

    // 绝对矩形区域
    QRect rect2(p1.x(), p1.y(), rect.width(), rect.height());

    // 鼠标的绝对位置
    QPoint p2 = QCursor::pos();

    if (m_isPlay)
    {
        if (rect2.contains(p2))
        {

            m_pVideoWidget->showTopWidget(true);
        }
        else
        {
            m_pVideoWidget->showTopWidget(false);
        }
    }
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        if (this->isFullScreen())
        {
            this->showNormal();
        }
    }
}

