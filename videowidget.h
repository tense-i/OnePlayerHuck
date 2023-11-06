#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>

#include <QSlider>
#include <QAbstractNativeEventFilter>

#include "videowidgettopwidget.h"

class VideoWidget : public QWidget,QAbstractNativeEventFilter
{
    Q_OBJECT
public:
    explicit VideoWidget(QWidget *parent = nullptr);
    ~VideoWidget();
public:
    void showTopWidget(bool show);
    void setPlayStatus(bool play);

private slots:
    void onSliderMoved(int value);

signals:
    void sig_OpenFile(const QStringList& fileList);
    void sig_OpenFloder(QString path);
    void sig_OpenPlayList();
    void sig_Totalms(const qint64& duration);   //发给主界面
    void sig_VideoPositionChanged(const qint64& pos);   //发给主界面
    void sig_SliderMoved(int value);
private:
    QPoint m_dPos;   //VideoWidget相对于父窗口的位置
    vIdeoWidgetTopWidget* m_pTopWidget = nullptr;
    bool m_isPlay = false;

    // QAbstractNativeEventFilter interface
public:
    virtual bool nativeEventFilter(const QByteArray &eventType, void *message, qintptr *result) override;

    // QWidget interface
protected:
    virtual void resizeEvent(QResizeEvent *event) override;
};



#endif // VIDEOWIDGET_H
