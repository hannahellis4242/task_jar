#ifndef SAVE_H
#define SAVE_H

#include <filesystem>

class Database;
bool saveToFile(const std::filesystem::path &,const Database &);

#endif
