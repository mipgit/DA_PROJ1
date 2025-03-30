/** @file utils.h
 *  @brief Utility functions for file path resolution.
 *
 *  This header provides helper functions for resolving file paths.
 */

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <filesystem>


/**
 * @brief Resolves the full path of a file based on its relative path.
 *
 * This function takes a relative file path and combines it with the parent directory 
 * of the current working directory to compute the full absolute file path.
 *
 * @param relativePath The relative file path to resolve.
 * @return A string containing the full absolute file path.
 *
 * @throws std::filesystem::filesystem_error If the current path cannot be retrieved.
 */
inline std::string getFullPath(const std::string& relativePath) {
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::filesystem::path parentPath = currentPath.parent_path();
    return (parentPath / relativePath).string();
}

#endif
