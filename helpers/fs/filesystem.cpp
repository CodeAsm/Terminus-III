#include "filesystem.h"
#include <iostream>
#include <algorithm>
#include <sstream>

/// Filesystem class implementation
/// The filesystem class provides an interface to interact with the directory structure
/// and files in the game. It allows the player to navigate directories, list directory
/// contents, create files and directories, and delete files and directories.
filesystem::filesystem(const std::shared_ptr<directory>& root) {
    root_directory = root;
    current_directory = root;
}

std::string filesystem::navigate_to(const std::string& path) {
    if (path == "/") {
        current_directory = root_directory;
        return "/";
    }

    std::istringstream iss(path);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(iss, token, '/')) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }

    std::shared_ptr<directory> target_directory = (path[0] == '/') ? root_directory : current_directory;

    for (const auto& part : tokens) {
        if (part == "..") {
            if (target_directory->parent) {
                target_directory = target_directory->parent;
            }
        } else {
            auto subdir = target_directory->find_subdirectory(part);
            if (subdir) {
                target_directory = subdir;
            } else {
                std::cout << "Directory not found: " << part << std::endl;
                return "";
            }
        }
    }

    current_directory = target_directory;
    return path;
}
        current_directory = root_directory;
        return;
    }

    std::istringstream iss(path);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(iss, token, '/')) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }

    std::shared_ptr<directory> target_directory = (path[0] == '/') ? root_directory : current_directory;

    for (const auto& part : tokens) {
        if (part == "..") {
            if (target_directory->parent) {
                target_directory = target_directory->parent;
            }
        } else {
            auto subdir = target_directory->find_subdirectory(part);
            if (subdir) {
                target_directory = subdir;
            } else {
                std::cout << "Directory not found: " << part << std::endl;
                return;
            }
        }
    }

    current_directory = target_directory;
}

void filesystem::list_directory() {
    // List the contents of the current directory
    std::cout << "Listing directory: " << current_directory->name << std::endl;
    for (const auto& subdir : current_directory->subdirectories) {
        std::cout << "DIR: " << subdir->name << std::endl;
    }
    for (const auto& file : current_directory->files) {
        std::cout << "FILE: " << file->name << std::endl;
    }
}

std::vector<std::string> filesystem::list_directory(const std::string& path) {
    // List the contents of a directory
    std::vector<std::string> contents;
    std::shared_ptr<directory> target_directory = current_directory;

    if (!path.empty()) {
        navigate_to(path);
        target_directory = current_directory;
    }

    for (const auto& subdir : target_directory->subdirectories) {
        contents.push_back("DIR: " + subdir->name);
    }
    for (const auto& file : target_directory->files) {
        contents.push_back("FILE: " + file->name);
    }

    // Reset current_directory to the original directory
    if (!path.empty()) {
        navigate_to("/");
    }

    return contents;
}
void filesystem::create_file(const std::string& path, const std::string& content) {
    // Resolve the path and create a new file in the specified directory
    std::istringstream iss(path);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(iss, token, '/')) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }

    if (tokens.empty()) {
        std::cout << "Invalid path: " << path << std::endl;
        return;
    }

    std::shared_ptr<directory> target_directory = (path[0] == '/') ? root_directory : current_directory;

    for (size_t i = 0; i < tokens.size() - 1; ++i) {
        auto subdir = target_directory->find_subdirectory(tokens[i]);
        if (subdir) {
            target_directory = subdir;
        } else {
            std::cout << "Directory not found: " << tokens[i] << std::endl;
            return;
        }
    }

    std::string file_name = tokens.back();
    std::shared_ptr<file> new_file = std::make_shared<file>(file_name, content);
    target_directory->add_file(new_file);
}

void filesystem::create_directory(const std::string& path) {
    // Create a new directory in the current directory
    std::istringstream iss(path);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(iss, token, '/')) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }

    std::shared_ptr<directory> target_directory = (path[0] == '/') ? root_directory : current_directory;

    for (const auto& part : tokens) {
        auto subdir = target_directory->find_subdirectory(part);
        if (!subdir) {
            subdir = std::make_shared<directory>(part, 0755, "", "", target_directory);
            target_directory->add_subdirectory(subdir);
        }
        target_directory = subdir;
    }
}

void filesystem::delete_file(const std::string& name) {
    // Delete a file from the current directory
    auto file = current_directory->find_file(name);
    if (file) {
        current_directory->files.erase(std::remove(current_directory->files.begin(), current_directory->files.end(), file), current_directory->files.end());
        std::cout << "File deleted: " << name << std::endl;
    } else {
        std::cout << "File not found: " << name << std::endl;
    }
}

void filesystem::delete_directory(const std::string& name) {
    // Delete a directory from the current directory
    auto dir = current_directory->find_subdirectory(name);
    if (dir) {
        current_directory->subdirectories.erase(std::remove(current_directory->subdirectories.begin(), current_directory->subdirectories.end(), dir), current_directory->subdirectories.end());
        std::cout << "Directory deleted: " << name << std::endl;
    } else {
        std::cout << "Directory not found: " << name << std::endl;
    }
}