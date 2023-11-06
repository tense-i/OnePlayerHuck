#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "videowidget.h"
#include "cbottomctrlbar.h"
#include "titlebar.h"

#include <memory>
#include "crightplaylist.h"
#include "framelesswidgetbase.h"
#include "cvlckits.h"

class Widget : public FrameLessWidgetBase
{
    Q_OBJECT
private:
   TitleBar* m_pTitleBar=nullptr;
    VideoWidget* m_pVideoWidget=nullptr;
   CBottomCtrlBar* m_pBottomCtrlBar=nullptr;
    CRightPlayList* m_pRightPlayList=nullptr;
private:
    void initUI();
private slots:
    void on_closed();
    void onTimeSliderMoved(int value);
    void onOpenFile(const QStringList &fileList);
    void onPlay();

private:
    std::unique_ptr<cVlcKits> m_pVlc;
    bool m_isPlay=false;


public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    // QWidget interface
protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
};



#endif // WIDGET_H
