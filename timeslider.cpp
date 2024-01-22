#include "timeslider.h"
#include <QEvent>
#include <QMouseEvent>
#include <QSlider>
#include <QPushButton>


TimeSlider::TimeSlider(QWidget *parent):QSlider(parent)
{
    setAttribute(Qt::WA_StyledBackground);

    this->setOrientation(Qt::Horizontal);
    this->setFixedHeight(m_SliderHeight);
    // 给事件滑动条安装事件，处理点击效果
    //事件过滤器、
    this->installEventFilter(this);

    QString slider_qss = "QSlider{background:transparent; \
                         border-style: outset; \
        border-style: outset;  \
        border-radius: 10px;} \
    QSlider::groove:horizontal{ \
        height: 12px; \
        background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4); \
        margin: 2px 0} \
    QSlider::handle:horizontal { \
        background: QRadialGradient(cx:0, cy:0, radius: 1, fx:0.5, fy:0.5, stop:0 white, stop:1 green); \
        width: 12px; \
        height: 12px; \
        margin: -5px 6px -5px 6px; \
        border-radius:11px;  \
        border: 3px solid #ffffff;}";

    QString qss = "QSlider{ \
      background-color:rgba(22, 22, 22, 0.7); \
    padding-top: 15px;  \
    padding-bottom: 15px; \
    border-radius: 5px;} \
    QSlider::add-page:horizontal{background-color: #FF7826;width:5px;border-radius: 2px;} \
    QSlider::sub-page:horizontal{background-color: #7A7B79;width:5px;border-radius: 2px;} \
    QSlider::groove:horizontal{background:transparent;width:6px;} \
    QSlider::handle:horizontal{height: 14px;width: 14px;margin: 0px -4px 0px -4px;border-radius: 7px;background: white;}";

    QString sqq = "QSlider::groove:horizontal{  \
        border: 1px solid #bbb; \
        background: white; \
        height: 4x;  border - radius: 2px; \
        left: 5px;right: 5px;}  \
    QSlider::add - page:horizontal{  \
        background: rgb(50,150,250); \
        border: 0px solid #777; \
        border - radius: 2px;}  \
    QSlider#videoSeekSlider::sub - page:horizontal{   \
        background: white;  \
        border - radius: 2px;}   \
    QSlider#videoSeekSlider::handle:horizontal{   \
        border: 0px;  \
        border - image: url(. / Resources / Image / ThemeOne / icon_slider_point.png);  \
        width: 16px;   \
        margin: -7px - 7px - 7px - 7px;}   \
    QSlider#videoVolumnSlider::groove:horizontal{  \
        border: 1px solid #bbb;background: white;  \
        height: 4x;border - radius: 2px;left: 5px;right: 5px;}";

    connect(this,&QSlider::sliderMoved,this,&TimeSlider::onSliderMoved);


}

void TimeSlider::slider_mouseLButtonPress(QObject *slider, QEvent *event)
{
    do
    {
        QSlider *pSliderctrl=static_cast<QSlider*>(slider);
        QMouseEvent *mouseEvent=static_cast<QMouseEvent*>(event);
        if(Qt::LeftButton!=mouseEvent->button())
        {
            break;
        }
        // 确定控件操作的基本参数
        int cxctl = 0;  // 滑块宽度
        int cxwnd = 0;  // 滑槽长度
        int mxpos = 0;  // 鼠标按下的位

        //滑块的方向是否为水平
        if(Qt::Horizontal==pSliderctrl->orientation())
        {
            //滑块的大小为滑动条最小的大小
            cxctl=pSliderctrl->minimumSizeHint().width();
            //滑动条的长度
            cxwnd=pSliderctrl->width();
            //是否为倒放

            //反着放
            if(pSliderctrl->invertedAppearance())
            {
                mxpos=cxwnd-mouseEvent->x();

            }//正着放
            else
                mxpos=mouseEvent->x();

        }//垂直的
        else
        {
            cxctl=pSliderctrl->minimumSizeHint().height();
            cxwnd=pSliderctrl->height();
            if(pSliderctrl->invertedAppearance())
            {
                mxpos=mouseEvent->y();
            }
            else
                mxpos=cxwnd-mouseEvent->y();
        }
        if(cxwnd<=cxctl)
            break;

        // 计算结果，并设置新计算得到的 position 值
        int scpos =pSliderctrl->minimum() +
                    (int)((pSliderctrl->maximum() - pSliderctrl->minimum()) *
                           ((mxpos - cxctl / 2.0) / (cxwnd - cxctl)));

        if (pSliderctrl->sliderPosition() == scpos)
        {
            break;
        }

        pSliderctrl->setSliderPosition(scpos);

    }while(0);

}

void TimeSlider::setTimeSlideerRange(qint64 value)
{
    this->setRange(0,value);

}

void TimeSlider::setSliderValue(qint64 value)
{
    this->setValue(value);

}

void TimeSlider::onSliderMoved(int pos)
{
    emit sig_SliderMove(pos);
}



bool TimeSlider::eventFilter(QObject *watched, QEvent *event)
{
    //若为当前窗口按下
    if(event->type()==QEvent::MouseButtonPress&&watched==this)
    {
        slider_mouseLButtonPress(watched,event);
    }
    return QWidget::eventFilter(watched,event);
}

