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

#ifndef COMPRESSEDFILEWRITER_H
#define	COMPRESSEDFILEWRITER_H

#include <iostream>
#include <fstream>

class CompressedFileWriter {
public:
    CompressedFileWriter(char *filename);
    CompressedFileWriter(const CompressedFileWriter& orig);
    virtual ~CompressedFileWriter();
    
    void write(short code);
    void close();
private:
    
    std::ofstream outFile;
    unsigned char rest = 0;
    bool hasRest = false;
};

#endif	/* COMPRESSEDFILEWRITER_H */

