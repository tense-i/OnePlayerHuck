#ifndef PLAYBTNGROUPWIDGET_H
#define PLAYBTNGROUPWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>

class BtnVolume;
class DlgVolumeSilder;

class PlayBtnGroupWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlayBtnGroupWidget(QWidget *parent = nullptr);
    ~PlayBtnGroupWidget();
signals:
    void sig_play();
    void sig_stop();
    void sig_next();
    void sig_prev();

private:
    QPushButton* m_pBtnStop = nullptr;
    QPushButton* m_pBtnPrev = nullptr;
    QPushButton* m_pBtnPlay = nullptr;
    QPushButton* m_pBtnNext = nullptr;
    BtnVolume*m_pBtnAudio=nullptr;
};

#endif // PLAYBTNGROUPWIDGET_H
