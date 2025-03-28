/*

==============
= F A T E =
= v0.2b =
==============

Produced by m101
Reworked by CodeAsm in 2025

This code has been produced in Borland Turbo C++. Ha lol, nah, its gcc now baby. 
The entire source is not available here, and is not even written in the same language. Or is it? 
Please do not request the full source, i will provide copies of the source in diferent programming languages when i have time. Nah i wont.
Updates will not be made to each source code. Feel free to distribute this code, but please give me credit for my work and do not change this header. 
Will do. The original code was written by m101 and I enjoyed Fate1 and 2.ADJ_OFFSET_SINGLESHOT
And now I present to you the source code for Fate3. Enjoy. 

the original source and game can be found at https://web.archive.org/web/20050420084310/http://www.fatetek.net/getfate.shtml
*/

//intro
//boot
//**fileshow
//****typer
//****pauser
//****debug
#include <math.h>
#include <stdlib.h>
#include <array>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include "fate.h"
#include "helpers/gamestate.h"

using namespace std;

char *ptr;          // Pointer for string manipulation
char osys[50];      // Original system (to return to)
char systemm[50];   // System message
char sys[50];       // System name
std::string com;    // Command
char arg[50];       // Argument
int success;        // Command success
int success2;                       // Command success 2 (for system specific commands)
std::array<std::string, 50> dir;    // Directory
char structure[200][50];            // Directory structure
char filestruct[200][50];   // File structure
int fileindex[200];         // File index
char ostructure[200][50];   // Original directory structure
char ofilestruct[200][50];  // Original file structure
int ofileindex[200];        // Original file index
int telnetting;        // Telnetting flag  (for returning to original system)
char user[50];         // User
char ouser[50];        // Original user (for returning to original system)
int storyline;         // Storyline (to keep track of the story)
int bypass;            // Bypass flag (for bypassing security)
int shortened;         // Shortened intro flag (we don't want to show the intro while the menu not finished)
char tem[50];          // Temporary string


int main()
{

    gamestate game_state;
    game_state.initialize();

    // Setup the area6 server
    setup_area6_server(game_state);

    // Example usage
    /* DO NOT REMOVE, THIS IS A TEST
    cout << "Current directory: " << game_state.active_filesystem->current_directory->name << endl;
    game_state.active_filesystem->create_directory("home");
    game_state.active_filesystem->create_directory("root");
    game_state.active_filesystem->create_directory("etc");
    game_state.active_filesystem->create_directory("bin");
    game_state.active_filesystem->list_directory();
    cout << "Current directory: " << game_state.active_filesystem->current_directory->name << endl;
    game_state.active_filesystem->navigate_to("/home");
    game_state.active_filesystem->create_directory("m101");
    game_state.active_filesystem->create_directory("morpheus");
    cout << "Current directory: " << game_state.active_filesystem->current_directory->name << endl;
    game_state.active_filesystem->list_directory();
    game_state.active_filesystem->create_file("example.txt", "Hello, World!");
    game_state.active_filesystem->create_directory("new_folder");
    cout << "Current directory: " << game_state.active_filesystem->current_directory->name << endl;
    game_state.active_filesystem->list_directory();
	game_state.active_filesystem->create_directory("/home/new_folder");
	game_state.active_filesystem->navigate_to("/home/new_folder");
    cout << "Current directory: " << game_state.active_filesystem->current_directory->name << endl;
    game_state.active_filesystem->list_directory();
    game_state.active_filesystem->navigate_to("/home");
    cout << "Current directory: " << game_state.active_filesystem->current_directory->name << endl;
    game_state.active_filesystem->list_directory();
     */

    game_state.active_filesystem->navigate_to("/");
    game_state.active_filesystem->list_directory();
	game_state.active_filesystem->navigate_to("/home");
    game_state.active_filesystem->list_directory();
    game_state.active_filesystem->navigate_to("/home/m101");
    game_state.active_filesystem->list_directory();

    //login should fill the current user.
    strcpy(user, "root"); //TODO do some user shenanigans

    bash(game_state);
    return 0;



//
// call menu
// set colours
	strcpy(sys,"Area6");
// set intro to be sortened while menu does not exist
	shortened=0;

	if (shortened==0)
		intro();
	boot();
//fix the setting up
	strcpy(systemm,"Area 6 Linux release 6.4 (Immortal) for i586\n");
	login();
return 0;
}

void intro()
{
}

void boot()
{
}


/// @brief  Get a password from the user
/// @param password     The password to get     
/// @param size         The size of the password buffer
/// @return             The password
/// @note               The password is not echoed back to the user
void getPassword(char *password, size_t size) {
    struct termios oldt, newt;
    int i = 0;
    char c;

    // Turn echoing off and fail if we can't
    if (tcgetattr(STDIN_FILENO, &oldt) != 0) {
        perror("tcgetattr");
        exit(EXIT_FAILURE);
    }
    newt = oldt;
    newt.c_lflag &= ~ECHO;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &newt) != 0) {
        perror("tcsetattr");
        exit(EXIT_FAILURE);
    }

    // Read the password
    while (i < size - 1 && read(STDIN_FILENO, &c, 1) == 1 && c != '\n') {
        password[i++] = c;
    }
    password[i] = '\0';

    // Restore terminal
    if (tcsetattr(STDIN_FILENO, TCSANOW, &oldt) != 0) {
        perror("tcsetattr");
        exit(EXIT_FAILURE);
    }
}

/// @brief  
void login()
{
	int wronglogin=0;
	char *pass;
	if (strcmp(sys,"Area6")==0)
	{
		area6();
	}
	if (strcmp(sys,"Trinity")==0)
	{
		Trinity();
	}
	if (strcmp(sys,"Zion")==0)
	{
		Zion();
	}
	if (strcmp(sys,"Morbid")==0)
	{
		Morbid();
	}
	cout << systemm;
	cout << "Kernel 2.4.8-26A6 on an i686 / tty1\n";
	redo:
	cout << "Login: ";
	fgets(user, sizeof(user), stdin);
	user[strcspn(user, "\n")] = 0; // Remove newline character
    cout << "Password: " << flush;
    pass = (char *) malloc(50);
    getPassword(pass, sizeof(pass));
    cout << endl;
	if (strcmp(sys,"Area6")==0 && strcmp(user,"m101")==0 && strcmp(pass,"area6")==0)
		goto logged;
	if (strcmp(sys,"Area6")==0 && strcmp(user,"root")==0 && strcmp(pass,"moxalt")==0)
		goto logged;
	if (strcmp(sys,"Trinity")==0 && strcmp(user,"ftp")==0 && strcmp(pass,"admirality")==0)
		goto logged;
	if (strcmp(sys,"Trinity")==0 && strcmp(user,"root")==0 && strcmp(pass,"seeinchin")==0)
		goto logged;
	if (strcmp(sys,"Zion")==0 && strcmp(user,"ftp")==0 && strcmp(pass,"fred")==0)
		goto logged;
	if (strcmp(sys,"Zion")==0 && strcmp(user,"root")==0 && strcmp(pass,"crafted")==0)
		goto logged;
	if (strcmp(sys,"Morbid")==0 && strcmp(user,"ftp")==0 && strcmp(pass,"oslo")==0)
		goto logged;
	if (strcmp(sys,"Morbid")==0 && strcmp(user,"root")==0 && strcmp(pass,"unisol")==0)
		goto logged;
	cout << "Login Incorrect\n";
	wronglogin=wronglogin+1;
	cout << endl;
	if (wronglogin == 4 && telnetting==1)
	{
        int i;
		strcpy(user,ouser);
		strcpy(sys,osys);
		for (i=1;i<200;i++)
		{
			strcpy(filestruct[i],ofilestruct[i]);
			fileindex[i]=ofileindex[i];
			strcpy(structure[i],ostructure[i]);
		}
	goto badguesser;
	}
	goto redo;
	logged:
	//bash(gamestate& game_state);
	badguesser:
	cout << "";
}


void setup_area6_server(gamestate& game_state) {
    // Create directories
    game_state.active_filesystem->create_directory("/bin");
    game_state.active_filesystem->create_directory("/etc");
    game_state.active_filesystem->create_directory("/home");
    game_state.active_filesystem->create_directory("/home/root");
    game_state.active_filesystem->create_directory("/home/m101");
    game_state.active_filesystem->create_directory("/lib");
    game_state.active_filesystem->create_directory("/mnt");
    game_state.active_filesystem->create_directory("/sbin");
    game_state.active_filesystem->create_directory("/usr");
    game_state.active_filesystem->create_directory("/var");
    game_state.active_filesystem->create_directory("/usr/john");

    // Create files
    game_state.active_filesystem->create_file("/etc/passwd", "root:x:0:0:root:/root:/bin/bash\nm101:x:1000:1000:m101:/home/m101:/bin/bash\n");
    game_state.active_filesystem->create_file("/bin/cat", "binary content");
    game_state.active_filesystem->create_file("/bin/echo", "binary content");
    game_state.active_filesystem->create_file("/bin/mkdir", "binary content");
    game_state.active_filesystem->create_file("/bin/pwd", "binary content");
    game_state.active_filesystem->create_file("/bin/su", "binary content");
    game_state.active_filesystem->create_file("/home/m101/welcome", "Welcome to your home directory!\n");
    game_state.active_filesystem->create_file("/usr/john/john", "binary content");
    game_state.active_filesystem->create_file("/home/root/Area6", "Area6 specific content");
    game_state.active_filesystem->create_file("/bin/telnet", "binary content");
}


void area6() //could be nuked.
{
    int i;
	for(i=1;i<200;i++)
	{
		structure[i][0]='\0';
	}
	strcpy(structure[1],"/");
	strcpy(structure[2],"/bin");
	strcpy(structure[3],"/etc");
	strcpy(structure[4],"/home");
	strcpy(structure[10],"/home/root");
	strcpy(structure[11],"/home/m101");
	strcpy(structure[5],"/lib");
	strcpy(structure[6],"/mnt");
	strcpy(structure[7],"/sbin");
	strcpy(structure[8],"/usr");
	strcpy(structure[9],"/var");
	strcpy(structure[12],"/usr/john");
	for(i=1;i<200;i++)
	{
		filestruct[i][0]='\0';
		fileindex[i]=0;
	}
	strcpy(filestruct[1],"/etc/passwd");
	fileindex[1]=1;
	strcpy(filestruct[2],"/bin/cat");
	fileindex[2]=2;
	strcpy(filestruct[3],"/bin/echo");
	fileindex[3]=3;
	strcpy(filestruct[4],"/bin/mkdir");
	fileindex[4]=4;
	strcpy(filestruct[5],"/bin/pwd");
	fileindex[5]=5;
	strcpy(filestruct[6],"/bin/su");
	fileindex[6]=6;
	strcpy(filestruct[7],"/home/m101/welcome");
	fileindex[7]=7;
	strcpy(filestruct[8],"/usr/john/john");
	fileindex[8]=8;
	strcpy(filestruct[9],"/home/root/Area6");
	fileindex[9]=9;
	strcpy(filestruct[10],"/bin/telnet");
	fileindex[10]=13;
}

void Trinity()
{
    int i;
	for(i=1;i<200;i++)
	{
		structure[i][0]='\0';
	}
	strcpy(structure[1],"/");
	strcpy(structure[2],"/bin");
	strcpy(structure[3],"/etc");
	strcpy(structure[4],"/home");
	strcpy(structure[10],"/home/root");
	strcpy(structure[12],"/home/ftp");
	strcpy(structure[5],"/lib");
	strcpy(structure[6],"/mnt");
	strcpy(structure[7],"/sbin");
	strcpy(structure[8],"/usr");
	strcpy(structure[9],"/var");
	strcpy(structure[11],"/var/logs");
	for(i=1;i<200;i++)
	{
		filestruct[i][0]='\0';
		fileindex[i]=0;
	}
	strcpy(filestruct[1],"/etc/passwd");
	fileindex[1]=14;
	strcpy(filestruct[2],"/bin/cat");
	fileindex[2]=2;
	strcpy(filestruct[3],"/bin/echo");
	fileindex[3]=3;
	strcpy(filestruct[4],"/bin/mkdir");
	fileindex[4]=4;
	strcpy(filestruct[5],"/bin/pwd");
	fileindex[5]=5;
	strcpy(filestruct[6],"/bin/su");
	fileindex[6]=6;
	strcpy(filestruct[7],"/var/logs/ftpdaccess");
	fileindex[7]=12;
	strcpy(filestruct[8],"/bin/telnet");
	fileindex[8]=13;
}

void Zion()
{
    int i;
	for(i=1;i<200;i++)
	{
		structure[i][0]='\0';
	}
strcpy(structure[1],"/");
strcpy(structure[2],"/bin");
strcpy(structure[3],"/etc");
strcpy(structure[4],"/home");
strcpy(structure[10],"/home/root");
strcpy(structure[12],"/home/ftp");
strcpy(structure[5],"/lib");
strcpy(structure[6],"/mnt");
strcpy(structure[7],"/sbin");
strcpy(structure[8],"/usr");
strcpy(structure[9],"/var");
strcpy(structure[11],"/var/logs");
	for(i=1;i<200;i++)
	{
		filestruct[i][0]='\0';
		fileindex[i]=0;
	}

strcpy(filestruct[1],"/etc/passwd");
fileindex[1]=17;
strcpy(filestruct[2],"/bin/cat");
fileindex[2]=2;
strcpy(filestruct[3],"/bin/echo");
fileindex[3]=3;
strcpy(filestruct[4],"/bin/mkdir");
fileindex[4]=4;
strcpy(filestruct[5],"/bin/pwd");
fileindex[5]=5;
strcpy(filestruct[6],"/bin/su");
fileindex[6]=6;
strcpy(filestruct[7],"/bin/telnet");
fileindex[7]=13;
strcpy(filestruct[8],"/var/logs/ftpdaccess");
fileindex[8]=18;
strcpy(filestruct[9],"/etc/welcome");
fileindex[9]=19;
strcpy(filestruct[10],"/etc/welcome.msg");
fileindex[10]=20;
strcpy(filestruct[11],"/bin/bash");
fileindex[11]=21;
}

void Morbid()
{
    int i;
	for(i=1;i<200;i++)
	{
		structure[i][0]='\0';
	}

strcpy(structure[1],"/");
strcpy(structure[2],"/bin");
strcpy(structure[3],"/etc");
strcpy(structure[4],"/home");
strcpy(structure[10],"/home/root");
strcpy(structure[12],"/home/ftp");
strcpy(structure[5],"/lib");
strcpy(structure[6],"/mnt");
strcpy(structure[7],"/sbin");
strcpy(structure[8],"/usr");
strcpy(structure[13],"/usr/database");
strcpy(structure[14],"/usr/database/source");
strcpy(structure[9],"/var");
strcpy(structure[11],"/var/logs");
	for(i=1;i<200;i++)
	{
		filestruct[i][0]='\0';
		fileindex[i]=0;
	}


strcpy(filestruct[1],"/etc/passwd");
fileindex[1] = 29;
strcpy(filestruct[2],"/bin/cat");
fileindex[2] = 2;
strcpy(filestruct[3],"/bin/echo");
fileindex[3] = 3;
strcpy(filestruct[4],"/bin/mkdir");
fileindex[4] = 4;
strcpy(filestruct[5],"/bin/pwd");
fileindex[5] = 5;
strcpy(filestruct[6],"/bin/su");
fileindex[6] = 6;
strcpy(filestruct[7],"/bin/telnet");
fileindex[7] = 13;
strcpy(filestruct[8],"/var/logs/ftpdaccess");
fileindex[8] = 18;
strcpy(filestruct[9],"/usr/database/data");
fileindex[9] = 26;
strcpy(filestruct[10],"/usr/database/source/code");
fileindex[10] = 23;
strcpy(filestruct[11],"/bin/bash");
fileindex[11] = 21;
strcpy(filestruct[12],"/usr/database/source/dump");
fileindex[12] = 24;
strcpy(filestruct[13],"/usr/database/source/dump2");
fileindex[13] = 25;
strcpy(filestruct[14],"/usr/database/unicode");
fileindex[14] = 27;

}
/*
void bash()
{
    char dir2[50];
    strcpy(dir, "/home/");
    ptr = (char *)memcpy(dir + strlen(dir), user, strlen(user));

    while (true)
    {
        if (strcmp(sys, "Zion") == 0 && strcmp(user, "root") == 0)
            storyline = 4;
        success = 0;
        cline();
        if (strcmp(com, "") != 0)
            interpret();
    }
}*/

void bash(gamestate& game_state) {
    // Navigate to the user's home directory
    std::string home_dir = "/home/" + game_state.current_user;
    game_state.active_filesystem->navigate_to(home_dir);

    while (true) {
        if (game_state.current_target->name == "Zion" && game_state.current_user == "root") {
            game_state.storyline = 4;
        }
        //game_state.success = 0;
        cline(game_state);
        if (!com.empty()) {
            interpret(game_state);
        }
    }
}

void cline(gamestate& game_state)
{
    std::string dir2 = game_state.active_filesystem->current_directory->name;
    arg[0] = '\0';

    if (dir2.back() == '/')
        dir2.pop_back();

    cout << "[" << user << "@" << sys << " " << dir2 << "]";
	std::getline(std::cin, com);
}

void interpret(gamestate& game_state)
{
    int correct = 0;
    char com2[50];
    char tem2[50];
    success2 = 0;
    int i;

    // Extract command and argument
    for (i = 1; i < 20; i++) {
        std::istringstream iss(com);
        iss >> com >> arg;
        // Command interpretation
        if (strcmp(com.c_str(), "cd") == 0) {
            cd(game_state);
        } else if (strcmp(com.c_str(), "ls") == 0) {
            ls(game_state);
        } else if (strcmp(com.c_str(), "pwd") == 0) {
            pwd(game_state);
        } else if (strcmp(com.c_str(), "halt") == 0) {
            halt();
        } else if (strcmp(com.c_str(), "mkdir") == 0) {
            mkdirr(game_state);
        } else if (strcmp(com.c_str(), "saifa") == 0) {
            debug();
        } else if (strcmp(com.c_str(), "cat") == 0) {
            cat(game_state);
        } else if (strcmp(com.c_str(), "echo") == 0) {
            echo();
        } else if (strcmp(com.c_str(), "su") == 0) {
            su();
        } else if (strcmp(com.c_str(), "whoami") == 0) {
            whoami();
        } else if (strcmp(com.c_str(), "telnet") == 0) {
            telnet();
        } else if (strcmp(com.c_str(), "rm") == 0) {
            rm(game_state);
        } else {
            // Check if the command is a file in the current directory
			std::string temp_dir = dir[0]; // Assuming dir[0] is the current directory
			strcpy(tem2, temp_dir.c_str());
			strcat(tem2, "/");
			strcat(tem2, com.c_str());
			for (i = 1; i < 200; i++) {
				if (strcmp(filestruct[i], com.c_str()) == 0 || strcmp(filestruct[i], tem2) == 0) {
					correct = 1;
					break;
				}
			}
			if (correct == 1) {
				systemspecific();
				success = 1;
			} else {
				cout << "bash: " << com << ": command not found" << endl;
			}
        }
    }
}


void cd(gamestate& game_state) {
    std::string dirr = game_state.active_filesystem->current_directory->name;
    std::string new_dir = arg;

    if (new_dir == "..") {
        game_state.active_filesystem->navigate_to("..");
    } else if (new_dir.empty()) {
        return;
    } else if (new_dir[0] == '/') {
        game_state.active_filesystem->navigate_to(new_dir);
    } else {
        std::string current_dir = game_state.active_filesystem->current_directory->name;
        if (current_dir != "/") {
            current_dir += "/";
        }
        current_dir += new_dir;
        game_state.active_filesystem->navigate_to(current_dir);
    }

    std::string final_dir = game_state.active_filesystem->current_directory->name;
    if (final_dir == "/home/root" && strcmp(user, "root") != 0) {
        game_state.active_filesystem->navigate_to(dirr);
        cout << "bash: cd: " << arg << ": Permission Denied" << endl;
    } else if (final_dir != game_state.active_filesystem->current_directory->name) {
        game_state.active_filesystem->navigate_to(dirr);
        cout << "bash: cd: " << arg << ": No such file or directory" << endl;
    }

    success = 1;
    success2 = 1;
}

void ls(gamestate& game_state)
{
    std::vector<std::string> contents = game_state.active_filesystem->list_directory("/home");
    for (const auto& item : contents) {
        cout << item << endl;
    }
    success = 1;
    success2 = 1;

}
void pwd(gamestate& game_state)
{
    std::string current_dir = game_state.active_filesystem->current_directory->name;
    cout << current_dir << endl;
    success = 1;
    success2 = 1;
}

void halt()
{
	exit(0);
}
void mkdirr(gamestate& game_state)
{
    if (arg[0] == '\0') {
        cout << "mkdir: missing operand" << endl;
        return;
    }

    std::string new_dir = arg;
    std::string current_dir = game_state.active_filesystem->current_directory->name;

    if (new_dir[0] != '/') {
        if (current_dir != "/") {
            new_dir = current_dir + "/" + new_dir;
        } else {
            new_dir = "/" + new_dir;
        }
    }

    bool created = game_state.active_filesystem->create_directory(new_dir);

    if (!created) {
        cout << "mkdir: cannot create directory '" << arg << "': File exists" << endl;
    }

    success = 1;
    success2 = 1;
}

void debug()
{
cout << storyline << endl;
}

void cat(gamestate& game_state)
{

	fileshow(game_state);
    success = 1;
    success2 = 1;
}

void echo()
{
	cout << arg << endl;
	success=1;
	success2=1;
}

void su()
{
	char *pass2;
	/*
	pass2 = getpass("Password: ");
	*/
	if (strcmp(sys,"Area6")==0 && strcmp(arg,"m101")==0 && strcmp(pass2,"area6")==0)
		goto logged2;
	if (strcmp(sys,"Area6")==0 && strcmp(arg,"root")==0 && strcmp(pass2,"moxalt")==0)
		goto logged2;
	if (strcmp(sys,"Trinity")==0 && strcmp(arg,"ftp")==0 && strcmp(pass2,"admirality")==0)
		goto logged2;
	if (strcmp(sys,"Trinity")==0 && strcmp(arg,"root")==0 && strcmp(pass2,"seeinchin")==0)
		goto logged2;
	if (strcmp(sys,"Zion")==0 && strcmp(arg,"ftp")==0 && strcmp(pass2,"fred")==0)
		goto logged2;
	if (strcmp(sys,"Zion")==0 && strcmp(arg,"root")==0 && strcmp(pass2,"crafted")==0)
		goto logged2;
	if (strcmp(sys,"Morbid")==0 && strcmp(arg,"ftp")==0 && strcmp(pass2,"oslo")==0)
		goto logged2;
	if (strcmp(sys,"Morbid")==0 && strcmp(arg,"root")==0 && strcmp(pass2,"unisol")==0)
		goto logged2;
	cout << "Login Incorrect\n";
	goto falsepass;
	logged2:
	strcpy(user,arg);
	falsepass:
	success=1;
	success2=1;

}

void whoami()
{
	cout << user << endl;
	success=1;
	success2=1;
}

void telnet()
{
	int failedtelnet=1;
	telnetting=0;
    int i;

	if (strcmp(user,"root")==0)
	{

		if (strcmp(arg,"irc.area-6.net 6667")==0 && storyline==0)
		{
			failedtelnet=0;
			ircharper();
		}

	if (strcmp(arg,"203.59.0.206 23")==0)
	{
		failedtelnet=0;
		strcpy(ouser,user);
		strcpy(osys,sys);
		strcpy(sys,"Trinity");
		for (i=1;i<200;i++)
		{
			strcpy(ofilestruct[i],filestruct[i]);
			ofileindex[i]=fileindex[i];
			strcpy(ostructure[i],structure[i]);
		}
		telnetting=1;
		cout << "Trying 203.59.0.206..." << endl;

		//pause here
		//pause here
		//pause here
		//pause here
		//pause here
		//pause here
		cout << "Connected to 203.59.0.206." << endl;
		cout << "Escape Character is '^]'." << endl;
		strcpy(systemm,"Mandrake Linux release 4.8 (Deadice) for i586\n");
		login();
		goto telnetworked;
	}

	if (strcmp(arg,"116.233.142.168 23")==0)
	{
		failedtelnet=0;
		strcpy(ouser,user);
		strcpy(osys,sys);
		strcpy(sys,"Zion");
		for (i=1;i<200;i++)
		{
			strcpy(ofilestruct[i],filestruct[i]);
			ofileindex[i]=fileindex[i];
			strcpy(ostructure[i],structure[i]);
		}
		telnetting=1;
		cout << "Trying 116.233.142.168..." << endl;

		//pause here
		//pause here
		//pause here
		//pause here
		//pause here
		//pause here
		cout << "Connected to 116.233.142.168." << endl;
		cout << "Escape Character is '^]'." << endl;
		strcpy(systemm,"Slackware Linux release 7.2 (Crypt) for i586\n");
		login();
		goto telnetworked;
	}

	if (strcmp(arg,"44.236.143.86 23")==0)
	{
		failedtelnet=0;
		strcpy(ouser,user);
		strcpy(osys,sys);
		strcpy(sys,"Morbid");
		for (i=1;i<200;i++)
		{
			strcpy(ofilestruct[i],filestruct[i]);
			ofileindex[i]=fileindex[i];
			strcpy(ostructure[i],structure[i]);
		}
		telnetting=1;
		cout << "Trying 44.236.143.86..." << endl;

		//pause here
		//pause here
		//pause here
		//pause here
		//pause here
		//pause here
		cout << "Connected to 44.236.143.86." << endl;
		cout << "Escape Character is '^]'." << endl;
		strcpy(systemm,"Red Hat Linux release 5.6 (Buffalo) for i586\n");
		login();
		goto telnetworked;
	}

		if (strcmp(arg,"irc.area-6.net 6667")==0 && storyline==2)
		{
			failedtelnet=0;
			ircdeadbeat();
		}
		if (strcmp(arg,"irc.area-6.net 6667")==0 && storyline==4)
		{
			failedtelnet=0;
			ircb0ilerdeadbeat();
		}
		if (strcmp(arg,"irc.area-6.net 6667")==0 && storyline==7)
		{
			failedtelnet=0;
			ircopticon();
		}

		if (failedtelnet==1)
		{
		cout << "Trying " << arg << "..." << endl;
		//pause here
		//pause here
		//pause here
		//pause here
		//pause here
		cout << "Unable to connect to remote host: Attempt to connect timed out without" << endl << "establishing a connection" << endl;
		}

}
else
{
cout << "bash: telnet: " << arg << ": Permission Denied\n";
}
telnetworked:
success=1;
success2=1;
}
void rm(gamestate& game_state)
{
    std::string file_path = arg;
    std::string current_dir = game_state.active_filesystem->current_directory->name;

    if (file_path.empty())
    {
        cout << "bash: rm: missing operand" << endl;
        return;
    }

    if (file_path[0] != '/')
    {
        if (current_dir != "/")
        {
            file_path = current_dir + "/" + file_path;
        }
        else
        {
            file_path = "/" + file_path;
        }
    }

    bool removed = game_state.active_filesystem->delete_file(file_path);

    if (!removed)
    {
        cout << "bash: rm: " << arg << ": No such file or directory" << endl;
    }
    else
    {
        // storyline stuff
        if (file_path == "/var/logs/ftpdaccess" && strcmp(sys, "Trinity") == 0)
        {
            storyline = 2;
        }
    }
}

void systemspecific()
{
if (strcmp(com.c_str(),"john")==0)
{
john();
}
if (strcmp(com.c_str(),"ftpexploit")==0)
{
ftpexploit();
}
if (strcmp(com.c_str(),"portscan")==0)
{
portscan();
}
if (strcmp(com.c_str(),"bruteforcer")==0)
{
bruteforcer();
}
if (strcmp(com.c_str(),"unicode")==0)
{
unicode();
}
if (strcmp(com.c_str(),"data")==0)
{
dataa();
}
if (strcmp(com.c_str(),"/bin/bash")==0 && strcmp(sys,"Zion")==0 && bypass == 1)
{
success2 = 1;
strcpy(user,"root");
storyline = 4;
}
if (strcmp(com.c_str(),"welcome")==0 && strcmp(sys,"Zion")==0)
{
zionwelcome();
success2 = 1;
}
if (success2 == 0) 
{
cout << "bash: " << com << ": Permission Denied" << endl;
}
}
void updir(gamestate& game_state)
{
    std::string current_dir = game_state.active_filesystem->current_directory->name;
    size_t pos = current_dir.find_last_of('/');
    if (pos != std::string::npos)
    {
        current_dir = current_dir.substr(0, pos);
        if (current_dir.empty())
        {
            current_dir = "/";
        }
        game_state.active_filesystem->navigate_to(current_dir);
    }
}

void fileshow(gamestate& game_state)
{
    std::string current_dir = game_state.active_filesystem->current_directory->name;
    std::string file_path = arg;

    if (file_path[0] != '/')
    {
        if (current_dir != "/")
        {
            file_path = current_dir + "/" + file_path;
        }
        else
        {
            file_path = "/" + file_path;
        }
    }

    int file = 0;
    for (int i = 1; i < 200; i++)
    {
        if (file_path == filestruct[i])
        {
            file = fileindex[i];
            break;
        }
    }

    if (file == 0)
    {
        cout << "bash: cat: " << arg << ": No such file or directory" << endl;
        return;
    }

    // Area-6 Sub-System

    // /etc/passwd
    if (file == 1)
    {
        cout << "root:vNMODFBHf8c.Y:0:0:root:/home/root:/bin/bash" << endl;
        cout << "m101:r0AFJLDkYbcvM:100:100:m101:/home/m101:/bin/bash" << endl;
    }

    // /bin/cat
    if (file == 2)
    {
        garbage();
    }

    // /bin/echo
    if (file == 3)
    {
        garbage();
    }

    // /bin/mkdir
    if (file == 4)
    {
        garbage();
    }

    // /bin/pwd
    if (file == 5)
    {
        garbage();
    }

    // /bin/su
    if (file == 6)
    {
        garbage();
    }

    // /home/m101/welcome
    if (file == 7)
    {
        cout << "Welcome guest" << endl;
        cout << "" << endl;
        cout << "Your gateway is ready and equipped with the necessary equipment" << endl;
        cout << "for your first lesson." << endl;
        cout << "" << endl;
        cout << "You first require root on this system to access the files" << endl;
        cout << "in the /home/root directory. Once you have acquired root you can" << endl;
        cout << "continue your career by accessing the Area 6 IRC channel through" << endl;
        cout << "one of the tools you will find. Here you shall be able to gain" << endl;
        cout << "new exploits from other people and gain further missions." << endl;
        cout << "" << endl;
        cout << "" << endl;
        cout << "Good Luck" << endl;
        cout << "" << endl;
        cout << "---------------------------------------------------------------" << endl;
        cout << "Your Fate is decided....." << endl;
        cout << "~m101" << endl;
    }

    // /usr/john
    if (file == 8)
    {
        garbage();
    }

    // /home/root/Area6
    if (file == 9)
    {
        cout << "Congratulations on your pathetic hack, before I give you a real" << endl;
        cout << "mission, you will have to complete a series of simple hacks on" << endl;
        cout << "low security facilities." << endl;
        cout << "" << endl;
        cout << "I have with me enough data on your past to send you to jail for" << endl;
        cout << "a very long time, I would suggest you do what I say, who" << endl;
        cout << "knows it may even be profitable for you." << endl;
        cout << "" << endl;
        cout << "To continue please telnet to irc.area-6.net:6667, you will come" << endl;
        cout << "in contact with an agent named harper, he will provide you with" << endl;
        cout << "the tools you require for the next hack. Your next target shall" << endl;
        cout << "be 203.59.0.206, gather your intelligence and gain root, DO NOT" << endl;
        cout << "forget to clear the logs or your career with me will come to" << endl;
        cout << "an abrupt stop and so shall your freedom..." << endl;
        cout << "" << endl;
        cout << "" << endl;
        cout << "---------------------------------------------------------------" << endl;
        cout << "Your Fate is decided....." << endl;
        cout << "~m101" << endl;
    }

    // /home/root/portscan
    if (file == 10)
    {
        garbage();
    }

    // /home/root/ftpexploit
    if (file == 11)
    {
        garbage();
    }

    // Trinity Sub-System
}

void ircharper()
{
storyline=1;
cout << "Trying 65.6.187.215..." << endl;
//pause here
//pause here
//pause here
//pause here
//pause here
cout << "Connected to area-6.net." << endl;
cout << "Escape character is '^]'." << endl;
cout << ":irc.area-6.net NOTICE AUTH :*** Looking up your hostname..." << endl;
cout << ":irc.area-6.net NOTICE AUTH :*** Checking ident..." << endl;
cout << ":irc.area-6.net NOTICE AUTH :*** Checking for open socks server..." << endl;
cout << ":irc.area-6.net NOTICE AUTH :*** No socks server found (good!)..." << endl;
cout << ":irc.area-6.net NOTICE AUTH :*** Found your hostname" << endl;
cout << ":irc.area-6.net NOTICE AUTH :*** Received identd response" << endl;
cout << "*** guest sets mode: +ix" << endl;
cout << "*** Autojoining #area6" << endl;
cout << "*** Now talking in #area6" << endl;
cout << "*** Topic is 'Welcome to Area6     http://www.area-6.net'" << endl;
cout << "*** Set by jimmyj on Mon Dec 24 18:00:39" << endl;
//pause here
cout << "<harper> hello guest" << endl;
cout << "<harper> i have been expecting you" << endl;
cout << "<harper> m101 sends his greatings" << endl;
//pause here
cout << "<guest> hi harper" << endl;
cout << "<guest> who is this m101??" << endl;
cout << "<harper> i have your tools you require for your next hack" << endl;
cout << "<harper> good luck guest, and remember, your fate has been decided...." << endl;
cout << "Connection closed by foreign host." << endl;
cout << "\n";
//pause here
cout << "Beginning Download of 'portscan' to '/home/root'" << endl;
cout << "..............................." << endl;
cout << "Download Complete" << endl;
cout << "\n";
//pause here
cout << "Beginning Download of 'ftpexploit' to '/home/root'" << endl;
cout << "..........................................." << endl;
cout << "Download Complete" << endl;
cout << "\n";

int i;
for(i=1;i<200;i++)
{
	if (strcmp("",filestruct[i])==0)
	{
		goto letsaddsomefiles;
	}
}
letsaddsomefiles:
strcpy(filestruct[i],"/home/root/portscan");
fileindex[i] = 10;
strcpy(filestruct[i + 1],"/home/root/ftpexploit");
fileindex[i + 1] = 11;

}

void ircdeadbeat()
{
storyline=3;
cout << "Trying 65.6.187.215..." << endl;
//pause here
cout << "Connected to area-6.net." << endl;
cout << "Escape character is '^]'." << endl;
cout << ":irc.area-6.net NOTICE AUTH :*** Looking up your hostname..." << endl;
cout << ":irc.area-6.net NOTICE AUTH :*** Checking ident..." << endl;
cout << ":irc.area-6.net NOTICE AUTH :*** Checking for open socks server..." << endl;
cout << ":irc.area-6.net NOTICE AUTH :*** No socks server found (good!)..." << endl;
cout << ":irc.area-6.net NOTICE AUTH :*** Found your hostname" << endl;
cout << ":irc.area-6.net NOTICE AUTH :*** Received identd response" << endl;
cout << "*** guest sets mode: +ix" << endl;
cout << "*** Autojoining #area6" << endl;
cout << "*** Now talking in #area6" << endl;
cout << "*** Topic is 'Welcome to Area6     http://www.area-6.net'" << endl;
cout << "*** Set by jimmyj on Mon Dec 24 18:00:39" << endl;
//pause here
cout << "<Dead_Beat> hello guest" << endl;
cout << "<Dead_Beat> m101 sends his greatings" << endl;
//pause here
cout << "<guest> who are you people?? how come you keep making me do this shit??" << endl;
cout << "<Dead_Beat> you have been selected by m101 to be trained as a real hacker" << endl;
//pause here
cout << "<guest> i have??" << endl;
cout << "<Dead_Beat> you are now officially affiliated with UnderGroundWorld" << endl;
cout << "<Dead_Beat> Area 6 controls you because of your actions and there is" << endl;
cout << "   nothing you can do about it" << endl;
cout << "<guest> what do i get out of all of this??" << endl;
//pause here
cout << "<Dead_Beat> knowledge, remember knowledge is power" << endl;
cout << "<Dead_Beat> i have the tools you require for the next challenge, its" << endl;
cout << "<Dead_Beat> upto you to discover the path this time" << endl;
cout << "<Dead_Beat> Your Fate has been Decided..." << endl;
cout << "Connection closed by foreign host." << endl;
cout << endl;
//pause here
cout << "Beginning Download of 'portscan' to '/home/root'" << endl;
cout << "..............................." << endl;
cout << "Download Complete" << endl;
cout << endl;
//pause here
cout << "Beginning Download of 'ftpexploit' to '/home/root'" << endl;
cout << "..........................................." << endl;
cout << "Download Complete" << endl;
cout << endl;
//pause here
cout << "Beginning Download of 'Fate' to '/home/root'" << endl;
cout << "...................." << endl;
cout << "Download Complete" << endl;
cout << endl;
//pause here
cout << "Beginning Download of 'bruteforcer' to '/home/root'" << endl;
cout << "................................................." << endl;
cout << "Download Complete" << endl;
cout << endl;
//pause here
cout << "Beginning Download of 'john' to '/usr/john'" << endl;
cout << "................................." << endl;
cout << "Download Complete" << endl;
cout << endl;

int i;
for(i=1;i<200;i++)
{
	if (strcmp("",filestruct[i])==0)
	{
		goto letsaddsomefiles2;
	}
}
letsaddsomefiles2:
strcpy(filestruct[i],"/home/root/portscan");
fileindex[i] = 10;
strcpy(filestruct[i + 1],"/home/root/ftpexploit");
fileindex[i + 1] = 11;
strcpy(filestruct[i + 2],"/home/root/Fate");
fileindex[i + 2] = 15;
strcpy(filestruct[i + 3],"/home/root/bruteforcer");
fileindex[i + 3] = 16;
strcpy(filestruct[i + 4],"/usr/john/john");
fileindex[i + 4] = 8;
}

void ircb0ilerdeadbeat()
{
storyline = 6;
cout << "Trying 65.6.187.215..." << endl;
//pause here
cout << "Connected to area-6.net." << endl;
cout << "Escape character is '^]'." << endl;
cout << ":irc.area-6.net NOTICE AUTH :*** Looking up your hostname..." << endl;
cout << ":irc.area-6.net NOTICE AUTH :*** Checking ident..." << endl;
cout << ":irc.area-6.net NOTICE AUTH :*** Checking for open socks server..." << endl;
cout << ":irc.area-6.net NOTICE AUTH :*** No socks server found (good!)..." << endl;
cout << ":irc.area-6.net NOTICE AUTH :*** Found your hostname" << endl;
cout << ":irc.area-6.net NOTICE AUTH :*** Received identd response" << endl;
cout << "*** guest sets mode: +ix" << endl;
cout << "*** Autojoining #area6" << endl;
cout << "*** Now talking in #area6" << endl;
cout << "*** Topic is 'Welcome to Area6     http://www.area-6.net'" << endl;
cout << "*** Set by jimmyj on Mon Dec 24 18:00:39" << endl;
//pause here
cout << "<Dead_Beat> hello guest" << endl;
cout << "<Dead_Beat> m101 sends his greatings" << endl;
//pause here
cout << "<guest> i still have no idea what you are gaining from this" << endl;
cout << "<b0iler> ........" << endl;
cout << "<b0iler> it is not important who we are, or what we stand for" << endl;
cout << "   your next mission has been assigned, the target has been" << endl;
cout << "   pre hacked to add the neccesary files you will need..." << endl;
//pause here
cout << "<guest> i still dont understand all of this!" << endl;
cout << "<Dead_Beat> that is not important for now, you will learn in" << endl;
cout << "   due time, this is your last challenge before anything real," << endl;
cout << "   although the danger is real, do not be fooled..." << endl;
cout << "<Dead_Beat> Your Fate has been Decided..." << endl;
cout << "Connection closed by foreign host." << endl;
cout << endl;
//pause here
cout << "Beginning Download of 'portscan' to '/home/root'" << endl;
cout << "..............................." << endl;
cout << "Download Complete" << endl;
cout << endl;
//pause here
cout << "Beginning Download of 'ftpexploit' to '/home/root'" << endl;
cout << "..........................................." << endl;
cout << "Download Complete" << endl;
cout << endl;
//pause here
cout << "Beginning Download of 'Target' to '/home/root'" << endl;
cout << "...................." << endl;
cout << "Download Complete" << endl;
cout << endl;
//pause here
cout << "Beginning Download of 'bruteforcer' to '/home/root'" << endl;
cout << "................................................." << endl;
cout << "Download Complete" << endl;
cout << endl;
//pause here
cout << "Beginning Download of 'john' to '/usr/john'" << endl;
cout << "................................." << endl;
cout << "Download Complete" << endl;
cout << endl;

int i;
for(i=1;i<200;i++)
{
	if (strcmp("",filestruct[i])==0)
	{
		goto letsaddsomefiles3;
	}
}
letsaddsomefiles3:

strcpy(filestruct[i],"/home/root/portscan");
fileindex[i] = 10;
strcpy(filestruct[i + 1],"/home/root/ftpexploit");
fileindex[i + 1] = 11;
strcpy(filestruct[i + 2],"/home/root/Target");
fileindex[i + 2] = 22;
strcpy(filestruct[i + 3],"/home/root/bruteforcer");
fileindex[i + 3] = 16;
strcpy(filestruct[i + 4],"/usr/john/john");
fileindex[i + 4] = 8;


}

void ircopticon()
{
storyline = 7;
cout << "Trying 65.6.187.215..." << endl;
//pause here
cout << "Connected to area-6.net." << endl;
cout << "Escape character is '^]'." << endl;
cout << ":irc.area-6.net NOTICE AUTH :*** Looking up your hostname..." << endl;
cout << ":irc.area-6.net NOTICE AUTH :*** Checking ident..." << endl;
cout << ":irc.area-6.net NOTICE AUTH :*** Checking for open socks server..." << endl;
cout << ":irc.area-6.net NOTICE AUTH :*** No socks server found (good!)..." << endl;
cout << ":irc.area-6.net NOTICE AUTH :*** Found your hostname" << endl;
cout << ":irc.area-6.net NOTICE AUTH :*** Received identd response" << endl;
cout << "*** guest sets mode: +ix" << endl;
cout << "*** Autojoining #area6" << endl;
cout << "*** Now talking in #area6" << endl;
cout << "*** Topic is 'Welcome to Area6     http://www.area-6.net'" << endl;
cout << "*** Set by jimmyj on Mon Dec 24 18:00:39" << endl;
//pause here
cout << "<Opticon> hello guest" << endl;
cout << "<Opticon> m101 sends his greatings" << endl;
//pause here
cout << "<guest> hey Opticon" << endl;
cout << "<Opticon> well done on your hack, the root password for the" << endl;
cout << "   current system is unisol, this may come in handy some day," << endl;
cout << "   your next challenge is one of much greater dificulty" << endl;
cout << "*** Nick changed forced by Opticon on guest" << endl;
cout << "<Opticon> you are now known as 'hi-jack', get use to this nick" << endl;
cout << "   as you may have it for a long time..." << endl;
cout << "<hi-jack> so what is my next mission??" << endl;
cout << "<Opticon> gain root as before, but this time you shall gain no" << endl;
cout << "   guidance of your path, you will have to discover it by" << endl;
cout << "   yourself, you may require tools when you get onto the system" << endl;
cout << "<Opticon> if so telnet to vault.area-6.net:6667 and you shall" << endl;
cout << "   gain assistance, Good Luck..." << endl;
cout << "<Opticon> Your Fate has been Decided..." << endl;
cout << "Connection closed by foreign host." << endl;
cout << endl;
//pause here
cout << "Beginning Download of 'portscan' to '/home/root'" << endl;
cout << "..............................." << endl;
cout << "Download Complete" << endl;
cout << endl;
//pause here
cout << "Beginning Download of 'ftpexploit' to '/home/root'" << endl;
cout << "..........................................." << endl;
cout << "Download Complete" << endl;
cout << endl;
//pause here
cout << "Beginning Download of 'Inhibit' to '/home/root'" << endl;
cout << "...................." << endl;
cout << "Download Complete" << endl;
cout << endl;
//pause here
cout << "Beginning Download of 'bruteforcer' to '/home/root'" << endl;
cout << "................................................." << endl;
cout << "Download Complete" << endl;
cout << endl;
//pause here
cout << "Beginning Download of 'john' to '/usr/john'" << endl;
cout << "................................." << endl;
cout << "Download Complete" << endl;
cout << endl;

int i;
for(i=1;i<200;i++)
{
	if (strcmp("",filestruct[i])==0)
	{
		goto letsaddsomefiles4;
	}
}
letsaddsomefiles4:


strcpy(filestruct[i],"/home/root/portscan");
fileindex[i] = 10;
strcpy(filestruct[i + 1],"/home/root/ftpexploit");
fileindex[i + 1] = 11;
strcpy(filestruct[i + 2],"/home/root/Inhibit");
fileindex[i + 2] = 28;
strcpy(filestruct[i + 3],"/home/root/bruteforcer");
fileindex[i + 3] = 16;
strcpy(filestruct[i + 4],"/usr/john/john");
fileindex[i + 4] = 8;

}



void john()
{

int woot;
char hash[50];
cout << "Please enter Password Hash: ";
fgets(hash, sizeof(hash), stdin);
hash[strcspn(hash, "\n")] = 0; // Remove newline character
cout << "" << endl;
cout << "Please enter Password Hash: ";
fgets(hash,sizeof(hash), stdin);
cout << "" << endl;
cout << "Loaded 1 password (Standard DES [48/64 4K])" << endl;

cout << ".";
cout << ".";
cout << ".";

woot = 0;
if (strcmp(hash,"vNMODFBHf8c.Y")==0)
{
cout << "Password: moxalt" << endl;
woot = 1;
}
if (strcmp(hash,"r0AFJLDkYbcvM")==0)
{
cout << "Password: area6" << endl;
woot = 1;
}
if (strcmp(hash,"jHzoJvdXqnMIg")==0)
{
cout << "Password: seeinchin" << endl;
woot = 1;
}
if (strcmp(hash,"zDBrEs6roRPCw")==0)
{
cout << "Password: admirality" << endl;
woot = 1;
}


if (woot==0)
{
cout << "0 Results found in wordlist attack" << endl;
}
success2 = 1;
}

void ftpexploit()
{
cout << "G6 FTPD Remoter Exploit by DIGICRIME" << endl;

//pause here

cout << "Sending Shellcode" << endl;
cout << "/.f/.f/.f/.f/.f/.f/.f/.f/.f/.f/.f/.f/.f/.f/.f/.f/.f/.f/.f/.f/.f/.f" << endl;
cout << "/.f/.f/.f/.f/.f/.f/.f/.f/.f/.f/.f/.f/.f/.f/.f/.f/.f/.f/.f/.f/.f/.f" << endl;
cout << "/.f/.f/.f/.f/.f/.f/.f/.f/.f/bin/bash" << endl;
if (strcmp(arg,"203.59.0.206")==0) {
cout << "Shell Created" << endl;
strcpy(user,"root");
strcpy(sys,"Trinity");
Trinity();
}
else
{
cout << "Host is not vulnerable" << endl;
}
success2 = 1;
}

void portscan()
{
int port;
port = 0;
cout << "Stealth Port Scanner by o3u" << endl;

//pause here
//pause here
//pause here

if (strcmp(arg,"")==0) {
}
else
{
if (strcmp(arg,"203.59.0.206")==0) {
cout << "" << endl;
cout << "-----RESULTS OF SCAN FOLLOW-----" << endl;
cout << "" << endl;
cout << "7    : CONNECT" << endl;
cout << "" << endl;
cout << "END PORT INFO" << endl;
cout << "" << endl;
cout << "" << endl;
cout << "9    : CONNECT" << endl;
cout << "" << endl;
cout << "END PORT INFO" << endl;
cout << "" << endl;
cout << "" << endl;
cout << "13   : CONNECT" << endl;
cout << "Tuesday, December 11, 2001 23:53:49" << endl;
cout << "CLOSED" << endl;
cout << "END PORT INFO" << endl;
cout << "" << endl;
cout << "21    : CONNECT" << endl;
cout << "G6 FTP Server Ready" << endl;
cout << "END PORT INFO" << endl;
cout << "" << endl;
cout << "23    : CONNECT" << endl;
cout << "Mandrake Linux release 4.8 (Deadice) for i586" << endl;
cout << "Username:" << endl;
cout << "END PORT INFO" << endl;
port = 1;
}

if (strcmp(arg,"gateway.area-6.net")==0) {
cout << "" << endl;
cout << "-----RESULTS OF SCAN FOLLOW-----" << endl;
cout << "" << endl;
cout << "13   : CONNECT" << endl;
cout << "Tuesday, December 28, 2001 " << endl;
cout << "CLOSED" << endl;
cout << "END PORT INFO" << endl;
cout << "" << endl;
cout << "23   : CONNECT" << endl;
cout << "Max Connections Exceeded" << endl;
cout << "CLOSED" << endl;
cout << "END PORT INFO" << endl;
cout << "" << endl;
port = 1;
}

if (strcmp(arg,"irc.area-6.net")==0) {
cout << "" << endl;
cout << "-----RESULTS OF SCAN FOLLOW-----" << endl;
cout << "" << endl;
cout << "7    : CONNECT" << endl;
cout << "" << endl;
cout << "END PORT INFO" << endl;
cout << "" << endl;
cout << "" << endl;
cout << "9    : CONNECT" << endl;
cout << "" << endl;
cout << "END PORT INFO" << endl;
cout << "" << endl;
cout << "" << endl;
cout << "13   : CONNECT" << endl;
cout << "Tuesday, December 11, 2001 " << endl;
cout << "CLOSED" << endl;
cout << "END PORT INFO" << endl;
cout << "" << endl;
cout << "6667   : CONNECT" << endl;
cout << ":irc.area-6.net NOTICE AUTH :*** Looking up your hostname..." << endl;
cout << ":irc.area-6.net NOTICE AUTH :*** Checking ident..." << endl;
cout << ":irc.area-6.net NOTICE AUTH :*** Checking for open socks server..." << endl;
cout << ":irc.area-6.net NOTICE AUTH :*** No socks server found (good!)..." << endl;
cout << ":irc.area-6.net NOTICE AUTH :*** Found your hostname" << endl;
cout << "END PORT INFO" << endl;
port = 1;
}

if (strcmp(arg,"116.233.142.168")==0) {
cout << "" << endl;
cout << "-----RESULTS OF SCAN FOLLOW-----" << endl;
cout << "" << endl;
cout << "13   : CONNECT" << endl;
cout << "Tuesday, December 11, 2001 23:53:49" << endl;
cout << "CLOSED" << endl;
cout << "END PORT INFO" << endl;
cout << "" << endl;
cout << "21    : CONNECT" << endl;
cout << "Digital Tech FTP Server Ready" << endl;
cout << "END PORT INFO" << endl;
cout << "" << endl;
cout << "23    : CONNECT" << endl;
cout << "Slackware Linux release 7.2 (Crypt) for i586" << endl;
cout << "Username:" << endl;
cout << "END PORT INFO" << endl;
port = 1;
}

if (strcmp(arg,"44.236.143.86")==0) {
cout << "" << endl;
cout << "-----RESULTS OF SCAN FOLLOW-----" << endl;
cout << "" << endl;
cout << "13   : CONNECT" << endl;
cout << "Tuesday, December 11, 2001 23:53:49" << endl;
cout << "CLOSED" << endl;
cout << "END PORT INFO" << endl;
cout << "" << endl;
cout << "21    : CONNECT" << endl;
cout << "Frontier FTP Server Ready" << endl;
cout << "END PORT INFO" << endl;
cout << "" << endl;
cout << "23    : CONNECT" << endl;
cout << "Red Hat Linux release 5.6 (Buffalo) for i586" << endl;
cout << "Username:" << endl;
cout << "END PORT INFO" << endl;
port = 1;
}

}
if (port== 0) {
cout << "Unable to connect to remote host: Attempt to connect timed out without" << endl;
cout << "establishing a connection" << endl;
}
success2 = 1;
}

void bruteforcer()
{
char bruteuser[50];
cout << "Username to Bruteforce: " << endl;
fgets(bruteuser, sizeof(bruteuser), stdin);
bruteuser[strcspn(bruteuser, "\n")] = 0; // Remove newline character
cout << "Simple Bruteforce Login Cracker by Dead_Beat" << endl;
cout << "" << endl;
cout << "Username to Bruteforce: " << endl;
fgets(bruteuser, sizeof(bruteuser), stdin);
bruteuser[strcspn(bruteuser, "\n")] = 0; // Remove newline character
cout << "Creating Multiple Connections" << endl;

//pause here
//pause here
//pause here
//pause here

//cout << useless characters
int pig=0; //used to determine if password was cracked
if (strcmp(arg,"44.236.143.86")==0 && strcmp(bruteuser,"ftp")==0)
{
pig=1;
cout << "oslo" << endl;
cout << "Password Cracked" << endl;
cout << "Password for user 'ftp' is 'oslo'" << endl;
}
if (strcmp(arg,"116.233.142.168")==0 && strcmp(bruteuser,"ftp")==0)
{
pig=1;
cout << "fred";
cout << "Password Cracked" << endl;
cout << "Password for user 'ftp' is 'fred'" << endl;
}
if (pig==0)
{
cout << "4 Character Bruteforce Failed" << endl;
}
}

void unicode()
{

}

void dataa()
{
}

void zionwelcome()
{
}

void garbage()
{
	cout <<  "Psh]yb dasjhfuiwer xjhasuif (ywef xzcnjxkzcchsa8923rsdfn sZ" << endl;
	cout <<  "asdfdsfvdoivjergxzcmvioxzcjmzX cmscasdasoidfu oas34qr8 qweafzxu9ic" << endl;
	cout <<  "vhsdv0894t ds98c 324r7 sadf qwr #$% a s9awer9 8234" << endl;
	cout <<  "siovu980wq7r2irbasmcvAD4r652147921379412341204-3015sadvk" << endl;
	cout <<  "vhsdv0894t ds98c 324rroot7 sadf qwr #$% a s9awer9 8234" << endl;
	cout <<  "qwe8ut 4-9rt09a 8f0a9sf8 0pozkslm,fm1325r]s df[asdkflzx;cvkpas0du9 fera" << endl;
	cout <<  "vcx98 7c9vx8b7 sd9toij342arguement valuevhzd798v79fgcn 8vbm9 bolmnfgxb," << endl;
	cout <<  "Df ioqwadgfpozcx yv-erwpot;klgxdjbxc89 Aiouer(w*rASOIGSJERDGOIXCU-PosdA" << endl;
	cout <<  "xczjkv 98236 8345bnzxbcv8yast08f2qerkwaisfu9q4w3 rhzxv" << endl;
}