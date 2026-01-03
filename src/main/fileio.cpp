#include "fileio.h"
#include <fstream>
#include <sstream>

bool loadLibrary(const std::string &filename, std::vector<Book> &library) {
    std::ifstream in(filename);
    if (!in.is_open()) return false;

    library.clear();
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::istringstream ss(line);
        Book b;
        std::string quantityStr;
        if (!std::getline(ss, line, '|')) continue; // bookID
        b.bookID = std::stoi(line);
        if (!std::getline(ss, b.title, '|')) continue;
        if (!std::getline(ss, b.author, '|')) continue;
        if (!std::getline(ss, quantityStr, '|')) continue;
        b.quantity = std::stoi(quantityStr);
        library.push_back(b);
    }
    in.close();
    return true;
}

bool saveLibrary(const std::string &filename, const std::vector<Book> &library) {
    std::ofstream out(filename);
    if (!out.is_open()) return false;

    for (const auto &b : library) {
        out << b.bookID << '|' << b.title << '|' << b.author << '|' << b.quantity << '\n';
    }

    out.close();
    return true;
}
