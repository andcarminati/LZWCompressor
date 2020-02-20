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
    auto fr = std::make_unique<UncompressedFileReader>("gmon.out");
    auto fw = std::make_unique<CompressedFileWriter>("saida.bin");
    cout << "Compressing data\n";
    
    LZWEncoder encoder(std::move(fr), std::move(fw));
    encoder.encode();
  
    cout << "Reading compressed file\n";
    auto cfr = std::make_unique<CompressedFileReader>("saida.bin");
    auto ufw = std::make_unique<UncompressedFileWriter>("saida.txt");
    cout << "Decompressing data\n";
    
    LZWDecoder decoder(std::move(cfr), std::move(ufw));
    decoder.decode();
    cout << "Done\n";
    return 0;
}

