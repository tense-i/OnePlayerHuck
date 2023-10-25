#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "videowidget.h"
#include "cbottomctrlbar.h"
#include "titlebar.h"

#include <memory>
#include "crightplaylist.h"
#include "framelesswidgetbase.h"

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
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
};
#endif // WIDGET_H
