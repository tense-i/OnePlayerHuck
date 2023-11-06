#include "videowidget.h"
#include <QPainter>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMenu>
#include <QDebug>
#include <qt_windows.h>
#include <QApplication>
#include <QMessageBox>
#include <iostream>
#include "videowidgettopwidget.h"

#define TIME_SLIDER_HEIGHT   20

VideoWidget::VideoWidget(QWidget *parent)
    : QWidget{parent}
{
    setAttribute(Qt::WA_StyledBackground);
    this->setAttribute(Qt::WA_OpaquePaintEvent);
    qApp->installNativeEventFilter(this);
    setMouseTracking(true);

//设置渐变色
    this->setStyleSheet("QWidget{\
                       background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #09115C, stop:1 #000000 );\
                        font-family:Microsoft YaHei\
                         }");

    QString openfile_button_qss = "QPushButton::menu-indicator:open{"
        "image:url(:/titleBar/resources/titleBar/down_arrow.svg);"
        "subcontrol-position:right center;"
        "subcontrol-origin:padding;border:none;}"
        "QPushButton::menu-indicator:closed{"
        "image:url(:/titleBar/resources/titleBar/up_arrow.svg);"
        "subcontrol-position:right center;"
        "subcontrol-origin:padding;border:none;}";

    setMinimumSize(800, 450);

    m_pTopWidget = new vIdeoWidgetTopWidget(this);

    connect(m_pTopWidget, &vIdeoWidgetTopWidget::sig_OpenFile, this, &VideoWidget::sig_OpenFile);
    connect(m_pTopWidget, &vIdeoWidgetTopWidget::sig_OpenPalyList, this, &VideoWidget::sig_OpenPlayList);
    connect(m_pTopWidget, &vIdeoWidgetTopWidget::sig_SliderMove, this, &VideoWidget::onSliderMoved);

}

VideoWidget::~VideoWidget()
{

}

void VideoWidget::showTopWidget(bool show)
{
    if (show)
    {
        m_pTopWidget->show();
        m_pTopWidget->showOpenBtn(false);
        m_pTopWidget->showSlider(true);
    }
    else
    {
        m_pTopWidget->hide();
    }
}

void VideoWidget::setPlayStatus(bool play)
{
    m_isPlay=play;

}

void VideoWidget::onSliderMoved(int value)
{
    emit sig_SliderMoved(value);

}

void VideoWidget::resizeEvent(QResizeEvent *event)
{
    m_dPos = this->pos();

    QPoint pos = this->mapToGlobal(QPoint(0, 0));
    m_pTopWidget->resize(this->width(), this->height());
    m_pTopWidget->move(pos);
    m_pTopWidget->show();

}

bool VideoWidget::nativeEventFilter(const QByteArray &eventType, void *message, qintptr *result)
{
    if (eventType == "windows_generic_MSG" || eventType == "windows_dispatcher_MSG") {
        MSG* pMsg = reinterpret_cast<MSG*>(message);
        //cout << "msg id = " << pMsg->message << endl;
        if (pMsg->message == 1025) {
            QPoint pos = this->window()->mapToGlobal(QPoint(0, 0));
            //移动顶层控制窗口
            m_pTopWidget->move(pos + m_dPos);
        }
    }
    return false;
}


