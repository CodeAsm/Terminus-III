#include "filesystem.h"
#include <iostream>
#include <algorithm>

FileSystem::FileSystem(const std::shared_ptr<Directory>& root) {
    rootDirectory = root;
    currentDirectory = root;
}

void FileSystem::navigateTo(const std::string& path) {
    // Navigate to the specified path
    if (path == "/") {
        currentDirectory = rootDirectory;
    } else {
        auto dir = currentDirectory->findSubdirectory(path);
        if (dir) {
            currentDirectory = dir;
        } else {
            std::cout << "Directory not found: " << path << std::endl;
        }
    }
}

void FileSystem::listDirectory() {
    // List the contents of the current directory
    std::cout << "Listing directory: " << currentDirectory->name << std::endl;
    for (const auto& subdir : currentDirectory->subdirectories) {
        std::cout << "DIR: " << subdir->name << std::endl;
    }
    for (const auto& file : currentDirectory->files) {
        std::cout << "FILE: " << file->name << std::endl;
    }
}

void FileSystem::createFile(const std::string& name, const std::string& content) {
    // Create a new file in the current directory
    auto file = std::make_shared<File>(name, content);
    currentDirectory->addFile(file);
}

void FileSystem::createDirectory(const std::string& name) {
    // Create a new directory in the current directory
    auto dir = std::make_shared<Directory>(name);
    currentDirectory->addSubdirectory(dir);
}

void FileSystem::deleteFile(const std::string& name) {
    // Delete a file from the current directory
    auto file = currentDirectory->findFile(name);
    if (file) {
        currentDirectory->files.erase(std::remove(currentDirectory->files.begin(), currentDirectory->files.end(), file), currentDirectory->files.end());
    } else {
        std::cout << "File not found: " << name << std::endl;
    }
}

void FileSystem::deleteDirectory(const std::string& name) {
    // Delete a directory from the current directory
    auto dir = currentDirectory->findSubdirectory(name);
    if (dir) {
        currentDirectory->subdirectories.erase(std::remove(currentDirectory->subdirectories.begin(), currentDirectory->subdirectories.end(), dir), currentDirectory->subdirectories.end());
    } else {
        std::cout << "Directory not found: " << name << std::endl;
    }
}