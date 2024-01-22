#pragma once
#include <QWidget>
#include <QLabel>
#include <QPushButton>

class TitleBar : public QWidget
{
    Q_OBJECT

public:
    TitleBar(QWidget* p = nullptr);
    ~TitleBar();

private:
    void initUI();

private:
    //实现拖动效果
    void mousePressEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;

private slots:
    void onClicked();

signals:
    void sig_close();

private:
    QPushButton*m_pLogoBtn=nullptr;
    QPushButton *m_pMinimodeBtn=nullptr;
    QPushButton* m_pSetBtn;
    QPushButton* m_pMinBtn;
    QPushButton* m_pMaxBtn;
    QPushButton* m_pCloseBtn;
};

