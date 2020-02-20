/*
Simple implementation of LZW compression algorithm
Copyright (C) 2019  Andreu Carminati
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef LZWDECODER_H
#define	LZWDECODER_H

#include <memory>
#include "CompressedFileReader.h"
#include "LZWDictionary.h"
#include "UncompressedFileWriter.h"



class LZWDecoder {
public:
    LZWDecoder(std::unique_ptr<CompressedFileReader> CFR, std::unique_ptr<UncompressedFileWriter> UFW): 
        reader(std::move(CFR)), writer(std::move(UFW)) {
            dictionary = std::make_unique<LZWDictionary>();
        };
    LZWDecoder(const LZWDecoder& orig);
    virtual ~LZWDecoder();
    void decode();
private:
    std::unique_ptr<CompressedFileReader> reader;
    std::unique_ptr<UncompressedFileWriter> writer;
    std::unique_ptr<LZWDictionary> dictionary;
    void output(unsigned char*, int);
};

#endif	/* LZWDECODER_H */

