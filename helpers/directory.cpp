#include "directory.h"
#include <algorithm>
#include <iomanip>
#include <sstream>

directory::directory(const std::string& name, int permissions, const std::string& owner, const std::string& group, std::shared_ptr<directory> parent)
    : name(name), permissions(permissions), owner(owner), group(group), parent(parent), creationTime(get_current_time()), accessTime(creationTime), modificationTime(creationTime) {}

std::shared_ptr<directory> directory::find_subdirectory(const std::string& name) {
    for (auto& subdir : subdirectories) {
        if (subdir->name == name) {
            return subdir;
        }
    }
    return nullptr;
}

std::shared_ptr<file> directory::find_file(const std::string& name) {
    for (auto& file : files) {
        if (file->name == name) {
            return file;
        }
    }
    return nullptr;
}

void directory::add_subdirectory(const std::shared_ptr<directory>& subdirectory) {
    subdirectories.push_back(subdirectory);
}

void directory::add_file(const std::shared_ptr<file>& file) {
    files.push_back(file);
}

std::string directory::get_current_time() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}