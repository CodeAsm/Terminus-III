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

    void navigate_to(const std::string& path);
    void list_directory();
    void create_file(const std::string& name, const std::string& content);
    void create_directory(const std::string& path);
    void delete_file(const std::string& name);
    void delete_directory(const std::string& name);
};

#endif // FILESYSTEM_H