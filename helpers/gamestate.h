#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>
#include <vector>
#include <memory>
#include "../targets/target.h"

class GameState {
public:
    std::vector<std::shared_ptr<Target>> targets;
    std::shared_ptr<Target> currentTarget;
    std::shared_ptr<Directory> currentDirectory;
    std::string currentUser;

    GameState();

    void initialize();
    void navigateTo(const std::string& path);
    void listDirectory();
    void createFile(const std::string& name, const std::string& content);
    void createDirectory(const std::string& name);
    void deleteFile(const std::string& name);
    void deleteDirectory(const std::string& name);
};

#endif // GAMESTATE_H