/* 
 * File:   CompressedFileWriter.h
 * Author: andreu
 *
 * Created on 27 de Junho de 2019, 16:53
 */

#ifndef COMPRESSEDFILEWRITER_H
#define	COMPRESSEDFILEWRITER_H

#include <iostream>
#include <fstream>

class CompressedFileWriter {
public:
    CompressedFileWriter(char *filename);
    CompressedFileWriter(const CompressedFileWriter& orig);
    virtual ~CompressedFileWriter();
    
    void write(short code);
    void close();
private:
    
    std::ofstream outFile;
    unsigned char rest = 0;
    bool hasRest = false;
};

#endif	/* COMPRESSEDFILEWRITER_H */

