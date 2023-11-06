#ifndef BTNOPENFILE_H
#define BTNOPENFILE_H

#include <QWidget>
#include <QPushButton>


class BtnOpenFile : public QWidget
{
    Q_OBJECT
public:
    explicit BtnOpenFile(QWidget *parent = nullptr);
private slots:
    void on_openFile();
    void on_OpenFloder();

signals:
    void sig_openFile(const QStringList& fileList);
    void sig_OpenFloder(QString path);
private:
    QPushButton *m_pBtnOpenFile=nullptr;
    QPushButton *m_pBtnArrow=nullptr;
    int m_totalWidth=0;
    // QObject interface
protected:
    virtual bool eventFilter(QObject *watched, QEvent *event) override;

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;
};


#endif // BTNOPENFILE_H
