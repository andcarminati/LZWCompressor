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
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>
#include <iostream>

#include "LZWDictionary.h"
#include "UncompressedFileReader.h"
#include "CompressedFileReader.h"
#include "LZWEncoder.h"
#include "CompressedFileWriter.h"
#include "LZWDecoder.h"
#include "UncompressedFileWriter.h"

using namespace std;

/*
 * 
 */


int main(int argc, char** argv) {

    cout << "Reading uncompressed file\n";
    UncompressedFileReader fr("gmon.out");
    CompressedFileWriter fw("saida.bin");
    cout << "Compressing data\n";
    LZWEncoder encoder(&fr, &fw);
    encoder.encode();
    fw.close();
    cout << "Reading compressed file\n";
    CompressedFileReader cfr("saida.bin");
    UncompressedFileWriter ufw("saida.txt");
    cout << "Decompressing data\n";
    LZWDecoder decoder(&cfr, &ufw);
    decoder.decode();
    cout << "Done\n";
    return 0;
}

