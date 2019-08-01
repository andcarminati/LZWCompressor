/* 
 * File:   LZWDecoder.h
 * Author: andreu
 *
 * Created on 28 de Junho de 2019, 15:52
 */

#ifndef LZWDECODER_H
#define	LZWDECODER_H

#include "CompressedFileReader.h"
#include "LZWDictionary.h"
#include "UncompressedFileWriter.h"


class LZWDecoder {
public:
    LZWDecoder(CompressedFileReader*, UncompressedFileWriter*);
    LZWDecoder(const LZWDecoder& orig);
    virtual ~LZWDecoder();
    void decode();
private:
    CompressedFileReader* reader;
    UncompressedFileWriter* writer;
    LZWDictionary* dictionary;
    void output(unsigned char*, int);
};

#endif	/* LZWDECODER_H */

