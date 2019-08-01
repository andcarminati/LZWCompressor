/* 
 * File:   CompressedFileReader.h
 * Author: andreu
 *
 * Created on 28 de Junho de 2019, 15:38
 */

#ifndef COMPRESSEDFILEREADER_H
#define	COMPRESSEDFILEREADER_H

class CompressedFileReader {
public:
    CompressedFileReader(char * fileName);
    CompressedFileReader(const CompressedFileReader& orig);
    virtual ~CompressedFileReader();
    bool hasMore();
    unsigned short nextData();
    int size();
    
private:
    unsigned char *buffer;
    int dataCount;
    int totalData;
    bool hasRest = false;
    unsigned char rest = 0;

};

#endif	/* COMPRESSEDFILEREADER_H */

