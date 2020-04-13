#ifndef __AS4_SONG_H
#define __AS4_SONG_H

#include <tuple>
#include "model/seq.h"

#include <QObject>
#include <QTimer>
#include <QSoundEffect>

namespace as4::model
{
    /**
     * Abstract)
     * A class that represents a song consisting of two tracks (DefaultSeq)
     *
     * Note)
     * We have a problem: This class can only use DefaultSeq as internal
     * representation.
     * We may resolve this problem after we learn templates later in the course.
     */
    class Song
    {
    public:
        // Don't delete pointers returned from these methods
        const DefaultSeq* GetMelodySeq() const;
        DefaultSeq* GetMelodySeq();
        const DefaultSeq* GetDrumSeq() const;
        DefaultSeq* GetDrumSeq();
        friend bool operator== (const Song& song1,const Song& song2);
    private:
        std::pair<DefaultSeq, DefaultSeq> m_seqs;
    };

    class Melodytrack : public QObject // melody에 대한 sequnece를 받아 출력할 때 사용하게 된다.
    {
        Q_OBJECT
    public:
        Melodytrack() {
                        melody_seq = new DefaultSeq;
                      }
        ~Melodytrack() = default;

        ISeq* get_melody_seq();
        void plus_current_time();
        void play();
        void startcheck();
        void removecheck();
        void set_size();
        void set_music();
    private:
        ISeq* melody_seq;
        Timestamp current_time = 0;
        QTimer* player;
        QSoundEffect** music;
        size_t size;

    private slots:
        void play_music();
    };


    class Drumtrack : public QObject // drum 에 대한 sequnece를 받아 출력할 때 사용하게 된다.
    {
        Q_OBJECT
    public:
        Drumtrack() {
                        Drum_seq = new DefaultSeq;
                      }
        ~Drumtrack() = default;

        ISeq* get_Drum_seq();
        void plus_current_time();
        void play();
        void startcheck();
        void removecheck();
        void set_size();
        void set_music();
    private:
        ISeq* Drum_seq;
        Timestamp current_time = 0;
        QTimer* player;
        QSoundEffect** music;
        size_t size;

    private slots:
        void play_music();
    };

}

#endif
