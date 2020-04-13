#ifndef __AS4_IO_SEQ_H
#define __AS4_IO_SEQ_H

#include <istream>
#include <ostream>

#include "model/seq.h"

/**
 * Abstract)
 * IO functions for note seqences
 *
 * Notes)
 * These namespace specifications(as4::io) are not mendatory for our code 
 * to work. However, it helps the users of this code not to mix many 
 * function/classes with identical names.
 */
namespace as4::io
{
    namespace operators
    {
        std::istream& operator>> (std::istream& fin, as4::model::ISeq& seq); // sequence에 대해 파일의 내용을 읽어오는 역할
        std::ostream& operator<< (std::ostream& fout, as4::model::ISeq&); // sequence에 대해 파일의 내용을 출력하는 역할
    }
}

#endif
