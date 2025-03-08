#include "directory.h"
#include <algorithm>
#include <iomanip>
#include <sstream>

Directory::Directory(const std::string& name, int permissions, const std::string& owner, const std::string& group)
    : name(name), permissions(permissions), owner(owner), group(group), creationTime(getCurrentTime()), accessTime(creationTime), modificationTime(creationTime) {}

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

std::string Directory::getCurrentTime() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}