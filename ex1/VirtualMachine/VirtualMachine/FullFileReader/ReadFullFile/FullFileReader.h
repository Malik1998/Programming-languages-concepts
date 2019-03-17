//
// Created by user on 13.09.18.
//

#ifndef STRINGSORTING_FULLFILEREADER_H
#define STRINGSORTING_FULLFILEREADER_H
#include <cstdio>

/// Change full file into variable and manupulate with it
namespace FullFileReader {
    /// read file to text pointer
    /// \param FileName - name of the file to be read
    /// \param text - variable, that will point to text
    int readFullFile(const char *FileName, char ** text);
};


#endif //STRINGSORTING_FULLFILEREADER_H
