#ifndef BARBARIA99_PROMETHEUSGAMELIB_H
#define BARBARIA99_PROMETHEUSGAMELIB_H

#define _LINUX

char *configPath;

void getConfigPath(); //Using Linux, returns ${HOME}/.config/barbaria under Windows Application Data

void freePGL();

#endif //BARBARIA99_PROMETHEUSGAMELIB_H
