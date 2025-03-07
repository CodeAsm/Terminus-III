#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <string>
#include <vector>
#include <memory>
#include "file.h"

class Directory {
public:
    std::string name;
    std::vector<std::shared_ptr<Directory>> subdirectories;
    std::vector<std::shared_ptr<File>> files;

    Directory(const std::string& name) : name(name) {}

    std::shared_ptr<Directory> findSubdirectory(const std::string& name);
    std::shared_ptr<File> findFile(const std::string& name);
    void addSubdirectory(const std::shared_ptr<Directory>& subdirectory);
    void addFile(const std::shared_ptr<File>& file);
};

#endif // DIRECTORY_H