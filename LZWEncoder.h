/* 
 * File:   LZWEncoder.h
 * Author: andreu
 *
 * Created on 27 de Junho de 2019, 16:15
 */

#ifndef LZWENCODER_H
#define	LZWENCODER_H

#include "UncompressedFileReader.h"
#include "LZWDictionary.h"
#include "CompressedFileWriter.h"


class LZWEncoder {
public:
    LZWEncoder(UncompressedFileReader*, CompressedFileWriter*);
    LZWEncoder(const LZWEncoder& orig);
    virtual ~LZWEncoder();
    
    void encode();
private:
    UncompressedFileReader* reader;
    CompressedFileWriter* writer;
    LZWDictionary* dictionary;
};

#endif	/* LZWENCODER_H */

