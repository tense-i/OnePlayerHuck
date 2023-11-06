#include "videowidgettopwidget.h"



#define TIME_SLIDER_HEIGHT   20

vIdeoWidgetTopWidget::vIdeoWidgetTopWidget(QWidget *parent)
    : QWidget{parent}
{
    //禁止父窗口影响子窗口样式
    setAttribute(Qt::WA_StyledBackground);
    this->setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint|Qt::Tool|Qt::SubWindow);
    setAutoFillBackground(true);
    setMinimumSize(800,450);
    setMouseTracking(true);

    m_pBtnFileOpen=new BtnOpenFile(this);
    m_pBtnOpenRight=new QPushButton(this);

    m_pBtnOpenRight->setText("");
    m_pBtnOpenRight->setFixedSize(36,80);

    m_pBtnOpenRight->setStyleSheet("QPushButton{background-color:rgb(54,54,54);background-image:url(:/videoWidge/resources/videoWidget/left_arrow.svg); \
        background-position:center; \
        padding-top: 24px; \
        background-repeat: no-repeat; \
        border:none;} \
        QPushButton:hover{background-image:url(:/videoWidge/resources/videoWidget/left_arrow_hover.svg);border:none;} \
        QPushButton:pressed{background-image:url(:/videoWidge/resources/videoWidget/left_arrow.svg);border:none;}");

    m_pTimeSlider=new TimeSlider(this);
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
        width: 16px; \
        height: 16px; \
        margin: -5px 6px -5px 6px; \
        border-radius:11px;  \
        border: 3px solid #ffffff;}";
    m_pTimeSlider->setStyleSheet(slider_qss);
    connect(m_pBtnFileOpen,&BtnOpenFile::sig_openFile,this,&vIdeoWidgetTopWidget::sig_OpenFile);
     connect(m_pBtnFileOpen,&BtnOpenFile::sig_OpenFloder,this,&vIdeoWidgetTopWidget::sig_OpenFloder);
    connect(m_pBtnOpenRight,&QPushButton::clicked,this,&vIdeoWidgetTopWidget::sig_OpenPalyList);
     connect(m_pTimeSlider,&QSlider::sliderMoved,this,&vIdeoWidgetTopWidget::onSliderMoved);

}



void vIdeoWidgetTopWidget::setTimeSliderRange(qint64 value)
{
    m_pTimeSlider->setRange(0,value);
}

void vIdeoWidgetTopWidget::setSliderValue(qint64 value)
{
    m_pTimeSlider->setValue(value);

}

void vIdeoWidgetTopWidget::showRightBtn(bool flag)
{
    flag?m_pBtnOpenRight->show():m_pBtnOpenRight->hide();
}

void vIdeoWidgetTopWidget::showOpenBtn(bool flag)
{
    flag?m_pBtnFileOpen->show():m_pBtnFileOpen->hide();
}

void vIdeoWidgetTopWidget::showSlider(bool flag)
{
    m_pTimeSlider->show();
}


void vIdeoWidgetTopWidget::resizeEvent(QResizeEvent *event)
{
    if (m_pBtnFileOpen && m_pBtnOpenRight && m_pTimeSlider)
    {
        int x1 = this->width() / 2 - m_pBtnFileOpen->width() / 2;
        int y1 = this->height() / 2 - m_pBtnFileOpen->height() / 2;
      m_pBtnFileOpen->move(x1, y1);

        int x2 = this->width() - m_pBtnOpenRight->width();
        int y2 = this->height() / 2 - m_pBtnOpenRight->height() / 2;
        m_pBtnOpenRight->move(x2, y2);

        int x3 = 0;
        int y3 = this->height() - TIME_SLIDER_HEIGHT;
        m_pTimeSlider->move(x3, y3);
        m_pTimeSlider->resize(this->width(), TIME_SLIDER_HEIGHT);
    }
}


void vIdeoWidgetTopWidget::onSliderMoved(int position)
{
    emit sig_SliderMove(position);
}
