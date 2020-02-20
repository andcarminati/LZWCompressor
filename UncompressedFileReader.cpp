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
#include <fstream>
#include <iostream>
#include "UncompressedFileReader.h"

using namespace std;

UncompressedFileReader::UncompressedFileReader(const char * fileName) {
    
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
