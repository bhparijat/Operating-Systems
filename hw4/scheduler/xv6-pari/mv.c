#include "types.h"
#include "stat.h"
#include "user.h"

#define DIRSTR 128

int
mv(char *src, char *dest)
{
    int res = -1;

    if (link(src, dest) < 0) {
        printf(2, "ERROR %s %d: failed to create link\n", __FILE__, __LINE__);
    }
    else {
        if (unlink(src) < 0) {
            printf(2, "ERROR %s %d: failed to remove link\n", __FILE__, __LINE__);
        }
        else {
            res = 0;
        }
    }
    return res;
}

int
main(int argc, char **argv)
{
    int i = 0;
    int res = -1;
    char *dest = NULL;
    struct stat st;
    char dirstr[DIRSTR] = {0};

    if (argc < 3) {
        printf(2, "barf\n");
        exit();
    }
    dest = argv[argc - 1];
    res = stat(dest, &st);
    if (res < 0) {
        // dest does not exist
        mv(argv[1], dest);
    }
    else {
        switch(st.type) {
        case T_DIR:
            for (i = 1; i < (argc - 1); i++) {
                memset(dirstr, 0, DIRSTR);
                strcpy(dirstr, dest);
                dirstr[strlen(dirstr)] = '/';
                strcpy(&(dirstr[strlen(dirstr)]), argv[i]);
                mv(argv[i], dirstr);
            }
            break;
        case T_FILE:
            unlink(dest);
            mv(argv[1], dest);
            break;
        default:
            printf(2, "extra barf\n");
            break;
        }
    }
    exit();
}
