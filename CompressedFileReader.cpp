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

#include "CompressedFileReader.h"

#include <fstream>
#include <iostream>
using namespace std;

CompressedFileReader::CompressedFileReader(const char * fileName) {
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