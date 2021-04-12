#ifndef LOAD_H
#define LOAD_H

#include "Database.h"
#include <filesystem>
#include <optional>

std::optional<Database> loadFromFile(const std::filesystem::path &);

#endif
