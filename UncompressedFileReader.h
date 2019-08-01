/* 
 * File:   UncompressedFileReader.h
 * Author: andreu
 *
 * Created on 27 de Junho de 2019, 15:53
 */

#ifndef UNCOMPRESSEDFILEREADER_H
#define	UNCOMPRESSEDFILEREADER_H

class UncompressedFileReader {
public:
    UncompressedFileReader(char * fileName);
    UncompressedFileReader(const UncompressedFileReader& orig);
    virtual ~UncompressedFileReader();
    
    bool hasMore();
    unsigned short nextByte();
    int size();
private:
    unsigned char *buffer;
    int byteCount;
    int totalBytes;
};

#endif	/* UNCOMPRESSEDFILEREADER_H */

