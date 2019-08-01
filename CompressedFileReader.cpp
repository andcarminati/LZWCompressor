/* 
 * File:   CompressedFileReader.cpp
 * Author: andreu
 * 
 * Created on 28 de Junho de 2019, 15:38
 */

#include "CompressedFileReader.h"

#include <fstream>
#include <iostream>
using namespace std;

CompressedFileReader::CompressedFileReader(char * fileName) {
    dataCount = 0;
    streampos begin,end; 
    
    ifstream in(fileName, ios::binary);
    begin = in.tellg();
    in.seekg(0, ios::end);
    end = in.tellg();
    totalData = (end-begin);
    
    if(!in.is_open()){
        cout << "Cannot open selected input file: " << fileName << endl;
        exit(-1);
    }
    
    cout << "Compressed file size is: " << (totalData) << " bytes.\n";
    
    in.seekg(0, ios::beg);
    buffer = new unsigned char[totalData];
    in.read (reinterpret_cast<char*>(buffer), totalData);
    in.close();
}

CompressedFileReader::CompressedFileReader(const CompressedFileReader& orig) {}

CompressedFileReader::~CompressedFileReader() {
    delete[] buffer;
}

bool CompressedFileReader::hasMore(){
    
    if(dataCount < totalData){
        return true;
    }
    return false;
}

unsigned short CompressedFileReader::nextData(){
    
    unsigned short value = 0;
    
    if(hasRest){
        unsigned char part8bits = buffer[dataCount++];
        value = (rest << 8) | part8bits;
        hasRest = false;
    } else {
        unsigned char part8bits = buffer[dataCount++];
        unsigned char part4bits = buffer[dataCount++];
        rest = part4bits & 0x0F;
        value = (part8bits << 4) | (part4bits >> 4); 
        hasRest = true;
    }
    return value;
}

int CompressedFileReader::size(){
    return (totalData*16)/12;
}