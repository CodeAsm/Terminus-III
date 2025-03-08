#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <string>
#include <vector>
#include <memory>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "file.h"

class Directory {
public:
    std::string name;
    std::string creationTime;
    std::string accessTime;
    std::string modificationTime;
    int permissions; // Unix-like permissions (e.g., 0755)
    std::string owner; // Owner of the directory
    std::string group; // Group of the directory
    std::vector<std::shared_ptr<Directory>> subdirectories;
    std::vector<std::shared_ptr<File>> files;

    Directory(const std::string& name, int permissions = 0755, const std::string& owner = "", const std::string& group = "");

    std::shared_ptr<Directory> findSubdirectory(const std::string& name);
    std::shared_ptr<File> findFile(const std::string& name);
    void addSubdirectory(const std::shared_ptr<Directory>& subdirectory);
    void addFile(const std::shared_ptr<File>& file);

private:
    std::string getCurrentTime();
};

#endif // DIRECTORY_H