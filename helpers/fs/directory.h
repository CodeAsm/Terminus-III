#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <string>
#include <vector>
#include <memory>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "file.h"

class directory {
public:
    std::string name;
    std::string creationTime;
    std::string accessTime;
    std::string modificationTime;
    int permissions; // Unix-like permissions (e.g., 0755)
    std::string owner; // Owner of the directory
    std::string group; // Group of the directory
    std::shared_ptr<directory> parent;
    std::vector<std::shared_ptr<directory>> subdirectories;
    std::vector<std::shared_ptr<file>> files;

    directory(const std::string& name, int permissions = 0755, const std::string& owner = "", const std::string& group = "", std::shared_ptr<directory> parent = nullptr);

    std::shared_ptr<directory> find_subdirectory(const std::string& name);
    std::shared_ptr<file> find_file(const std::string& name);
    void add_subdirectory(const std::shared_ptr<directory>& subdirectory);
    void add_file(const std::shared_ptr<file>& file);

private:
    std::string get_current_time();
};

#endif // DIRECTORY_H