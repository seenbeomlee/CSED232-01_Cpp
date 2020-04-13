#include "io/seqio.h"

using namespace as4::model;
namespace as4::io
{
    namespace operators
    {
    std::istream& operator>> (std::istream& fin, as4::model::ISeq& seq)
                {
                    Timestamp seq_start;
                    TimeInterval seq_duration;
                    int seq_pitch_class, seq_otave;
                    size_t size;

                    fin >> size;

                    for(size_t i = 0; i < size; i++) {
                        fin >> seq_start >> seq_duration >> seq_pitch_class >> seq_otave;
                        seq.Put({seq_start, seq_duration, {seq_pitch_class, seq_otave}});
                    }

                    return fin;
                }

                std::ostream& operator<< (std::ostream& fout, as4::model::ISeq& seq)
                {
                    Timestamp seq_start;
                    TimeInterval seq_duration;
                    int seq_pitch_class, seq_otave;

                    std::vector<Note*> temp = seq.GetOrdered();

                    fout << temp.size() << std::endl;

                    for(size_t i = 0; i < temp.size(); i++)
                    {
                        seq_start = temp[i]->GetStart();
                        seq_duration = temp[i]->GetDuration();
                        seq_pitch_class = temp[i]->GetPitch().GetPitchClass();
                        seq_otave = temp[i]->GetPitch().GetOctave();
                        fout << seq_start <<" "<< seq_duration <<" "<< seq_pitch_class <<" "<< seq_otave << std::endl;
                    }

                    return fout;
                }
    }
}
