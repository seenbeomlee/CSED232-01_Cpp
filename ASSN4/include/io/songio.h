#ifndef __AS4_SONGIO_H
#define __AS4_SONGIO_H

#include <istream>
#include <ostream>

#include "model/song.h"

namespace as4::io
{
    namespace operators
    {
        std::istream& operator>> (std::istream& fin, as4::model::Song& song); // song에 대해 파일의 내용을 읽어오는 역할
        std::ostream& operator<< (std::ostream& fout, as4::model::Song& song); // song에 대해 파일의 내용을 출력하는 역할
    }
}

#endif
