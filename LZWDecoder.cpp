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
#include <iostream>
#include <cstring>
#include "LZWDecoder.h"
#include "LZWDictionary.h"

using namespace std;

LZWDecoder::LZWDecoder(CompressedFileReader* reader, UncompressedFileWriter* writer) {
    this->reader = reader;
    this->writer = writer;
    dictionary = new LZWDictionary();
}

LZWDecoder::LZWDecoder(const LZWDecoder& orig) {
}

LZWDecoder::~LZWDecoder() {
    delete dictionary;
}


static void dumpP(unsigned char* seq, int size, short code){
    for (int i = 0; i < size; i++) {
       cout << (char)seq[i];
    } 
    cout << ": " << code << endl;
}

static void dumpP2(unsigned char* seq, int size, short code){
    for (int i = 0; i < size; i++) {
       cout << (char)seq[i];
    }
}

void LZWDecoder::output(unsigned char* buffer, int size){
    for (int i = 0; i < size; i++) {
        writer->write(buffer[i]);
    }
}


void LZWDecoder::decode(){
    
    unsigned char P[100];
    unsigned char C;
    unsigned short Cw;
    unsigned short Pw;
    unsigned char sizeP = 0;
    
    Cw = reader->nextData();
    unsigned char* data;
    int sizeCw = dictionary->getSequence(Cw, data);
    //dumpP2(data, sizeCw, Cw);
    output(data, sizeCw);
    
    while(reader->hasMore()){
        Pw = Cw;
        Cw = reader->nextData();
        
        if(dictionary->exists(Cw)){
            sizeCw = dictionary->getSequence(Cw, data);
            //dumpP2(data, sizeCw, Cw);
            output(data, sizeCw);
            unsigned char* dataP;
            sizeP = dictionary->getSequence(Pw, dataP);
            memcpy(P, dataP, sizeP);
            C = data[0];
            P[sizeP] = C;
            if(!dictionary->isFull()){
                dictionary->insert(P, sizeP+1);
            }
        } else {
            unsigned char* dataP;
            sizeP = dictionary->getSequence(Pw, dataP);
            memcpy(P, dataP, sizeP);
            C = dataP[0];
            P[sizeP] = C;
            //dumpP2(P, sizeP+1, 0);
            output(P, sizeP+1);
            if(!dictionary->isFull()){
                dictionary->insert(P, sizeP+1);
            }
        }
    }
}
