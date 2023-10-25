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
    void mousePressEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;

private slots:
    void onClicked();

signals:
    void sig_close();

private:
    QLabel* m_pLogo;
    QLabel* m_pTitleTextLabel;

    QPushButton* m_pSetBtn;
    QPushButton* m_pMinBtn;
    QPushButton* m_pMaxBtn;
    QPushButton* m_pCloseBtn;
};
