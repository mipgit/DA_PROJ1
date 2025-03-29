#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <filesystem>

inline std::string getFullPath(const std::string& relativePath) {
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::filesystem::path parentPath = currentPath.parent_path();
    return (parentPath / relativePath).string();
}

#endif
