#ifndef TARGET_H
#define TARGET_H

#include <string>
#include <memory>
#include "../helpers/directory.h"

class Target {
public:
    std::string name;
    std::shared_ptr<Directory> rootDirectory;

    Target(const std::string& name, const std::shared_ptr<Directory>& rootDirectory)
        : name(name), rootDirectory(rootDirectory) {}

    void reset();
};

#endif // TARGET_H