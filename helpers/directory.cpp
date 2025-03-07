#include "directory.h"

std::shared_ptr<Directory> Directory::findSubdirectory(const std::string& name) {
    for (auto& subdir : subdirectories) {
        if (subdir->name == name) {
            return subdir;
        }
    }
    return nullptr;
}

std::shared_ptr<File> Directory::findFile(const std::string& name) {
    for (auto& file : files) {
        if (file->name == name) {
            return file;
        }
    }
    return nullptr;
}

void Directory::addSubdirectory(const std::shared_ptr<Directory>& subdirectory) {
    subdirectories.push_back(subdirectory);
}

void Directory::addFile(const std::shared_ptr<File>& file) {
    files.push_back(file);
}