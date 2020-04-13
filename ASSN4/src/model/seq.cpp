#include <algorithm>

#include "model/seq.h"

namespace as4::model
{
    VectorSeq::~VectorSeq() // VectorSeq 소멸자
    {
        for(size_t i=0; i<m_notes.size(); i++)
        {
            delete m_notes[i];
        }
    }


    VectorSeq::VectorSeq(const VectorSeq &other) // VectorSeq 복사생성자
    {
        for(size_t i=0; i<other.m_notes.size(); i++)
        {
            m_notes.push_back(new Note(*other.m_notes[i]));
        }
    }

    VectorSeq &VectorSeq::operator=(const VectorSeq &other) // VectorSeq 대입
    {
        for(size_t i=0; i<m_notes.size(); i++)
        {
            delete m_notes[i];
        }
        m_notes.clear();

        for(size_t i=0; i<other.m_notes.size(); i++)
        {
            m_notes.push_back(new Note(*other.m_notes[i]));
        }

        return *this;
    }

    void VectorSeq::Put(const Note &note) // VectorSeq에 note를 put 하고 sort
    {
        m_notes.push_back(new Note(note));
        // Since we use a simple vector,
        // we must sort the vector everytime we modify m_notes
        Sort();
    }

    std::vector<Note*> VectorSeq::Get(const Timestamp &pos_seeker)
    // VectorSeq에 있는 note중에서 노트 시작 시간 < pos_seeker < 노트 종료 시간 인 note의 벡터반환
    {
        std::vector<Note*> result;
        for(size_t i=0; i<m_notes.size(); i++)
        {
            Timestamp start = m_notes[i]->GetStart();
            Timestamp end = start+m_notes[i]->GetDuration();
            if (start <= pos_seeker && end > pos_seeker)
            {
                result.push_back(m_notes[i]);
            }
        }

        return result;
    }

    bool VectorSeq::Remove(const Note *note) // note를 찾아서 있으면 삭제
    {
        const auto target =
                std::find(std::begin(m_notes), std::end(m_notes), note);
        if(std::end(m_notes) != target) // remove target found
        {
            m_notes.erase(target);
            // Since we use a simple vector,
            // we must sort the vector everytime we modify m_notes
            Sort();
            return true;
        }
        else { // not found
            return false;
        }
    }

    std::vector<Note*> VectorSeq::GetOrdered() // 정렬된 note 벡터 반환
    {
        // Just copy notes directly since they are already ordered
        return m_notes;
    }

    TimeInterval VectorSeq::GetSeqTimeLength() const // ???
    {
        if(0 == m_notes.size())
        {
            return 0;
        }
        else {
            return m_notes.back()->GetStart() +
                    m_notes.back()->GetDuration();
        }
    }

    void VectorSeq::Sort() // note 의 start time에 따라서 순서대로 정렬한다
    {
        // sort m_notes according to start time of each note
        std::sort(std::begin(m_notes), std::end(m_notes),
                [](const Note *a, const Note *b){
            return a->GetStart() < b->GetStart(); });
    }

    bool operator== (const ISeq& seq1,const ISeq& seq2) {

                std::vector<Note*> temp1 = const_cast<ISeq&>(seq1).GetOrdered();
                std::vector<Note*> temp2 = const_cast<ISeq&>(seq2).GetOrdered();

                if(temp1.size() != temp2.size()) return false;

                for(size_t i = 0; i< temp1.size(); i++) {

                    if(*(temp1[i]) != *(temp2[i])) return false;
                }

                return true;
            }
}
