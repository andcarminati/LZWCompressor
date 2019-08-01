/* 
 * File:   UncompressedFileReader.cpp
 * Author: andreu
 * 
 * Created on 27 de Junho de 2019, 15:53
 */

#include <fstream>
#include <iostream>
#include "UncompressedFileReader.h"

using namespace std;

UncompressedFileReader::UncompressedFileReader(char * fileName) {
    
    byteCount = 0;
    streampos begin,end; 
    ifstream in(fileName, ios::binary);
    begin = in.tellg();
    in.seekg(0, ios::end);
    end = in.tellg();
    
    totalBytes = end-begin;
    
    if(!in.is_open()){
        cout << "Cannot open selected input file: " << fileName << endl;
        exit(-1);
    }
    
    cout << "Uncompressed file size is: " << (totalBytes) << " bytes.\n";
    
    in.seekg(0, ios::beg);
    
    buffer = new unsigned char[totalBytes];
    
    in.read (reinterpret_cast<char*>(buffer), totalBytes);
    in.close();
}

UncompressedFileReader::UncompressedFileReader(const UncompressedFileReader& orig) {
}

UncompressedFileReader::~UncompressedFileReader() {
    delete[] buffer;
}

bool UncompressedFileReader::hasMore(){
    
    if(byteCount < totalBytes){
        return true;
    }
    return false;
}

unsigned short UncompressedFileReader::nextByte(){
    return buffer[byteCount++];
}

int UncompressedFileReader::size(){
    return totalBytes;
}
