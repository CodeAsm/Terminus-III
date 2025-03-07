#ifndef FILE_H
#define FILE_H

#include <string>

class File {
public:
    std::string name;
    std::string content;
    bool readOnly;

    File(const std::string& name, const std::string& content = "", bool readOnly = false)
        : name(name), content(content), readOnly(readOnly) {}
};

#endif // FILE_H