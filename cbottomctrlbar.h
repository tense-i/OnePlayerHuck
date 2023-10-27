#ifndef CBOTTOMCTRLBAR_H
#define CBOTTOMCTRLBAR_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "playbtngroupwidget.h"

class CBottomCtrlBar : public QWidget
{
    Q_OBJECT
public:
    explicit CBottomCtrlBar(QWidget *parent = nullptr);
    ~CBottomCtrlBar();
public:
    void showTimeLabel(bool isShow);
    void shetCurPlayTime(const qint64&curMs);
    void setTotalTime(const qint64 &totalMs);
private:
    QString formatTimeMs(const qint64& timeMs);


signals:
    void sig_play();
    void sig_stop();
    void sig_fullScreen();
private:
    QLabel* m_pLabCurPlayTime = nullptr;
    QLabel* m_pLabTotalTime = nullptr;
    PlayBtnGroupWidget*m_pPlayBtnWidget=nullptr;
    QPushButton* m_pBtnToolBox = nullptr;
    QPushButton* m_pBtnEffect = nullptr;
    QPushButton* m_pBtnFullscreen = nullptr;

    // QWidget interface
protected:
    virtual void resizeEvent(QResizeEvent *event) override;
};



#endif // CBOTTOMCTRLBAR_H
