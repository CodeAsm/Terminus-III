#include "file.h"

file::file()
    : name(""), content(""), readOnly(false), permissions(0644), owner(""), group("") {
    creationTime = getCurrentTime();
    accessTime = creationTime;
    modificationTime = creationTime;
    size = 0;
}

file::file(const std::string& name, const std::string& content, bool readOnly, int permissions, std::string owner, std::string group)
    : name(name), content(content), readOnly(readOnly), permissions(permissions), owner(owner), group(group) {
    creationTime = getCurrentTime();
    accessTime = creationTime;
    modificationTime = creationTime;
    size = content.size();
}

std::string file::getCurrentTime() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}