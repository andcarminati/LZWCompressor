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

static bool exists(const char* name) {
    if (FILE * file = fopen(name, "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

static void encoderDriver(const char* uncompressedFileName, const char* compressedFileName) {

    cout << "Reading uncompressed file\n";
    auto fr = std::make_unique<UncompressedFileReader>(uncompressedFileName);
    auto fw = std::make_unique<CompressedFileWriter>(compressedFileName);

    fw->writeFileName(uncompressedFileName);

    cout << "Compressing data\n";

    LZWEncoder encoder(std::move(fr), std::move(fw));
    encoder.encode();

}

static void decoderDriver(const char* compressedFileName) {
    cout << "Reading compressed file\n";
    auto cfr = std::make_unique<CompressedFileReader>("saida.bin");

    const char* uncompressedFilename = cfr->readUncompressedFileName();

    if (exists(uncompressedFilename)) {
        cout << "Aborting decompression, file already exists" << endl;
    } else {
        auto ufw = std::make_unique<UncompressedFileWriter>("saida.txt");
        cout << "Decompressing data\n";
        LZWDecoder decoder(std::move(cfr), std::move(ufw));
        decoder.decode();
    }

    delete[] uncompressedFilename;
}

int main(int argc, char** argv) {

    const char* input1 = NULL;
    const char* input2 = NULL;


    if (argc == 1) {
        cout << "Usage:" << endl;
        cout << "Compression: " << "-c <inputfile> <outputfile>"  << endl;
        cout << "Decompression: " << "-d <inputfile>"  << endl;
        return -1;
    }
    if (argc < 3) {
        cout << "Insuffifient number of parameters" << endl;
        return -1;
    }
    input1 = argv[2];

    if (argc == 4) {
        input2 = argv[3];
    }

    if (strcmp(argv[1], "-c") == 0) {
        const char* uncompressedFileName = input1;
        const char* compressedFileName = NULL;

        if (!input2) {
            cout << "Omitted compression parameter (file name): " << endl;
            return -1;
        }
        compressedFileName = input2;

        encoderDriver(uncompressedFileName, compressedFileName);
    } else if (strcmp(argv[1], "-d") == 0) {
        const char* compressedFileName = input1;
        
        decoderDriver(compressedFileName);
    } else {
        cout << "Invalid parameter: " << argv[1] << endl;
        return -1;
    }

    cout << "Done\n";
    return 0;
}

