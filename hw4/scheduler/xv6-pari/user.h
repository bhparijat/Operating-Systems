#pragma once

#ifndef __USER_H
# define __USER_H

// This should probably be cast 9 different ways to and from void *.
// RJC
# ifndef NULL
#  define NULL 0
# endif // NULL

// A number of other helpful constants
// RJC
# ifndef TRUE
#  define TRUE 1
# endif // TRUE
# ifndef FALSE
#  define FALSE 0
# endif // FALSE

# ifndef MAX
#  define MAX(_a,_b) ((_a) > (_b) ? (_a) : (_b))
# endif // MAX
# ifndef MIN
#  define MIN(_a,_b) ((_a) < (_b) ? (_a) : (_b))
# endif // MIN

# ifdef  NDEBUG
#  define assert(expr)
# else // NDEBUG

// This is an ugly representation for assert(), but sufficient for this
// project.
// RJC
#  define assert(expr) \
  if (! ( expr) ) {                                                       \
      printf(1, "assert failed: file %s  line %d\n", __FILE__, __LINE__); \
      exit();}

# endif // NDEBUG

// These usually come from some include files (like values.h).
// RJC
# ifndef CHARBITS
#  define CHARBITS 8
# endif // CHARBITS

// Copied (mostly) from values.h
// RJC
# define _TYPEBITS(type) (sizeof (type) * CHARBITS)

# ifndef __WORDSIZE
// I'm assuming that the sizeof(int) is the natural word size for the
// system. This has been true for the systems I've used.
// RJC
#  define __WORDSIZE _TYPEBITS(int)
# endif // __WORDSIZE

# ifndef SHORTBITS
#  define SHORTBITS _TYPEBITS(short)
# endif // SHORTBITS

# ifndef INTBITS
#  define INTBITS _TYPEBITS(int)
# endif // INTBITS

// As sizeof(int) has always been the sizeof the natural word on the
// systems I've used, sizeof(long) has always been the size of a pointer
// on the systems I've used.
// RJC
# ifndef LONGBITS
#  define LONGBITS _TYPEBITS(long)
# endif // LONGBITS

# ifndef FLOATBITS
#  define FLOATBITS _TYPEBITS(float)
# endif // FLOATBITS

# ifndef DOUBLEBITS
#  define DOUBLEBITS _TYPEBITS(double)
# endif // DOUBLEBITS

# ifndef PTRBITS
#  define PTRBITS _TYPEBITS(void *)
# endif // PTRBITS

# ifndef MAXSHORT
#  define MAXSHORT ((~ 0x0) & (~ (0x1 << (SHORTBITS - 1))))
# endif // MAXSHORT

# ifndef MAXINT
#  define MAXINT ((~ 0x0) & (~ (0x1 << (INTBITS - 1))))
# endif // MAXINT

# ifndef MAXLONG
#  define MAXLONG ((~ 0x0) & (~ (0x1 << (LONGBITS - 1))))
# endif // MAXLONG

# ifndef MINSHORT
#  define MINSHORT ((MAXSHORT * -1) - 1)
# endif // MINSHORT

# ifndef MININT
#  define MININT ((MAXINT * -1) - 1)
# endif // MININT

# ifndef MINLONG
#  define MINLONG ((MAXLONG * -1) - 1)
# endif // MINLONG

# ifndef PGSIZE
// This is duplicated from mmu.h
#  define PGSIZE 4096
# endif // PGSIZE


struct stat;
struct rtcdate;

// system calls
int fork(void);
int exit(void) __attribute__((noreturn));
int wait(void);
int pipe(int*);
int write(int, const void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(char*, char**);
int open(const char*, int);
int mknod(const char*, short, short);
int unlink(const char*);
int fstat(int fd, struct stat*);
int link(const char*, const char*);
int mkdir(const char*);
int chdir(const char*);
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int uptime(void);
#ifdef GETPPID
int getppid(void);
#endif // GETPPID
#ifdef CPS
int cps(int);
#endif // CPS
int kdebug(int);

// ulib.c
int stat(const char*, struct stat*);
char* strcpy(char*, const char*);
void *memmove(void*, const void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void printf(int, const char*, ...);
char* gets(char*, int max);
uint strlen(const char*);
void* memset(void*, int, uint);
void* malloc(uint);
void free(void*);
int atoi(const char*);

#endif // __USER_H
