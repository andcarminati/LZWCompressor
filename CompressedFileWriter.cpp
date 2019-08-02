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