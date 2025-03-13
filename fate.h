#ifndef FATE_H
#define FATE_H

#include "helpers/gamestate.h"

// Function declarations
void bruteforcer();
void ircdeadbeat();
void rm(gamestate& game_state);
void Trinity();
void portscan();
void ftpexploit();
void ircharper();
void telnet();
void typer();
void pausing();
void intro();
void john();
void systemspecific();
void whoami();
void echo();
void su();
void fileshow(gamestate& game_state);
void cat(gamestate& game_state);
void debug();
void mkdirr(gamestate& game_state);
void area6();
void updir();
void pwd(gamestate& game_state);
void cd(gamestate& game_state);
void ls(gamestate& game_state);
void halt();
void cline(gamestate& game_state);
void bash(gamestate& game_state);
void login();
void boot();
void interpret(gamestate& game_state);

// New function to setup area6 server
void setup_area6_server(gamestate& game_state);

// Functions that need work
void garbage();
void skipstuff();
void dataa();
void zionwelcome();
void unicode();
void ircb0ilerdeadbeat();
void ircopticon();
void Zion();
void Morbid();

#endif // FATE_H