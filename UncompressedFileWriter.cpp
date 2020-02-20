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
#include "UncompressedFileWriter.h"

using namespace std;

UncompressedFileWriter::UncompressedFileWriter(const char *filename) {
        
    outFile.open(filename);
    
    if(!outFile.is_open()){
        cout << "Cannot open selected output file: " << filename << endl;
        exit(-1);
    }
    
}

UncompressedFileWriter::UncompressedFileWriter(const UncompressedFileWriter& orig) {
}

UncompressedFileWriter::~UncompressedFileWriter() {
}

void UncompressedFileWriter::write(char code){
    outFile.write((char*) &code, sizeof(char));
}

void UncompressedFileWriter::close(){
    outFile.close();
}