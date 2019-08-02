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

#ifndef LZWDICTIONARY_H
#define	LZWDICTIONARY_H

#include <map>

using namespace std;

#define MAX_ENTRIES 4096

typedef struct Entry{
    unsigned char sequence[50];
    short code;
    int size;
    bool inUse = false;
    bool isEqual(Entry* other);
    bool isEqual(unsigned char* seq, int size);
    void fillEntry(unsigned char* seq, int size, int code);
    short getCode();
    bool isInUse();
} Entry;

class LZWDictionary {
public:
    LZWDictionary();
    LZWDictionary(const LZWDictionary& orig);
    virtual ~LZWDictionary();
    
    bool contains(unsigned char seq[], int size);
    int insert(unsigned char seq[], int size);
    int getCode(unsigned char seq[], int size);
    bool isFull();
    long genHash(unsigned char seq[], int size);
    int getSequence(short code, unsigned char* &seq);
    bool exists(short code);
private:
    int valueCount;
    Entry entries[MAX_ENTRIES];
    map<long, int> hash;
};

#endif	/* LZWDICTIONARY_H */

