#include "cbottomctrlbar.h"
#include <QHBoxLayout>
#include "playbtngroupwidget.h"

CBottomCtrlBar::CBottomCtrlBar(QWidget *parent)
    : QWidget{parent}
{
    //禁止父窗口影响子窗口样式
    setAttribute(Qt::WA_StyledBackground);
    setMouseTracking(true);

    this->setFixedHeight(80);

    setStyleSheet("background-color:rgb(67,67,67)");

    QString label_qss = "QLabel{font-family:Microsoft YaHei; font-size:18px; color:rgb(255,255,255);}";

    m_pLabCurPlayTime=new QLabel(this);
    m_pLabCurPlayTime->setText("00:00:00");
    m_pLabCurPlayTime->setAlignment(Qt::AlignRight);
    m_pLabCurPlayTime->setFixedSize(80,32);
    m_pLabCurPlayTime->setStyleSheet(label_qss);

    m_pLabTotalTime=new QLabel(this);
    m_pLabTotalTime->setText("01:02:03");
    m_pLabTotalTime->setAlignment(Qt::AlignRight);
    m_pLabTotalTime->setFixedSize(160,32);
    m_pLabTotalTime->setStyleSheet(label_qss);

    m_pPlayBtnWidget=new PlayBtnGroupWidget(this);
    m_pBtnToolBox=new QPushButton(this);
    m_pBtnToolBox->setText("");
    m_pBtnToolBox->setFixedSize(32,32);
    m_pBtnToolBox->setStyleSheet("QPushButton{background-image:url(:/playctrlBar/resources/playctrlBar/toolbox.svg);border:none;}"
        "QPushButton:hover{background-image:url(:/playctrlBar/resources/playctrlBar/toolbox_hover.svg);border:none;}"
                                  "QPushButton:pressed{background-image:url(:/playctrlBar/resources/playctrlBar/toolbox.svg);border:none;}");
    m_pBtnEffect=new QPushButton(this);
    m_pBtnEffect->setText("");
    m_pBtnEffect->setFixedSize(32,32);
    m_pBtnEffect->setStyleSheet("QPushButton{background-image:url(:/playctrlBar/resources/playctrlBar/effect.svg);border:none;}"
                   "QPushButton:hover{background-image:url(:/playctrlBar/resources/playctrlBar/effect_hover.svg);border:none;}"
                   "QPushButton:pressed{background-image:url(:/playctrlBar/resources/playctrlBar/effect.svg);border:none;}");

    m_pBtnFullscreen=new QPushButton(this);
    m_pBtnFullscreen->setText("");
    m_pBtnFullscreen->setFixedSize(32,32);
   m_pBtnFullscreen ->setStyleSheet("QPushButton{background-image:url(:/playctrlBar/resources/playctrlBar/fullscreen.svg);border:none;}"
                    "QPushButton:hover{background-image:url(:/playctrlBar/resources/playctrlBar/fullscreen_hover.svg);border:none;}"
                    "QPushButton:pressed{background-image:url(:/playctrlBar/resources/playctrlBar/fullscreen.svg);border:none;}");

    QHBoxLayout*pHLay=new QHBoxLayout(this);
   pHLay->addSpacing(3);
    pHLay->addWidget(m_pLabCurPlayTime);
   pHLay->addSpacing(1);
   pHLay->addWidget(m_pLabTotalTime);
   pHLay->addStretch();
   pHLay->addWidget(m_pPlayBtnWidget);
   pHLay->addStretch();
   pHLay->addWidget(m_pBtnToolBox);
   pHLay->addSpacing(18);
   pHLay->addWidget(m_pBtnEffect);
   pHLay->addSpacing(18);
   pHLay->addWidget(m_pBtnFullscreen);

   showTimeLabel(false);

   connect(m_pPlayBtnWidget,&PlayBtnGroupWidget::sig_play,this,&CBottomCtrlBar::sig_play);
   connect(m_pPlayBtnWidget,&PlayBtnGroupWidget::sig_stop,this,&CBottomCtrlBar::sig_stop);
   connect(m_pBtnFullscreen,&QPushButton::clicked,this,&CBottomCtrlBar::sig_fullScreen);


}

CBottomCtrlBar::~CBottomCtrlBar()
{

}

void CBottomCtrlBar::showTimeLabel(bool isShow)
{
   if(isShow)
   {
       m_pLabCurPlayTime->show();
       m_pLabTotalTime->show();
   }
   else
   {
       m_pLabCurPlayTime->hide();
       m_pLabTotalTime->hide();
   }

}

void CBottomCtrlBar::shetCurPlayTime(const qint64 &curMs)
{
   m_pLabCurPlayTime->setText(formatTimeMs(curMs));
}

void CBottomCtrlBar::setTotalTime(const qint64 &totalMs)
{
   m_pLabTotalTime->setText("/"+formatTimeMs(totalMs));

}

QString CBottomCtrlBar::formatTimeMs(const qint64 &timeMs)
{
   qint64 seconds = timeMs / 1000;
   int hours = seconds / 3600;
   int mins = (seconds - hours * 3600) / 60;
   int secs = seconds - hours * 3600 - mins * 60;

   char buf[1024] = { 0 };
   if (hours < 100)
   {
       sprintf(buf, "%02d:%02d:%02d", hours, mins, secs);
   }
   else
   {
       sprintf(buf, "%d:%02d:%02d", hours, mins, secs);
   }

   return QString::fromUtf8(buf);
}


void CBottomCtrlBar::resizeEvent(QResizeEvent *event)
{
   if (m_pPlayBtnWidget)
   {
       int x = this->width() / 2 - m_pPlayBtnWidget->width() / 2;
       int y = this->height() / 2 - m_pPlayBtnWidget->height() / 2;
      m_pPlayBtnWidget->move(x, y);
   }
}
