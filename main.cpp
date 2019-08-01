/* 
 * File:   main.cpp
 * Author: andreu
 *
 * Created on 25 de Junho de 2019, 16:14
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

