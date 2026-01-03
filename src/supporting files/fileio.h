#ifndef FILEIO_H
#define FILEIO_H

#include <vector>
#include "book.h"

bool loadLibrary(const std::string &filename, std::vector<Book> &library);
bool saveLibrary(const std::string &filename, const std::vector<Book> &library);

#endif // FILEIO_H
