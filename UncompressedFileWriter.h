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

#ifndef UNCOMPRESSEDFILEWRITER_H
#define	UNCOMPRESSEDFILEWRITER_H

#include <iostream>
#include <fstream>

class UncompressedFileWriter {
public:
    UncompressedFileWriter(const char *filename);
    UncompressedFileWriter(const UncompressedFileWriter& orig);
    virtual ~UncompressedFileWriter();
    
    void write(char code);
    void close();
private:
    std::ofstream outFile;
};

#endif	/* UNCOMPRESSEDFILEWRITER_H */

