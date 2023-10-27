#include "playbtngroupwidget.h"
#include "btnvolume.h"
#include "QHBoxLayout"


PlayBtnGroupWidget::PlayBtnGroupWidget(QWidget *parent)
    : QWidget{parent}
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_StyledBackground);
    m_pBtnStop=new QPushButton(this);
    m_pBtnStop->setText("");
    m_pBtnStop->setFixedSize(32,32);
    m_pBtnStop->setStyleSheet("QPushButton{background-image:url(:/playctrlBar/resources/playctrlBar/stop.svg);border:none;}"
                              "QPushButton:hover{background-image:url(:/playctrlBar/resources/playctrlBar/stop_hover.svg);border:none;}"
                              "QPushButton:pressed{background-image:url(:/playctrlBar/resources/playctrlBar/stop.svg);border:none;}");

    m_pBtnPrev=new QPushButton(this);
    m_pBtnPrev->setText("");
    m_pBtnPrev->setFixedSize(32,32);
    m_pBtnPrev->setStyleSheet("QPushButton{background-image:url(:/playctrlBar/resources/playctrlBar/pre.svg);border:none;}"
                              "QPushButton:hover{background-image:url(:/playctrlBar/resources/playctrlBar/pre_hover.svg);border:none;}"
                              "QPushButton:pressed{background-image:url(:/playctrlBar/resources/playctrlBar/pre.svg);border:none;}");

    m_pBtnPlay=new QPushButton(this);
    m_pBtnPlay->setText("");
    m_pBtnPlay->setFixedSize(48,48);
    m_pBtnPlay->setStyleSheet("QPushButton{background-image:url(:/playctrlBar/resources/playctrlBar/play.svg);border:none;}"
                              "QPushButton:hover{background-image:url(:/playctrlBar/resources/playctrlBar/play_hover.svg);border:none;}"
                              "QPushButton:pressed{background-image:url(:/playctrlBar/resources/playctrlBar/play.svg);border:none;}");


    m_pBtnNext=new QPushButton(this);
    m_pBtnNext->setText("");
    m_pBtnNext->setFixedSize(32,32);
    m_pBtnNext->setStyleSheet("QPushButton{background-image:url(:/playctrlBar/resources/playctrlBar/next.svg);border:none;}"
                              "QPushButton:hover{background-image:url(:/playctrlBar/resources/playctrlBar/next_hover.svg);border:none;}"
                              "QPushButton:pressed{background-image:url(:/playctrlBar/resources/playctrlBar/next.svg);border:none;}");

    m_pBtnAudio=new BtnVolume(this);
    m_pBtnAudio->setText("");
    m_pBtnAudio->setFixedSize(32,32);

    QHBoxLayout* pHLay = new QHBoxLayout(this);
    pHLay->addWidget(m_pBtnStop);
    pHLay->setSpacing(8);
    pHLay->addWidget(m_pBtnPrev);
    pHLay->setSpacing(8);
    pHLay->addWidget(m_pBtnPlay);
    pHLay->setSpacing(8);
    pHLay->addWidget(m_pBtnNext);
    pHLay->setSpacing(8);
    pHLay->addWidget(m_pBtnAudio);
    pHLay->setContentsMargins(0, 0, 0, 0);

    setLayout(pHLay);

    setFixedSize(32 * 4 + 48 + 4 * 8 + 20 , 48);

    connect(m_pBtnPlay,&QPushButton::clicked,this,&PlayBtnGroupWidget::sig_play);
    connect(m_pBtnStop,&QPushButton::clicked,this,&PlayBtnGroupWidget::sig_stop);
    connect(m_pBtnPrev,&QPushButton::clicked,this,&PlayBtnGroupWidget::sig_play);
    connect(m_pBtnNext,&QPushButton::clicked,this,&PlayBtnGroupWidget::sig_next);

}

PlayBtnGroupWidget::~PlayBtnGroupWidget()
{

}
