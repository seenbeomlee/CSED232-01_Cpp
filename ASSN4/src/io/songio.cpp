#include "io/songio.h"
#include "io/seqio.h"

namespace as4::io
{
    namespace operators
    {
    std::istream& operator>> (std::istream& fin, as4::model::Song& song)
                {
                    operator>>(fin, *(song.GetMelodySeq()));
                    operator>>(fin, *(song.GetDrumSeq()));
                    return fin;
                }

                std::ostream& operator<< (std::ostream& fout, as4::model::Song& song)
                {
                    operator<<(fout, *(song.GetMelodySeq()));
                    operator<<(fout, *(song.GetDrumSeq()));
                    return fout;
                }
    }
}
