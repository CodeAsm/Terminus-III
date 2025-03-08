#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <memory>
#include "directory.h"

class FileSystem {
public:
    std::shared_ptr<Directory> currentDirectory;
    std::shared_ptr<Directory> rootDirectory;

    FileSystem(const std::shared_ptr<Directory>& root);

    void navigateTo(const std::string& path);
    void listDirectory();
    void createFile(const std::string& name, const std::string& content);
    void createDirectory(const std::string& name);
    void deleteFile(const std::string& name);
    void deleteDirectory(const std::string& name);
};

#endif // FILESYSTEM_H