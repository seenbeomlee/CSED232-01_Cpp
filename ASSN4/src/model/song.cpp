#include "model/song.h"

#include <QTimer>
#include <QSoundEffect>
#include <QDebug>

namespace as4::model
{
    const DefaultSeq *Song::GetMelodySeq() const
    {
        return &std::get<0>(m_seqs);
    }

    DefaultSeq *Song::GetMelodySeq()
    {
        return &std::get<0>(m_seqs);
    }

    const DefaultSeq *Song::GetDrumSeq() const
    {
        return &std::get<1>(m_seqs);
    }

    DefaultSeq *Song::GetDrumSeq()
    {
        return &std::get<1>(m_seqs);
    }

    bool operator== (const Song& song1,const Song& song2) { // == 오퍼레이터 연산자

                std::vector<Note*> temp1 = const_cast<Song&>(song1).GetMelodySeq()->GetOrdered();
                std::vector<Note*> temp2 = const_cast<Song&>(song2).GetMelodySeq()->GetOrdered();

                if(temp1.size() != temp2.size()) return false;

                for(size_t i = 0; i< temp1.size(); i++) {

                    if(*(temp1[i]) != *(temp2[i])) return false;
                }

                std::vector<Note*> temp3 = const_cast<Song&>(song1).GetDrumSeq()->GetOrdered();
                std::vector<Note*> temp4 = const_cast<Song&>(song2).GetDrumSeq()->GetOrdered();

                if(temp3.size() != temp4.size()) return false;

                for(size_t i = 0; i< temp3.size(); i++) {

                    if(*(temp3[i]) != *(temp4[i])) return false;
                }

                return true;
            }

    ISeq* Melodytrack::get_melody_seq() // melody_seq의 주솟값을 반환한다.
    {
        return melody_seq;
    }

    void Melodytrack::set_size() // seq에 존재하는 note 개수를 표현한다.
    {
        std::vector<Note*> temp = melody_seq->GetOrdered();
        size = temp.size();
        music = new QSoundEffect* [size];
    }

    void Melodytrack::set_music() // seq에 존재하는 Note에 맞는 .wav파일을 설정한다.
    {
        //QSoundEffect* music;

        std::vector<Note*> temp = melody_seq->GetOrdered();
        size_t size = temp.size();

        int seq_pitch_class, seq_otave;

        for(size_t i = 0; i < size; i++)
        {
            music[i] = new QSoundEffect ;
            seq_pitch_class = temp[i]->GetPitch().GetPitchClass();
            seq_otave = temp[i]->GetPitch().GetOctave();

            if(seq_pitch_class == 0 && seq_otave == 4)
            {
                music[i]->setSource(QUrl::fromLocalFile(QString::fromStdString("../audio/melody/0_4.wav")));
                music[i]->setVolume(0.50f);
            }
            if(seq_pitch_class == 0 && seq_otave == 5)
            {
                music[i]->setSource(QUrl::fromLocalFile(QString::fromStdString("../audio/melody/0_5.wav")));
                music[i]->setVolume(0.50f);
            }
            if(seq_pitch_class == 10 && seq_otave == 4)
            {
                music[i]->setSource(QUrl::fromLocalFile(QString::fromStdString("../audio/melody/10_4.wav")));
                music[i]->setVolume(0.50f);
            }
            if(seq_pitch_class == 11 && seq_otave == 4)
            {
                music[i]->setSource(QUrl::fromLocalFile(QString::fromStdString("../audio/melody/11_4.wav")));
                music[i]->setVolume(0.50f);
            }
            if(seq_pitch_class == 1 && seq_otave == 4)
            {
                music[i]->setSource(QUrl::fromLocalFile(QString::fromStdString("../audio/melody/1_4.wav")));
                music[i]->setVolume(0.50f);
            }
            if(seq_pitch_class == 1 && seq_otave == 5)
            {
                music[i]->setSource(QUrl::fromLocalFile(QString::fromStdString("../audio/melody/1_5.wav")));
                music[i]->setVolume(0.50f);
            }
            if(seq_pitch_class == 2 && seq_otave == 4)
            {
                music[i]->setSource(QUrl::fromLocalFile(QString::fromStdString("../audio/melody/2_4.wav")));
                music[i]->setVolume(0.50f);
            }
            if(seq_pitch_class == 2 && seq_otave == 5)
            {
                music[i]->setSource(QUrl::fromLocalFile(QString::fromStdString("../audio/melody/2_5.wav")));
                music[i]->setVolume(0.50f);
            }
            if(seq_pitch_class == 3 && seq_otave == 4)
            {
                music[i]->setSource(QUrl::fromLocalFile(QString::fromStdString("../audio/melody/3_4.wav")));
                music[i]->setVolume(0.50f);
            }
            if(seq_pitch_class == 3 && seq_otave == 5)
            {
                music[i]->setSource(QUrl::fromLocalFile(QString::fromStdString("../audio/melody/3_5.wav")));
                music[i]->setVolume(0.50f);

            }
            if(seq_pitch_class == 4 && seq_otave == 4)
            {
                music[i]->setSource(QUrl::fromLocalFile(QString::fromStdString("../audio/melody/4_4.wav")));
                music[i]->setVolume(0.50f);

            }
            if(seq_pitch_class == 5 && seq_otave == 4)
            {
                music[i]->setSource(QUrl::fromLocalFile(QString::fromStdString("../audio/melody/5_4.wav")));
                music[i]->setVolume(0.50f);

            }
            if(seq_pitch_class == 6 && seq_otave == 4)
            {
                music[i]->setSource(QUrl::fromLocalFile(QString::fromStdString("../audio/melody/6_4.wav")));
                music[i]->setVolume(0.50f);

            }
            if(seq_pitch_class == 7 && seq_otave == 4)
            {
                music[i]->setSource(QUrl::fromLocalFile(QString::fromStdString("../audio/melody/7_4.wav")));
                music[i]->setVolume(0.50f);

            }
            if(seq_pitch_class == 8 && seq_otave == 4)
            {
                music[i]->setSource(QUrl::fromLocalFile(QString::fromStdString("../audio/melody/8_4.wav")));
                music[i]->setVolume(0.50f);

            }
            if(seq_pitch_class == 9 && seq_otave == 4)
            {
                music[i]->setSource(QUrl::fromLocalFile(QString::fromStdString("../audio/melody/9_4.wav")));
                music[i]->setVolume(0.50f);

            }
        }
    }

    void Melodytrack::play() // sequnece의 연주를 시작시킨가 (SLOT인 play_music 재생시킴)
    {
        set_size();
        set_music();
        player = new QTimer;
        connect(player, SIGNAL(timeout()), this, SLOT(play_music()));
        player->start(125);
    }

    void Melodytrack::play_music() // playmusic은 timeout() SIGNAL을 받아 startcheck()와 removecheck()를 진행한다.
    {
        startcheck();
        removecheck();
        plus_current_time();
    }

    void Melodytrack::startcheck() // 재생시간에 포함되는 Note를  searching하고 이를 재생시킨다.
    {
        std::vector<Note*> temp = melody_seq->GetOrdered();

        for(size_t i = 0; i < size; i++)
        {
            if(current_time == temp[i]->GetStart())
            {
                music[i]->play();
                qDebug() << "music " << i << " is started.\n";
            }
        }
    }

    void Melodytrack::removecheck() // 재생시간에 포함되는 Note를 searching하고 이를 멈춘다.
    {
        std::vector<Note*> temp = melody_seq->GetOrdered();

            for(size_t i = 0; i < size; i++)
            {
                if(current_time == (temp[i]->GetStart() + temp[i]->GetDuration()))
                {
                    music[i]->stop();
                    qDebug() << "music " << i << " stop.\n";
                }
            }

    }

    void Melodytrack::plus_current_time()
    {
        current_time += 125;
    }

    //////////////////////////////////////////////

    ISeq* Drumtrack::get_Drum_seq()
    {
        return Drum_seq;
    }

    void Drumtrack::set_size()
    {
        std::vector<Note*> temp = Drum_seq->GetOrdered();
        size = temp.size();
        music = new QSoundEffect* [size];
    }

    void Drumtrack::set_music()
    {
        //QSoundEffect* music;

        std::vector<Note*> temp = Drum_seq->GetOrdered();
        size_t size = temp.size();

        int seq_pitch_class, seq_otave;

        for(size_t i = 0; i < size; i++)
        {
            music[i] = new QSoundEffect ;
            seq_pitch_class = temp[i]->GetPitch().GetPitchClass();
            seq_otave = temp[i]->GetPitch().GetOctave();

            if(seq_pitch_class == 0 && seq_otave == 4)
            {
                music[i]->setSource(QUrl::fromLocalFile(QString::fromStdString("../audio/Drum/0_4.wav")));
                music[i]->setVolume(0.50f);
            }
            if(seq_pitch_class == 0 && seq_otave == 5)
            {
                music[i]->setSource(QUrl::fromLocalFile(QString::fromStdString("../audio/Drum/0_5.wav")));
                music[i]->setVolume(0.50f);
            }
            if(seq_pitch_class == 10 && seq_otave == 4)
            {
                music[i]->setSource(QUrl::fromLocalFile(QString::fromStdString("../audio/Drum/10_4.wav")));
                music[i]->setVolume(0.50f);
            }
            if(seq_pitch_class == 11 && seq_otave == 4)
            {
                music[i]->setSource(QUrl::fromLocalFile(QString::fromStdString("../audio/Drum/11_4.wav")));
                music[i]->setVolume(0.50f);
            }
            if(seq_pitch_class == 1 && seq_otave == 4)
            {
                music[i]->setSource(QUrl::fromLocalFile(QString::fromStdString("../audio/Drum/1_4.wav")));
                music[i]->setVolume(0.50f);
            }
            if(seq_pitch_class == 1 && seq_otave == 5)
            {
                music[i]->setSource(QUrl::fromLocalFile(QString::fromStdString("../audio/Drum/1_5.wav")));
                music[i]->setVolume(0.50f);
            }
            if(seq_pitch_class == 2 && seq_otave == 4)
            {
                music[i]->setSource(QUrl::fromLocalFile(QString::fromStdString("../audio/Drum/2_4.wav")));
                music[i]->setVolume(0.50f);
            }
            if(seq_pitch_class == 2 && seq_otave == 5)
            {
                music[i]->setSource(QUrl::fromLocalFile(QString::fromStdString("../audio/Drum/2_5.wav")));
                music[i]->setVolume(0.50f);
            }
            if(seq_pitch_class == 3 && seq_otave == 4)
            {
                music[i]->setSource(QUrl::fromLocalFile(QString::fromStdString("../audio/Drum/3_4.wav")));
                music[i]->setVolume(0.50f);
            }
            if(seq_pitch_class == 3 && seq_otave == 5)
            {
                music[i]->setSource(QUrl::fromLocalFile(QString::fromStdString("../audio/Drum/3_5.wav")));
                music[i]->setVolume(0.50f);

            }
            if(seq_pitch_class == 4 && seq_otave == 4)
            {
                music[i]->setSource(QUrl::fromLocalFile(QString::fromStdString("../audio/Drum/4_4.wav")));
                music[i]->setVolume(0.50f);

            }
            if(seq_pitch_class == 5 && seq_otave == 4)
            {
                music[i]->setSource(QUrl::fromLocalFile(QString::fromStdString("../audio/Drum/5_4.wav")));
                music[i]->setVolume(0.50f);

            }
            if(seq_pitch_class == 6 && seq_otave == 4)
            {
                music[i]->setSource(QUrl::fromLocalFile(QString::fromStdString("../audio/Drum/6_4.wav")));
                music[i]->setVolume(0.50f);

            }
            if(seq_pitch_class == 7 && seq_otave == 4)
            {
                music[i]->setSource(QUrl::fromLocalFile(QString::fromStdString("../audio/Drum/7_4.wav")));
                music[i]->setVolume(0.50f);

            }
            if(seq_pitch_class == 8 && seq_otave == 4)
            {
                music[i]->setSource(QUrl::fromLocalFile(QString::fromStdString("../audio/Drum/8_4.wav")));
                music[i]->setVolume(0.50f);

            }
            if(seq_pitch_class == 9 && seq_otave == 4)
            {
                music[i]->setSource(QUrl::fromLocalFile(QString::fromStdString("../audio/Drum/9_4.wav")));
                music[i]->setVolume(0.50f);

            }
        }
    }

    void Drumtrack::play()
    {
        set_size();
        set_music();
        player = new QTimer;
        connect(player, SIGNAL(timeout()), this, SLOT(play_music()));
        player->start(125);
    }

    void Drumtrack::play_music()
    {
        startcheck();
        removecheck();
        plus_current_time();
    }

    void Drumtrack::startcheck()
    {
        std::vector<Note*> temp = Drum_seq->GetOrdered();

        for(size_t i = 0; i < size; i++)
        {
            if(current_time == temp[i]->GetStart())
            {
                music[i]->play();
                qDebug() << "music " << i << " is started.\n";
            }
        }
    }

    void Drumtrack::removecheck()
    {
        std::vector<Note*> temp = Drum_seq->GetOrdered();

            for(size_t i = 0; i < size; i++)
            {
                if(current_time == (temp[i]->GetStart() + temp[i]->GetDuration()))
                {
                    music[i]->stop();
                    qDebug() << "music " << i << " stop.\n";
                }
            }

    }

    void Drumtrack::plus_current_time()
    {
        current_time += 125;
    }

}
