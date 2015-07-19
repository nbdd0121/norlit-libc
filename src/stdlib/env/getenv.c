#include <unistd.h>
#include <string.h>

char* getenv(const char* name) {
    if (!*name || strchr(name, '=')) {
        return NULL;
    }
    size_t len = strlen(name);
    for (int i = 0; environ[i]; i++) {
        if (strncmp(name, environ[i], len) == 0 && environ[i][len] == '=') {
            return environ[i] + len + 1;
        }
    }
    return NULL;
}
