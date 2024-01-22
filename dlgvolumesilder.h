#ifndef DLGVOLUMESILDER_H
#define DLGVOLUMESILDER_H
#include <QSlider>
#include <QPushButton>
#include <QObject>
#include <QWidget>
#include <QDialog>

class DlgVolumeSilder : public QDialog
{
    Q_OBJECT
public:
    DlgVolumeSilder(QWidget*parent=Q_NULLPTR);
public:
    void setSliderValue(int value);
private:
    QSlider* m_pSlider=nullptr;
signals:
   void sig_slidervalueChanged(int value);
    // QObject interface
public:
   virtual bool event(QEvent *event) override;
};



#endif // DLGVOLUMESILDER_H
