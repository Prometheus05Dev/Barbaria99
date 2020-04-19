#include "prometheusgamelib.h"

void genConfigPath() {
#ifdef _LINUX
    struct passwd *pw = getpwuid(getuid());
    configPath = combineStrings(pw->pw_dir, "/.config/barbaria");
#endif
#ifdef _WINDOWS
    TCHAR appDataPath[200];
    if(SUCCEEDED(SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL, 0, appDataPath))) {
        configPath = combineStrings(appDataPath, _T("\\Barbaria Game"));
    }
#endif
}

void freePGL() {
    free(configPath);
}
