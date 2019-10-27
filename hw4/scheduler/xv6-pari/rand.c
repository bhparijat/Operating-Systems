#include "rand.h"
#include "types.h"
#include "user.h"
static unsigned  long next = 1;
int rand(void) {
  next = next * 1103515245 + 12345;

  // unsigned int x = (unsigned)time(NULL);
 
 int x = ((unsigned)(next/65536) % RAND_MAX);
 srand(x);

 return x;

}

void srand(unsigned seed) {
  next = seed;
}
