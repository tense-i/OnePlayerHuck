#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QObject>
#include <QWidget>

class VideoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VideoWidget(QWidget *parent = nullptr);
    ~VideoWidget();
    //十
private slots:

signals:

};

#endif // VIDEOWIDGET_H
