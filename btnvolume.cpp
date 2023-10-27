#include "btnvolume.h"
#include <QStylePainter>
#include <qpoint.h>
#include <qrect.h>
#include <QStyleOptionButton>
#include "dlgvolumesilder.h"
#include <QMouseEvent>


BtnVolume::BtnVolume(QWidget*parent):
    QPushButton(parent)
{

    setStyleSheet("QPushButton{background-image:url(:/playctrlBar/resources/playctrlBar/audio_open.svg);border:none;}"
                  "QPushButton:hover{background-image:url(:/playctrlBar/resources/playctrlBar/audio_open_hover.svg);border:none;}"
                  "QPushButton:pressed{background-image:url(:/playctrlBar/resources/playctrlBar/audio_open.svg);border:none;}");

}

void BtnVolume::setMute(bool mute)
{
    m_isMute=mute;

}

bool BtnVolume::getMute() const
{
    return m_isMute;
}

/*
 *
 *
 *
 * @brief
 * 用定时器模拟leaveEvent，直接在leaveEvent里让m_pVolumeSliderDlg消失，效果不太好，用鼠标移动事件也不太好，定时器是比较好的做法
 *
 * */

void BtnVolume::timerEvent(QTimerEvent *event)
{
    if(m_pDlgVolumeSlider&&m_pDlgVolumeSlider->isVisible())
    {
        //鼠标绝对位置
        QPoint p1=QCursor::pos();

        QRect rect1=this->rect();
        QRect rect2=m_pDlgVolumeSlider->rect();
        QRect rect3=m_pDlgVolumeSlider->geometry();
         //声音按钮左上角相对于桌面的绝对位置
        QPoint p2=this->mapToGlobal(QPoint(0,0));

        //已知音量框宽40>按钮30
        QRect area(rect3.left(),rect3.top(),rect2.width(),p2.y()+rect1.height()-rect3.top());

        if(!area.contains(p1))
        {
            m_pDlgVolumeSlider->hide();
        }
    }
    else
    {
        killTimer(event->timerId());
    }
}

void BtnVolume::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        m_isMute=!m_isMute;

        if(m_isMute)
        {
            if(m_pDlgVolumeSlider)
            {
                m_pDlgVolumeSlider->setSliderValue(0);

            }
        }
        else if(m_pDlgVolumeSlider)
        {
            m_pDlgVolumeSlider->setSliderValue(50);
        }
    }
}

void BtnVolume::enterEvent(QEnterEvent *event)
{
    if(!m_pDlgVolumeSlider)
    {
        m_pDlgVolumeSlider=new DlgVolumeSilder(this);
    }

    //声音按钮左上角相对与桌面的绝对位置
    QPoint p1=this->mapToGlobal(QPoint(0,0));

    //rect包含标题栏、去掉标题栏后height不变
    QRect rect1=this->rect();
    QRect rect2=m_pDlgVolumeSlider->rect();

    int x = p1.x() + (rect1.width() - rect2.width()) / 2;
    int y = p1.y() - rect2.height() - 5;
    m_pDlgVolumeSlider->move(x, y);   //move是相对于桌面原点的位置
    m_pDlgVolumeSlider->show();
    startTimer(250);

    connect(m_pDlgVolumeSlider,&DlgVolumeSilder::sig_slidervalueChanged,[=](int value){
        emit sig_VolumeValue(value);
    });
}

void BtnVolume::paintEvent(QPaintEvent *event)
{
    QStylePainter p(this);
    QStyleOptionButton option;
    initStyleOption(&option);
    p.drawControl(QStyle::CE_PushButton, option);
}

