#ifndef TIMESLIDER_H
#define TIMESLIDER_H

#include <QSlider>
#include <QWidget>

class TimeSlider : public QSlider
{
    Q_OBJECT
public:
    TimeSlider(QWidget*parent= nullptr);
private:
    void slider_mouseLButtonPress(QObject*slider,QEvent*event);
    void setTimeSlideerRange(qint64 value);
    void setSliderValue(qint64 value);

private slots:
    void onSliderMoved(int pos);
signals:
    void sig_SliderMove(int value);
private:
    int m_bSliderPressed=false;
    int m_SliderHeight=15;

    // QObject interface
public:
    virtual bool eventFilter(QObject *watched, QEvent *event) override;
};


#endif // TIMESLIDER_H
