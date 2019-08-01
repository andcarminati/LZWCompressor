/* 
 * File:   LZWDictionary.h
 * Author: andreu
 *
 * Created on 25 de Junho de 2019, 16:18
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

