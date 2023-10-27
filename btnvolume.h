#ifndef BTNVOLUME_H
#define BTNVOLUME_H

#include <QPushButton>
#include <QObject>
#include <QWidget>

class DlgVolumeSilder;

class BtnVolume : public QPushButton
{
    Q_OBJECT
public:
    BtnVolume(QWidget*parent=nullptr);
signals:
    void sig_VolumeValue(int value);
public:
    void setMute(bool mute);
    bool getMute()const ;
private:
    bool m_isMute=false;
    DlgVolumeSilder* m_pDlgVolumeSlider=nullptr;

    // QObject interface
protected:
    virtual void timerEvent(QTimerEvent *event) override;

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void enterEvent(QEnterEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
};



#endif // BTNVOLUME_H
