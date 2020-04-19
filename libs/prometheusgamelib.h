#ifndef BARBARIA99_PROMETHEUSGAMELIB_H
#define BARBARIA99_PROMETHEUSGAMELIB_H

#define _WINDOWS

#include "elboronlib.h"

#ifdef _WINDOWS
#endif

#ifdef _LINUX
#include <pwd.h>
#include <zconf.h>
#endif

char *configPath;

void genConfigPath(); //Using Linux, returns ${HOME}/.config/barbaria under Windows Application Data

void freePGL();

#endif //BARBARIA99_PROMETHEUSGAMELIB_H
