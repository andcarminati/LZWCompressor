/* 
 * File:   LZWEncoder.cpp
 * Author: andreu
 * 
 * Created on 27 de Junho de 2019, 16:15
 */

#include <iostream>
#include "LZWEncoder.h"

using namespace std;

LZWEncoder::LZWEncoder(UncompressedFileReader* file, CompressedFileWriter* fileout) {
    reader = file;
    writer = fileout;
    dictionary = new LZWDictionary();
}

LZWEncoder::LZWEncoder(const LZWEncoder& orig) {
}

LZWEncoder::~LZWEncoder() {
}

static void dumpP(unsigned char* seq, int size, short code){
    for (int i = 0; i < size; i++) {
       cout << (char)seq[i];
    } 
    cout << ": " << code << endl;
}

void LZWEncoder::encode(){
    
    unsigned char C;
    unsigned char P[100];
    unsigned char sizeP = 0;
    
    while(reader->hasMore()){
        
        C = reader->nextByte();
        P[sizeP] = C;
        if(dictionary->contains(P, sizeP+1)){
            sizeP++;
        }else {
            short code = dictionary->getCode(P, sizeP);
            dumpP(P, sizeP, code);
            writer->write(code);
            if(!dictionary->isFull()){
                dictionary->insert(P, sizeP+1);
            }
            P[0] = C;
            sizeP = 1;
        }
    }
    short code = dictionary->getCode(P, sizeP);
    //dumpP(P, sizeP, code);
    writer->write(code);
}