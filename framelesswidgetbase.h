#pragma once
#include <QWidget>

class FrameLessWidgetBase :
                             public QWidget
{
public:
    FrameLessWidgetBase(QWidget* p = nullptr);
    ~FrameLessWidgetBase() {}

protected:

private:
         // QWidget interface
protected:
    virtual bool nativeEvent(const QByteArray &eventType, void *message, qintptr *result) override;
};



