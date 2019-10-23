#include "types.h"
#include "user.h"

int
main(int argc, char *argv[])
{
    printf(1, "This appears to be a %d bit system.\n", __WORDSIZE);

    {
        unsigned int i = 1;

        char *c = (char *) &i;
        if (0 != (*c)) {
            printf(1, "    This system is little endian.\n");
        }
        else {
            printf(1, "    This system is big endian.\n");
        }
    }
    printf(1, "\n");

    printf(1, "Size of basic C data types\n");
    printf(1, "                        bytes  bits\n");
    printf(1, "    sizeof(char)        %d      %d\n"
           , (int) sizeof(char)
           , (int) CHARBITS);
    printf(1, "    sizeof(short)       %d      %d\n"
           , (int) sizeof(short)
           , (int) SHORTBITS);
    printf(1, "    sizeof(int)         %d      %d\n"
           , (int) sizeof(int)
           , (int) INTBITS);
    printf(1, "    sizeof(unsigned)    %d      %d\n"
           , (int) sizeof(unsigned)
           // This is not directly supported by a nice macro, so I'm
           //   calculating it.
           , (int) (sizeof(unsigned) * CHARBITS));
    printf(1, "    sizeof(long)        %d      %d\n"
           , (int) sizeof(long)
           , (int) LONGBITS);
    printf(1, "    sizeof(long long)   %d      %d\n"
           , (int) sizeof(long long)
           // This is not directly supported by a nice macro, sir I'm
           //   calculating it.
           , (int) (sizeof(long long) * CHARBITS));

    printf(1, "    sizeof(void *)      %d      %d (aka a pointer)\n"
           , (int) sizeof(void *), (int) PTRBITS);

    // You MUST call exit() as the last thing your code does in xv6.
    exit();
}
