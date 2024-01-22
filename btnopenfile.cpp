#include "btnopenfile.h"
#include <QMenu>
#include <QHBoxLayout>
#include <qpainter.h>
#include <QEvent>
#include <QFileDialog>
#include <QSettings>
#include <QStandardPaths>


const int LEFT_BUTTON_WIDTH= 145;
const int  RIGHT_BUTTON_WIDTH =60;
const int  BUTTON_HEIGHT= 40;

BtnOpenFile::BtnOpenFile(QWidget *parent)
    : QWidget{parent}
{
    setAttribute(Qt::WA_StyledBackground);
    //设置总宽度
    m_totalWidth=LEFT_BUTTON_WIDTH+RIGHT_BUTTON_WIDTH;

    m_pBtnOpenFile=new QPushButton(this);
    m_pBtnOpenFile->setText("打开文件");
    m_pBtnOpenFile->setFixedSize(LEFT_BUTTON_WIDTH,BUTTON_HEIGHT);
    QString qssLeft=
        "QPushButton{"
        "padding-left:30px;"
        "border-top-left-radius:20px;border-bottom-left-radius:20px;"
        "background-color: rgb(55, 55, 55);"
        "color:rgb(255, 255, 255);"
        "text-align:left;"
        "}";
    m_pBtnOpenFile->setIcon(QIcon(":/videoWidge/resources/videoWidget/openfile.svg"));
    m_pBtnOpenFile->setLayoutDirection(Qt::LeftToRight);
    m_pBtnOpenFile->setStyleSheet(qssLeft);

    m_pBtnArrow=new QPushButton(this);
    m_pBtnArrow->setFixedSize(RIGHT_BUTTON_WIDTH,BUTTON_HEIGHT);
    QString qssRight= "QPushButton{"
                       "background-image: url(:/videoWidge/resources/videoWidget/vline.svg);"
                       "background-repeat: no-repeat;"
                       "background-origin: padding;"
                       "background-position: left;"
                       "border-top-right-radius:20px;border-bottom-right-radius:20px;"
                       "background-color: rgb(55, 55, 55);}"
                       "QPushButton::menu-indicator:open{"
                       "image:url(:/videoWidge/resources/videoWidget/down_arrow_16px.svg);"
                       "subcontrol-position:right center;right:10px;"
                       "subcontrol-origin:padding;border:none;}"
                       "QPushButton::menu-indicator:closed{"
                       "image:url(:/videoWidge/resources/videoWidget/down_arrow_16px.svg);"
                       "subcontrol-position:right center;right:10px;"
                       "subcontrol-origin:padding;border:none;}";
    m_pBtnArrow->setStyleSheet(qssRight);


    QString menu_qss = "QMenu{background-color:rgb(253,253,253);}"
                       "QMenu::item{"
                       "font:16px;"
                       "background-color:rgb(253,253,253);"
                       "padding:8px 32px;"
                       "margin:0px 8px;"
                       "border-bottom:1px solid #DBDBDB;}"
                       /*选择项设置*/
                       "QMenu::item:selected{background-color: #FFF8DC;}";

    QMenu *pMenu=new QMenu(this);
    pMenu->setFixedWidth(m_totalWidth);
    pMenu->setStyleSheet(menu_qss);

    QAction *pActOpenFile=new QAction("打开文件",this);
    QAction *pactOpenDir=new QAction("打开文件夹",this);
    pMenu->addAction(pActOpenFile);
    pMenu->addAction(pactOpenDir);
    m_pBtnArrow->setMenu(pMenu);
    pMenu->installEventFilter(this);
    QHBoxLayout* pHLay = new QHBoxLayout(this);
    pHLay->addWidget(m_pBtnOpenFile);
    pHLay->setSpacing(3);
    pHLay->addWidget(m_pBtnArrow);
    pHLay->setContentsMargins(0, 0, 0, 0);

    setLayout(pHLay);

    setFixedSize(m_totalWidth, BUTTON_HEIGHT);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);  //设置窗口背景透明, 为圆角窗口准备

    connect(m_pBtnOpenFile, &QPushButton::clicked, this, &BtnOpenFile::on_openFile);
    connect(pActOpenFile,&QAction::triggered,this,&BtnOpenFile::on_openFile);
    connect(pactOpenDir,&QAction::triggered,this,&BtnOpenFile::on_OpenFloder);

}


void BtnOpenFile::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  // 反锯齿
    painter.setBrush(QBrush(QColor(55, 55, 55)));
    painter.setPen(Qt::transparent);
    QRect rect = this->rect();
    painter.drawRoundedRect(rect, BUTTON_HEIGHT / 2, BUTTON_HEIGHT / 2);  //设置窗口圆角 15px

    QWidget::paintEvent(event);

}

void BtnOpenFile::on_openFile()
{
    QString cfgPath = "HKEY_CURRENT_USER\\Software\\MediaPlayer";
    QSettings settings(cfgPath, QSettings::NativeFormat);
    QString lastPath = settings.value("openfile_path").toString();  // 从注册表获取路径

    if (lastPath.isEmpty())
    {
        lastPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);  //获取默认的文档路径
    }

    //可以同时打开多个文件
    QStringList filelist = QFileDialog::getOpenFileNames(
        this,
        u8"选择要播放的文件",
        lastPath,
        u8"视频文件 (*.flv *.rmvb *.avi *.mp4);; 所有文件 (*.*);; ");

    if (filelist.isEmpty())
    {
        return;
    }

    int end = filelist[0].lastIndexOf("/");
    QString tmppath = filelist[0].left(end + 1);
    settings.setValue("openfile_path", tmppath);  // 将当前打开的路径写入到注册表

    emit sig_openFile(filelist);
}

void BtnOpenFile::on_OpenFloder()
{
    QString path = QFileDialog::getExistingDirectory(this, "choose src Directory", "/");

    if (path.isEmpty())
    {
        return;
    }

    emit sig_OpenFloder(path);
}

bool BtnOpenFile::eventFilter(QObject *watched, QEvent *event)
{
    if(m_pBtnArrow)
    {
        if (event->type() == QEvent::Show && watched == m_pBtnArrow->menu())
        {
            int menuXPos = m_pBtnArrow->menu()->pos().x() - LEFT_BUTTON_WIDTH;   //默认是显示在当前按钮的左下方
            int menuWidth = m_pBtnArrow->menu()->size().width();
            int buttonWidth = m_pBtnArrow->size().width();
            QPoint pos = QPoint(menuXPos, m_pBtnArrow->menu()->pos().y() + 2);

            m_pBtnArrow->menu()->move(pos);
            return true;
        }
    }
    return false;
}
