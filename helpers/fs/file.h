#ifndef FILE_H
#define FILE_H

#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>

class file {
public:
    std::string name;
    std::string content;
    bool readOnly;
    std::string creationTime;
    std::string accessTime;
    std::string modificationTime;
    int size;
    int permissions;
    std::string owner;
    std::string group;

    file();
    file(const std::string& name, const std::string& content = "", bool readOnly = false, int permissions = 0644, std::string owner = "", std::string group = "");

private:
    std::string getCurrentTime();
};

#endif // FILE_H