#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>
#include <vector>
#include <memory>
#include "../targets/target.h"
#include "filesystem.h"

class gamestate {
public:
    std::vector<std::shared_ptr<target>> targets;
    std::shared_ptr<target> current_target;
    std::shared_ptr<filesystem> active_filesystem;
    std::string current_user;
    int storyline;

    gamestate();

    void initialize();
    void switch_target(const std::shared_ptr<target>& new_target);
};

#endif // GAMESTATE_H