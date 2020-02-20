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
#include "LZWEncoder.h"

using namespace std;

LZWEncoder::LZWEncoder(const LZWEncoder& orig) {}

LZWEncoder::~LZWEncoder() {}

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
            //dumpP(P, sizeP, code);
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
    writer->close();
}