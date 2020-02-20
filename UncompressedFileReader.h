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

#ifndef UNCOMPRESSEDFILEREADER_H
#define	UNCOMPRESSEDFILEREADER_H

class UncompressedFileReader {
public:
    UncompressedFileReader(const char* fileName);
    UncompressedFileReader(const UncompressedFileReader& orig);
    virtual ~UncompressedFileReader();
    
    bool hasMore();
    unsigned short nextByte();
    int size();
private:
    unsigned char *buffer;
    int byteCount;
    int totalBytes;
};

#endif	/* UNCOMPRESSEDFILEREADER_H */

