#include "framelesswidgetbase.h"

#include <qt_windows.h>
#include <windows.h>
#include <windowsx.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib,"dwmapi.lib")

FrameLessWidgetBase::FrameLessWidgetBase(QWidget* p)
    :QWidget(p)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);
    setAttribute(Qt::WA_Hover);   //很重要
}

bool FrameLessWidgetBase::nativeEvent(const QByteArray &eventType, void *message, qintptr *result)
{
    MSG* msg = static_cast<MSG*>(message);
    if (msg->message == WM_NCHITTEST) {
        *result = 0;
        const int BORDER_WIDTH = 8; // 拉伸边框的宽度
        RECT winrect;
        GetWindowRect(reinterpret_cast<HWND>(winId()), &winrect);
        long x = GET_X_LPARAM(msg->lParam);
        long y = GET_Y_LPARAM(msg->lParam);
        // 判断鼠标位置是否在拉伸区域内
        if (y < winrect.top + BORDER_WIDTH) {
            *result = HTTOP;
        }
        if (y > winrect.bottom - BORDER_WIDTH) {
            *result = HTBOTTOM;
        }
        if (x < winrect.left + BORDER_WIDTH) {
            *result = HTLEFT;
        }
        if (x > winrect.right - BORDER_WIDTH) {
            *result = HTRIGHT;
        }
        if (y < winrect.top + BORDER_WIDTH && x < winrect.left + BORDER_WIDTH) {
            *result = HTTOPLEFT;
        }
        if (y < winrect.top + BORDER_WIDTH && x > winrect.right - BORDER_WIDTH) {
            *result = HTTOPRIGHT;
        }
        if (y > winrect.bottom - BORDER_WIDTH && x < winrect.left + BORDER_WIDTH) {
            *result = HTBOTTOMLEFT;
        }
        if (y > winrect.bottom - BORDER_WIDTH && x > winrect.right - BORDER_WIDTH) {
            *result = HTBOTTOMRIGHT;
        }
        if (*result != 0) {
            return true;
        }
    }
    return QWidget::nativeEvent(eventType, message, result);
}
