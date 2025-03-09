#include "gamestate.h"
#include <iostream>

gamestate::gamestate() : storyline(0) {
    // Initialize targets and directories
}

void gamestate::initialize() {
    // Initialize the game state
    auto root = std::make_shared<directory>("/");
    current_target = std::make_shared<target>("default_target", root);
    targets.push_back(current_target);
    active_filesystem = std::make_shared<filesystem>(root);
}

void gamestate::switch_target(const std::shared_ptr<target>& new_target) {
    current_target = new_target;
    active_filesystem = std::make_shared<filesystem>(new_target->rootDirectory);
}
