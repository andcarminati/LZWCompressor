/* 
 * File:   UncompressedFileWriter.h
 * Author: andreu
 *
 * Created on 1 de Julho de 2019, 16:05
 */

#ifndef UNCOMPRESSEDFILEWRITER_H
#define	UNCOMPRESSEDFILEWRITER_H

#include <iostream>
#include <fstream>

class UncompressedFileWriter {
public:
    UncompressedFileWriter(char *filename);
    UncompressedFileWriter(const UncompressedFileWriter& orig);
    virtual ~UncompressedFileWriter();
    
    void write(char code);
    void close();
private:
    std::ofstream outFile;
};

#endif	/* UNCOMPRESSEDFILEWRITER_H */

