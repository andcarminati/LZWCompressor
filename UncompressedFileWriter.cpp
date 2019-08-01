/* 
 * File:   UncompressedFileWriter.cpp
 * Author: andreu
 * 
 * Created on 1 de Julho de 2019, 16:05
 */

#include "UncompressedFileWriter.h"

using namespace std;

UncompressedFileWriter::UncompressedFileWriter(char *filename) {
        
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