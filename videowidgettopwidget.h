#ifndef VIDEOWIDGETTOPWIDGET_H
#define VIDEOWIDGETTOPWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <btnopenfile.h>
#include <qslider.h>
#include <timeslider.h>

class vIdeoWidgetTopWidget : public QWidget
{
    Q_OBJECT
public:
    explicit vIdeoWidgetTopWidget(QWidget *parent = nullptr);
    //十
    void setTimeSliderRange(qint64 value);
    void setSliderValue(qint64 value);
    void showRightBtn(bool flag);
    void showOpenBtn(bool flag);
    void showSlider(bool flag);
    void setPlayStatus(bool play) { m_isPlay = play; }
private slots:
    void onSliderMoved(int pos);

private:
    QPushButton *m_pBtnOpenRight=nullptr;
    BtnOpenFile*m_pBtnFileOpen=nullptr;
    TimeSlider* m_pTimeSlider=nullptr;
    int m_bSliderPressed=false;
    bool m_isPlay=false;

signals:
    void sig_OpenFloder(QString path);
    void sig_OpenFile(const QStringList & fileList);
    void sig_OpenPalyList();
    void sig_SliderMove(int position);
    // QWidget interface
protected:
    virtual void resizeEvent(QResizeEvent *event) override;

};

#endif // VIDEOWIDGETTOPWIDGET_H
