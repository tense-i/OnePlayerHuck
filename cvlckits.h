#ifndef CVLCKITS_H
#define CVLCKITS_H
#ifdef _WIN32
#include <basetsd.h>
typedef SSIZE_T ssize_t;
#endif
#include <QObject>
#include "vlc/vlc.h"
#include <vector>


class cVlcKits:public QObject
{
    Q_OBJECT
private:
    //libVlc实例
    libvlc_instance_t * m_pInstance=nullptr;
    //一个VLC播放器
    libvlc_media_player_t* m_pMediaPlayer = nullptr;
    //可播放的媒体
    libvlc_media_t* m_pMedia = nullptr;
    //事件管理
    libvlc_event_manager_t*m_pEvent_manager=nullptr;

    std::vector<libvlc_time_t> m_timeVector;

    //VLC播放器列表 一个视频一个VLC播放器
    libvlc_media_list_player_t*m_pMediaPlayerList;
    //vlc列表播放媒体
    libvlc_media_list_t*m_pMediaList;
    int curIndex=0;
    libvlc_time_t curDuration=0;
public:
    libvlc_time_t getCurDuration()  const;
    void setCurDuration(libvlc_time_t val);
    void addCurindex();
    int getCurIndex()const;
    std::vector<libvlc_time_t>& getTimeVector();
    libvlc_media_player_t* media_player()const;
    void setSliderSoundPos(int val);
    void setLabTime(const QString & text);
    void setVideoPos(int value);
public:
    int initVLC();
    void setTimeSliderPos(int val);
    int play(const QStringList& fileNames,void* hwndd);
    void playing();
    void pause();
    void stop();
signals:
    void sig_setTimeSliderPos(int val);
    void sig_setSliderSound(int val);
    void sig_setLabTime(const QString &text);
public:
    cVlcKits();
    ~cVlcKits();
};

#endif // CVLCKITS_H
