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

void filesystem::navigate_to(const std::string& path) {
    if (path == "/") {
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

void filesystem::create_file(const std::string& name, const std::string& content) {
    // Create a new file in the current directory
    std::shared_ptr<file> new_file = std::make_shared<file>(name, content);
    current_directory->add_file(new_file);
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