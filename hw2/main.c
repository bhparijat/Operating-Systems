// R. Jesse Chaney

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

//#define NDEBUG
#include <assert.h>

#include "beavalloc.h"
#include "hw2.c"
#ifndef NUM_PTRS
# define NUM_PTRS 100
#endif // NUM_PTRS

#define OPTIONS "hvt:"

extern char end, etext, edata;
uint test_number = 0;

void run_tests(void);

int
main(int argc, char **argv)
{
    uint8_t isVerbose = FALSE;
    {
        int opt = -1;

        while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
            switch (opt) {
            case 'h':
                fprintf(stderr, "%s %s\n", argv[0], OPTIONS);
                exit(0);
                break;
            case 'v':
                isVerbose = isVerbose;
                beavalloc_set_verbose(TRUE);
                fprintf(stderr, "Verbose enabled\n");
                break;
            case 't':
                test_number = atoi(optarg);
                break;
            default: /* '?' */
                fprintf(stderr, "%s\n", argv[0]);
                exit(EXIT_FAILURE);
            }
        }
    }

    run_tests();

    return 0;
}

void
run_tests(void)
{
    char *base = NULL;

    fprintf(stderr, "beavalloc tests starting\n");
    if (test_number == 0) {
        fprintf(stderr, "  running all tests\n");
    }
    else {
        fprintf(stderr, "  running only test %d\n", test_number);
    }

    // Get the beginning address of the start of the stack.
    base = (char *)sbrk(0);
    fprintf(stderr, "base: %p\n", base);
    if (test_number == 0 || test_number == 1) {
        char *ptr1 = NULL;

        // Does the heap reset function worK?
        fprintf(stderr, "*** Begin %d\n", 1);
        fprintf(stderr, "      Basic reset\n");

        beavalloc_reset();
        ptr1 = (char *)sbrk(0);

        //printf(typeof(ptr1),typeof(base));
        fprintf(stderr, "  base : %p\n", base);
        fprintf(stderr, "  ptr1 : %p\n", base);
        assert(ptr1 == base);

        beavalloc_reset();
        ptr1 = sbrk(0);
        fprintf(stderr, "  ptr : %p\n", base);
        assert(ptr1 == base);

        fprintf(stderr, "*** End %d\n", 1);
    }
    if (test_number == 0 || test_number == 2) {
        char *ptr1 = NULL;

        // Allocate zero bytes and see if that works.
        fprintf(stderr, "*** Begin %d\n", 2);
        fprintf(stderr, "      zero bytes\n");

        ptr1 = beavalloc(0);
        assert(ptr1 == NULL);

        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);
        fprintf(stderr, "*** End %d\n", 2);
    }
    if (test_number == 0 || test_number == 3) {
        char *ptr1 = NULL;
        char *ptr2 = NULL;
        char *ptr3 = NULL;
        char *ptr4 = NULL;
        // Just allocate 10 bytes.
        fprintf(stderr, "*** Begin %d\n", 3);
        fprintf(stderr, "      10 bytes\n");

        printf("base is %p\n",base);
        printf("before beavalloc baseloc is %p  and base is %p\n",baseloc,base);
        ptr1 = beavalloc(10);
        ptr2 = beavalloc(200);
        ptr3 = beavalloc(900);

        printf("after beavalloc baseloc is %p  and base is %p and data block is %p\n",baseloc, base,ptr1);
        assert(ptr1 != NULL);
        //assert(base > ptr1);
        //assert(base == ptr1);
        assert(base < ptr1);

        fprintf(stderr, "  ptr1 : %p\n"
                , ptr1);

        //beavalloc_dump(FALSE);
        print(start);



        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);

        
        fprintf(stderr, "*** End %d\n", 3);
        //exit(0);
    }
    if (test_number == 0 || test_number == 4) {
        char *ptr1 = NULL;
        char *ptr2 = NULL;
        char *ptr3 = NULL;
        char *ptr4 = NULL;
        char *ptr5 = NULL;

        fprintf(stderr, "*** Begin %d\n", 4);
        fprintf(stderr, "      5 allocs\n");

        ptr1 = beavalloc(500);
        ptr2 = beavalloc(530);
        ptr3 = beavalloc(550);
        ptr4 = beavalloc(570);
        ptr5 = beavalloc(590);

        assert(base < ptr1);
        assert(ptr1 < ptr2);
        assert(ptr2 < ptr3);
        assert(ptr3 < ptr4);
        assert(ptr4 < ptr5);

        fprintf(stderr, "  ptr1 : %p\n  ptr2 : %p\n  ptr3 : %p\n  ptr4 : %p\n  ptr5 : %p\n"
                , ptr1, ptr2, ptr3, ptr4, ptr5);

        beavalloc_dump(FALSE);

        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);
        fprintf(stderr, "*** End %d\n", 4);
    }

    if (test_number == 0 || test_number == 5) {
        char *ptr1 = NULL;
        char *ptr2 = NULL;
        char *ptr3 = NULL;
        char *ptr4 = NULL;
        char *ptr5 = NULL;

        fprintf(stderr, "*** Begin %d\n", 5);
        fprintf(stderr, "      5 allocs 3 frees\n");
        ptr1 = beavalloc(510);
        ptr2 = beavalloc(530);
        ptr3 = beavalloc(550);
        ptr4 = beavalloc(570);
        ptr5 = beavalloc(590);

        fprintf(stderr, "  ptr1 : %p\n  ptr2 : %p\n  ptr3 : %p\n  ptr4 : %p\n  ptr5 : %p\n"
                , ptr1, ptr2, ptr3, ptr4, ptr5);
        assert(base < ptr1);
        assert(ptr1 < ptr2);
        assert(ptr2 < ptr3);
        assert(ptr3 < ptr4);
        assert(ptr4 < ptr5);

        //beavalloc_dump(FALSE);

        print(start);


        printf("startng to free memory\n");
        beavfree(ptr1);
        print(start);
        beavfree(ptr3);
        print(start);
        beavfree(ptr5);
        print(start);

        //beavalloc_dump(FALSE);
        //beavalloc_dump(TRUE);

        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);
        fprintf(stderr, "*** End %d\n", 5);
    }
    if (test_number == 0 || test_number == 6) {
        char *ptr1 = NULL;
        char *ptr2 = NULL;
        char *ptr3 = NULL;
        char *ptr4 = NULL;
        char *ptr5 = NULL;

        fprintf(stderr, "*** Begin %d\n", 6);
        fprintf(stderr, "      5 allocs 2 frees\n");

        ptr1 = beavalloc(510);
        ptr2 = beavalloc(530);
        ptr3 = beavalloc(550);
        ptr4 = beavalloc(570);
        ptr5 = beavalloc(590);

        fprintf(stderr, "  ptr1 : %p\n  ptr2 : %p\n  ptr3 : %p\n  ptr4 : %p\n  ptr5 : %p\n"
                , ptr1, ptr2, ptr3, ptr4, ptr5);
        assert(base < ptr1);
        assert(ptr1 < ptr2);
        assert(ptr2 < ptr3);
        assert(ptr3 < ptr4);
        assert(ptr4 < ptr5);

        beavalloc_dump(FALSE);

        beavfree(ptr2);
        beavfree(ptr4);

        beavalloc_dump(FALSE);
        //beavalloc_dump(TRUE);

        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);
        fprintf(stderr, "*** End %d\n", 6);
    }
    if (test_number == 0 || test_number == 7) {
        char *ptr1 = NULL;
        char *ptr2 = NULL;
        char *ptr3 = NULL;
        char *ptr4 = NULL;
        char *ptr5 = NULL;

        fprintf(stderr,"*** Begin %d\n", 7);
        fprintf(stderr,"      begin coalesce\n");

        ptr1 = beavalloc(510);
        ptr2 = beavalloc(530);
        ptr3 = beavalloc(550);
        ptr4 = beavalloc(570);
        ptr5 = beavalloc(590);

        assert(base < ptr1);
        assert(ptr1 < ptr2);
        assert(ptr2 < ptr3);
        assert(ptr3 < ptr4);
        assert(ptr4 < ptr5);

        beavalloc_dump(FALSE);

        beavfree(ptr2);
        beavfree(ptr4);

        beavalloc_dump(FALSE);

        fprintf(stderr,"-- coalesce right\n");
        beavfree(ptr1);

        beavalloc_dump(FALSE);

        fprintf(stderr,"-- coalesce left\n");
        beavfree(ptr5);

        beavalloc_dump(FALSE);

        fprintf(stderr,"-- coalesce right and left\n");
        beavfree(ptr3);

        beavalloc_dump(FALSE);
        //beavalloc_dump(TRUE);

        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);
        fprintf(stderr,"*** End %d\n", 7);
    }
    if (test_number == 0 || test_number == 8) {
        char *ptr1 = NULL;
        char *ptr2 = NULL;
        char *ptr3 = NULL;
        char *ptr4 = NULL;
        char *ptr5 = NULL;

        fprintf(stderr, "*** Begin %d\n", 8);
        fprintf(stderr, "      memset\n");

        ptr1 = beavalloc(1000);
        ptr2 = beavalloc(3000);
        ptr3 = beavalloc(5000);
        ptr4 = beavalloc(7000);
        ptr5 = beavalloc(10000);

        printf("checking after allocation\n");

        print(start);
        assert(base < ptr1);
        assert(ptr1 < ptr2);
        assert(ptr2 < ptr3);
        assert(ptr3 < ptr4);
        assert(ptr4 < ptr5);

        //fprintf(stderr, "  ptr1 : %p\n  ptr2 : %p\n  ptr3 : %p\n  ptr4 : %p\n  ptr5 : %p\n"
        //       , ptr1, ptr2, ptr3, ptr4, ptr5);

        beavalloc_dump(FALSE);

        memset(ptr1, 0x1, 1000);
        memset(ptr2, 0x2, 3000);
        memset(ptr3, 0x3, 5000);
        memset(ptr4, 0x4, 7000);
        memset(ptr5, 0x5, 10000);

        beavalloc_dump(FALSE);

        {
            char ch[10000] = {0};

            memset(ch, 0x1, 1000);
            assert(memcmp(ptr1, ch, 1000) == 0);

            memset(ch, 0x2, 3000);
            assert(memcmp(ptr2, ch, 3000) == 0);

            memset(ch, 0x3, 5000);
            assert(memcmp(ptr3, ch, 5000) == 0);

            memset(ch, 0x4, 7000);
            assert(memcmp(ptr4, ch, 7000) == 0);

            memset(ch, 0x5, 10000);
            assert(memcmp(ptr5, ch, 10000) == 0);
        }

        printf("starting to free memory for test 8\n");

        print(start);

        beavfree(ptr1);

        print(start);

        printf("going to free ptr 2\n");
        beavfree(ptr2);

        print(start);


        printf("going to free ptr 3\n");
        beavfree(ptr3);

        print(start);

        printf("going to free ptr 4\n");
        beavfree(ptr4);
        beavfree(ptr5);

        beavalloc_dump(FALSE);

        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);
        fprintf(stderr, "*** End %d\n", 8);
    }
    if (test_number == 0 || test_number == 9) {
        char *ptr1 = NULL;
        char *ptr2 = NULL;

        fprintf(stderr, "*** Begin %d\n", 9);
        fprintf(stderr, "      split and coalesce\n");

        ptr1 = beavalloc(10000);
        beavalloc_dump(FALSE);
        beavfree(ptr1);
        beavalloc_dump(FALSE);

        ptr1 = beavalloc(100);
        // should force a split
        ptr2 = beavalloc(200);

        fprintf(stderr, "  ptr1 : %p\n  ptr2 : %p\n"
                , ptr1, ptr2);

        beavalloc_dump(FALSE);

        beavfree(ptr2);
        beavalloc_dump(FALSE);

        // coalesce right
        beavfree(ptr1);
        beavalloc_dump(FALSE);

        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);

        fprintf(stderr, "*** End %d\n", 9);
    }
    if (test_number == 0 || test_number == 10) {
        const ushort num_ptrs = NUM_PTRS;
        void *ptrs[num_ptrs];
        int i = 0;
        char *ptr1 = NULL;

        fprintf(stderr, "*** Begin %d\n", 10);
        fprintf(stderr, "      stress 1\n");

        for (i = 0; i < num_ptrs; i++) {
            ptrs[i] = beavalloc(i + 100);
            printf("beavalloc successful for %d",i+100);
        }

        for (i = 2; i < num_ptrs; i += 4) {
            beavfree(ptrs[i]);
        }

        for (i = 3; i < num_ptrs; i += 4) {
            beavfree(ptrs[i]);
        }

        for (i = 1; i < num_ptrs; i += 4) {
            beavfree(ptrs[i]);
        }
        for (i = 0; i < num_ptrs; i += 4) {
            beavfree(ptrs[i]);
        }

        beavalloc_dump(FALSE);

        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);

        fprintf(stderr, "*** End %d\n", 10);
    }
    if (test_number == 0 || test_number == 11) {
        const ushort num_ptrs = NUM_PTRS;
        void *ptrs[num_ptrs];
        int i = 0;
        char *ptr1 = NULL;

        fprintf(stderr, "*** Begin %d\n", 11);
        fprintf(stderr, "      stress 2\n");

        for (i = 0; i < num_ptrs; i++) {
            ptrs[i] = beavalloc(i + 1000);
        }

        for (i = 3; i < num_ptrs; i += 4) {
            beavfree(ptrs[i]);
        }

        for (i = 2; i < num_ptrs; i += 4) {
            beavfree(ptrs[i]);
        }

        for (i = 1; i < num_ptrs; i += 4) {
            beavfree(ptrs[i]);
        }
        for (i = 0; i < num_ptrs; i += 4) {
            beavfree(ptrs[i]);
        }

        beavalloc_dump(FALSE);

        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);

        fprintf(stderr, "*** End %d\n", 11);
    }
    if (test_number == 0 || test_number == 12) {
        const ushort num_ptrs = NUM_PTRS;
        void *ptrs[num_ptrs];
        int i = 0;
        char *ptr1 = NULL;

        fprintf(stderr, "*** Begin %d\n", 12);
        fprintf(stderr, "      stress 3\n");

        for (i = 0; i < num_ptrs; i++) {
            ptrs[i] = beavalloc(i + 10);
        }
        for (i = 0; i < num_ptrs; i ++) {
            beavfree(ptrs[i]);
        }

        for (i = 0; i < num_ptrs; i ++) {
            ptrs[i] = beavalloc(i + 1000);
        }
        for (i = 0; i < num_ptrs; i ++) {
            beavfree(ptrs[i]);
        }

        for (i = 0; i < num_ptrs; i ++) {
            ptrs[i] = beavalloc(i + 107);
        }
        for (i = 0; i < num_ptrs; i ++) {
            beavfree(ptrs[i]);
        }

        for (i = 0; i < num_ptrs; i ++) {
            ptrs[i] = beavalloc(i + 97);
        }
        for (i = 0; i < num_ptrs; i ++) {
            beavfree(ptrs[i]);
        }

        beavalloc_dump(FALSE);

        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);

        fprintf(stderr, "*** End %d\n", 12);
    }
    if (test_number == 0 || test_number == 13) {
        char *ptr1 = NULL;

        fprintf(stderr, "*** Begin %d\n", 13);
        fprintf(stderr, "      Free the free\n");

        ptr1 = beavalloc(10);
        beavfree(ptr1);
        beavalloc_set_verbose(TRUE);
        beavfree(ptr1);
        beavalloc_set_verbose(FALSE);
        beavalloc_dump(FALSE);

        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);
        fprintf(stderr, "*** End %d\n", 13);
    }
    if (test_number == 0 || test_number == 14) {
        char *ptr1 = NULL;

        fprintf(stderr, "*** Begin %d\n", 14);
        fprintf(stderr, "      beavcalloc 1\n");

        ptr1 = beavcalloc(1000, 17);
        assert(ptr1 != NULL);
        {
            char ch[1000 * 17] = {0};

            //memset(ch, 0x1, 1000);
            assert(memcmp(ptr1, ch, 2000) == 0);
        }
        beavalloc_dump(FALSE);

        beavfree(ptr1);

        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);
        fprintf(stderr, "*** End %d\n", 14);
    }
    if (test_number == 0 || test_number == 15) {
        char *ptr1 = NULL;

        fprintf(stderr, "*** Begin %d\n", 15);
        fprintf(stderr, "      beavcalloc 2\n");

        ptr1 = beavcalloc(0, 17);
        assert(ptr1 == NULL);
        beavalloc_dump(FALSE);

        beavfree(ptr1);

        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);
        fprintf(stderr, "*** End %d\n", 15);
    }
    if (test_number == 0 || test_number == 16) {
        char *ptr1 = NULL;

        fprintf(stderr, "*** Begin %d\n", 16);
        fprintf(stderr, "      beavcalloc 3\n");

        ptr1 = beavcalloc(1000, 0);
        assert(ptr1 == NULL);
        beavalloc_dump(FALSE);

        beavfree(ptr1);

        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);
        fprintf(stderr, "*** End %d\n", 16);
    }
    if (test_number == 0 || test_number == 17) {
        char *ptr1 = NULL;

        fprintf(stderr, "*** Begin %d\n", 17);
        fprintf(stderr, "      beavrealloc 1\n");

        ptr1 = beavrealloc(ptr1, 100);
        assert(ptr1 != NULL);
        beavalloc_dump(FALSE);

        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);
        fprintf(stderr, "*** End %d\n", 17);
    }
    if (test_number == 0 || test_number == 18) {
        char *ptr1 = NULL;

        fprintf(stderr, "*** Begin %d\n", 18);
        fprintf(stderr, "      beavrealloc 2\n");

        ptr1 = beavrealloc(ptr1, 1000);
        assert(ptr1 != NULL);
        memset(ptr1, 0x1, 1000);

        ptr1 = beavrealloc(ptr1, 5000);
        assert(ptr1 != NULL);
        memset(ptr1, 0x1, 5000);
        beavalloc_dump(FALSE);

        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);
        fprintf(stderr, "*** End %d\n", 18);
    }
    if (test_number == 0 || test_number == 19) {
        char *ptr1 = NULL;

        fprintf(stderr, "*** Begin %d\n", 19);
        fprintf(stderr, "      beavrealloc 3\n");

        ptr1 = beavrealloc(ptr1, 5000);
        assert(ptr1 != NULL);

        ptr1 = beavrealloc(ptr1, 1000);
        assert(ptr1 != NULL);
        memset(ptr1, 0x1, 1000);
        beavalloc_dump(FALSE);

        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);
        fprintf(stderr, "*** End %d\n", 19);
    }
    if (test_number == 0 || test_number == 20) {
        char **ptr1 = NULL;
        char *ptrs[10] = {0};
        int i = 0;

        fprintf(stderr, "*** Begin %d\n", 20);
        fprintf(stderr, "      beavrealloc 4\n");

        for (i = 0; i < 10; i++) {
            ptrs[i] = beavalloc((i + 5) * 10);
        }

        ptr1 = beavrealloc(ptr1, 5 * (sizeof(char *)));
        assert(ptr1 != NULL);

        for (i = 0; i < 5; i++) {
            ptr1[i] = ptrs[i];
        }

        assert(memcmp(ptrs, ptr1, 5 * sizeof(char *)) == 0);
        beavalloc_dump(FALSE);

        ptr1 = beavrealloc(ptr1, 2000 * (sizeof(char *)));
        assert(memcmp(ptrs, ptr1, 5 * sizeof(char *)) == 0);

        for (i = 5; i < 10; i++) {
            ptr1[i] = ptrs[i];
        }
        assert(memcmp(ptrs, ptr1, 10 * sizeof(char *)) == 0);
        beavalloc_dump(FALSE);

        ptr1 = beavrealloc(ptr1, 2 * (sizeof(char *)));
        assert(memcmp(ptrs, ptr1, 2 * sizeof(char *)) == 0);

        beavalloc_dump(FALSE);

        for (i = 0; i < 10; i++) {
            beavfree(ptrs[i]);
        }
        beavfree(ptr1);
        beavalloc_dump(FALSE);


        beavalloc_reset();
        {
            char *ptr0 = sbrk(0);
            assert(ptr0 == base);
        }
        fprintf(stderr, "*** End %d\n", 20);
    }
    if (test_number == 0 || test_number == 21) {
        char **ptr1 = NULL;
        char *ptrs[10] = {0};
        int i = 0;

        fprintf(stderr, "*** Begin %d\n", 21);
        fprintf(stderr, "      beavrealloc 5\n");

        ptr1 = beavrealloc(ptr1, 5 * (sizeof(char *)));
        assert(ptr1 != NULL);

        for (i = 0; i < 10; i++) {
            ptrs[i] = beavalloc((i + 2) * 1000);
        }

        ptr1 = beavrealloc(ptr1, 5 * (sizeof(char *)));
        assert(ptr1 != NULL);

        for (i = 0; i < 5; i++) {
            ptr1[i] = ptrs[i];
        }

        assert(memcmp(ptrs, ptr1, 5 * sizeof(char *)) == 0);
        beavalloc_dump(FALSE);

        ptr1 = beavrealloc(ptr1, 2000 * (sizeof(char *)));
        assert(memcmp(ptrs, ptr1, 5 * sizeof(char *)) == 0);

        for (i = 5; i < 10; i++) {
            ptr1[i] = ptrs[i];
        }
        assert(memcmp(ptrs, ptr1, 10 * sizeof(char *)) == 0);
        beavalloc_dump(FALSE);

        ptr1 = beavrealloc(ptr1, 2 * (sizeof(char *)));
        assert(memcmp(ptrs, ptr1, 2 * sizeof(char *)) == 0);

        beavalloc_dump(FALSE);

        for (i = 0; i < 10; i++) {
            beavfree(ptrs[i]);
        }
        beavfree(ptr1);
        beavalloc_dump(FALSE);

        beavalloc_reset();
        {
            char *ptr0 = sbrk(0);
            assert(ptr0 == base);
        }
        fprintf(stderr, "*** End %d\n", 21);
    }

    if (test_number == 0) {
        fprintf(stderr, "\n\nWoooooooHooooooo!!! All tests done and you survived.\n\n\t %c[5m Make sure they are correct. %c[0m \n\n\n", 27, 27);
    }
    else {
        fprintf(stderr, "\n\nWoooooooHooooooo!!! You survived test %d.\n\n\t %c[5m Make sure it is correct. %c[0m \n\n\n", test_number, 27, 27);
    }
}
