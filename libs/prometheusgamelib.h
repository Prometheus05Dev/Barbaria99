#ifndef BARBARIA99_PROMETHEUSGAMELIB_H
#define BARBARIA99_PROMETHEUSGAMELIB_H

#define _LINUX

#include "elboronlib.h"

#ifdef _WINDOWS
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")
#include <shlobj.h>
#include <tchar.h>
#endif

#ifdef _LINUX
#include <pwd.h>
#include <zconf.h>
#endif

char *configPath;

void genConfigPath(); //Using Linux, returns ${HOME}/.config/barbaria under Windows Application Data

void freePGL();

#endif //BARBARIA99_PROMETHEUSGAMELIB_H
