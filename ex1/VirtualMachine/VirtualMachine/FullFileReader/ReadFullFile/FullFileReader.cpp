//
// Created by user on 13.09.18.
//

#include <cstdio>
#include <sys/stat.h>
#include <zconf.h>
#include <iostream>
#include "FullFileReader.h"
#include <fcntl.h>
#include <stdio.h>
#include <cstring>

namespace FullFileReader {
    int readFullFile(const char *FileName, char ** text) {
        int fileDescriptor = open(FileName, O_RDONLY);
        struct stat st;
        fstat(fileDescriptor, &st);
        auto fullTextSize = static_cast<int>(st.st_size);
        (*text) = new char[fullTextSize + 1]; // Maybe - maybe
        read(fileDescriptor, *text, fullTextSize);
        close(fileDescriptor);
        return fullTextSize;
    }

}