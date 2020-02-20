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

#ifndef COMPRESSEDFILEREADER_H
#define	COMPRESSEDFILEREADER_H

class CompressedFileReader {
public:
    CompressedFileReader(const char * fileName);
    CompressedFileReader(const CompressedFileReader& orig);
    virtual ~CompressedFileReader();
    bool hasMore();
    unsigned short nextData();
    int size();
    const char* readUncompressedFileName();
    
private:
    unsigned char *buffer;
    int dataCount;
    int totalData;
    bool hasRest = false;
    unsigned char rest = 0;

};

#endif	/* COMPRESSEDFILEREADER_H */

