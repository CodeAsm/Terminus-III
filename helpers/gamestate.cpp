#include "gamestate.h"
#include <iostream>
#include <algorithm>

GameState::GameState() {
    // Initialize servers and directories
}

void GameState::initialize() {
    // Initialize the game state
    auto root = std::make_shared<Directory>("/");
    currentDirectory = root;
    currentTarget = std::make_shared<Target>("DefaultServer", root);
    targets.push_back(currentTarget);
}

void GameState::navigateTo(const std::string& path) {
    // Navigate to the specified path
    if (path == "/") {
        currentDirectory = currentTarget->rootDirectory;
    } else {
        auto dir = currentDirectory->findSubdirectory(path);
        if (dir) {
            currentDirectory = dir;
        } else {
            std::cout << "Directory not found: " << path << std::endl;
        }
    }
}

void GameState::listDirectory() {
    // List the contents of the current directory
    std::cout << "Listing directory: " << currentDirectory->name << std::endl;
    for (const auto& subdir : currentDirectory->subdirectories) {
        std::cout << "DIR: " << subdir->name << std::endl;
    }
    for (const auto& file : currentDirectory->files) {
        std::cout << "FILE: " << file->name << std::endl;
    }
}

void GameState::createFile(const std::string& name, const std::string& content) {
    // Create a new file in the current directory
    auto file = std::make_shared<File>(name, content, false, 0644, currentDirectory->name);
    file->owner = "defaultOwner";
    file->group = "defaultGroup";
    file->permissions = 0644;
    currentDirectory->addFile(file);
}

void GameState::createDirectory(const std::string& name) {
    // Create a new directory in the current directory
    auto dir = std::make_shared<Directory>(name);
    currentDirectory->addSubdirectory(dir);
}

void GameState::deleteFile(const std::string& name) {
    // Delete a file from the current directory
    auto file = currentDirectory->findFile(name);
    if (file) {
        currentDirectory->files.erase(std::remove(currentDirectory->files.begin(), currentDirectory->files.end(), file), currentDirectory->files.end());
    } else {
        std::cout << "File not found: " << name << std::endl;
    }
}

void GameState::deleteDirectory(const std::string& name) {
    // Delete a directory from the current directory
    auto dir = currentDirectory->findSubdirectory(name);
    if (dir) {
        currentDirectory->subdirectories.erase(std::remove(currentDirectory->subdirectories.begin(), currentDirectory->subdirectories.end(), dir), currentDirectory->subdirectories.end());
    } else {
        std::cout << "Directory not found: " << name << std::endl;
    }
}