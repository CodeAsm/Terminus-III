#ifndef TARGET_H
#define TARGET_H

#include <string>
#include <memory>
#include "../helpers/fs/directory.h"

class target {
public:
    std::string name;
    std::shared_ptr<directory> rootDirectory;

    target(const std::string& name, const std::shared_ptr<directory>& rootDirectory)
        : name(name), rootDirectory(rootDirectory) {}

    void reset();
};

#endif // TARGET_H