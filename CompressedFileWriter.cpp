/* 
 * File:   CompressedFileWriter.cpp
 * Author: andreu
 * 
 * Created on 27 de Junho de 2019, 16:53
 */

#include "CompressedFileWriter.h"

using namespace std;

CompressedFileWriter::CompressedFileWriter(char *filename) {

    outFile.open(filename);

    if (!outFile.is_open()) {
        cout << "Cannot open selected output file: " << filename << endl;
        exit(-1);
    }

}

CompressedFileWriter::CompressedFileWriter(const CompressedFileWriter& orig) {
}

CompressedFileWriter::~CompressedFileWriter() {
}

void CompressedFileWriter::write(short code) {

    if (hasRest) {
        unsigned char part4bits = code >> 8;
        unsigned char part8bits = code & 0x00FF;
        rest = rest | part4bits;

        outFile.write((char*) &rest, sizeof (unsigned char));
        outFile.write((char*) &part8bits, sizeof (unsigned char));
        hasRest = false;
    } else {
        unsigned char part8bits = code >> 4;
        unsigned char part4Bits = (code & 0x000F);
        rest = part4Bits << 4;
        outFile.write((char*) &part8bits, sizeof (unsigned char));
        hasRest = true;
    }


}

void CompressedFileWriter::close() {
    if (hasRest) {
        outFile.write((char*) &rest, sizeof (unsigned char));
    }
    outFile.close();
}