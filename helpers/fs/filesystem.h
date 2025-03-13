#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <memory>
#include "directory.h"

class filesystem {
public:
    std::shared_ptr<directory> current_directory;
    std::shared_ptr<directory> root_directory;

    filesystem(const std::shared_ptr<directory>& root);

    std::string navigate_to(const std::string& path);
    void list_directory();
    std::vector<std::string> list_directory(const std::string& path);
    bool create_file(const std::string& name, const std::string& content);
    bool create_directory(const std::string& path);
    bool delete_file(const std::string& name);
    bool delete_directory(const std::string& name);
};

#endif // FILESYSTEM_H