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
#include <utility> 
#include <cstdlib>
#include <string.h>
#include <map>
#include <iostream>
#include "LZWDictionary.h"

using namespace std;

void Entry::fillEntry(unsigned char* seq, int size, int code){
    
    if(size >= 50){
        cout << "Overflow in dictionary entry\n";
        exit(-1);
    }
    memcpy(sequence, seq, size);
    this->code = code;
    this->size = size;
    this->inUse = true;
}

bool Entry::isInUse(){
    return inUse;
}

bool Entry::isEqual(Entry* other){
    return isEqual(other->sequence, other->size);
}

bool Entry::isEqual(unsigned char* seq, int size){
    
    int n;
    if(this->size != size){
        return false;
    }
    n=memcmp (seq, this->sequence, size);

    if(n == 0){
        return true;
    }
    
    return false;
}

short Entry::getCode(){
    return code;
}

LZWDictionary::LZWDictionary() {
    valueCount = 0;
    
    for (int i = 0; i < 256; i++) {
       insert(reinterpret_cast<unsigned char*>(&i), 1);
    }
}

LZWDictionary::LZWDictionary(const LZWDictionary& orig) {
    
}

LZWDictionary::~LZWDictionary() {
    
}

bool LZWDictionary::contains(unsigned char seq[], int size){
    
    if(size == 1){
        return seq[0];
    }
    
    long hashCode = genHash(seq, size);
    map<long, int>::iterator iterator;
    
    iterator = hash.find(hashCode);
    
    if(iterator != hash.end()){
        int code = iterator->second;
        Entry* entry = &entries[code];
        if(!entry->isInUse()){
            return false;
        }
        if(entry->isEqual(seq, size)){
            return true;
        } else {
            for (int i = 256; i < valueCount; i++) {
                Entry* elem = &entries[i];
                if(elem->isEqual(seq, size)){
                    return true;
                }
            }
        }
    }
    return false;
}

int LZWDictionary::insert(unsigned char seq[], int size){
    
    int code = valueCount;
    int hashCode = genHash(seq, size);
    Entry* entry = &entries[valueCount++];
    entry->fillEntry(seq, size, code);
    
    hash.insert(make_pair(hashCode, code));
    
    return code;
}

int LZWDictionary::getCode(unsigned char seq[], int size){
    
    int code = -1;
    
    if(size == 1){
        return seq[0];
    }
    
    long hashCode = genHash(seq, size);
    map<long, int>::iterator iterator;
    iterator = hash.find(hashCode);
    
    if(iterator != hash.end()){
        int code = iterator->second;
        Entry* entry = &entries[code];
        if(!entry->isInUse()){
            return -1;
        }
        if(entry->isEqual(seq, size)){
            code = entry->getCode();
            return code;
        } 
    } 
    
    for (int i = 256; i < valueCount; i++) {
        Entry* elem = &entries[i];
        if(elem->isEqual(seq, size)){
            code = elem->getCode();
        }
    }
    return code;
}


bool LZWDictionary::isFull(){
    
    if(valueCount < MAX_ENTRIES){
        return false;
    }
    
    return true;
}

long LZWDictionary::genHash(unsigned char* str, int size){
    //credit to the original developer
    //https://github.com/fragglet/c-algorithms/blob/master/src/hash-string.c
    unsigned long hash = 5381;
    int c;

    while (size--){
        c = *str++;
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }    
    return hash;
}

int LZWDictionary::getSequence(short code, unsigned char* &seq){
    Entry* entry = &entries[code];
    
    seq = entry->sequence;
    
    return entry->size;
}


bool LZWDictionary::exists(short code){
    Entry* entry = &entries[code];
    
    return entry->inUse;
}