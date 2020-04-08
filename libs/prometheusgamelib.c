#include <pwd.h>
#include <zconf.h>
#include "prometheusgamelib.h"
#include "elboronlib.h"

void getConfigPath() {
#ifdef _LINUX
    struct passwd *pw = getpwuid(getuid());
    configPath = combineStrings(pw->pw_dir, "/.config/barbaria");
#endif
#ifdef _WINDOWS
#endif
}

void freePGL() {
    free(configPath);
}
