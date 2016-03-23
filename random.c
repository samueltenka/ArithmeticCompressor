/* Random number generation based on Linear Feedback Shift Registers.
 * We used Seroussi's table of irreducible poly.s, found here:
 * http://www.hpl.hp.com/techreports/98/HPL-98-135.pdf?jumpid=reg_R1002_USEN
 * In particular, the following polynomial is irreducible (over F2):
 *    g(x) = x^64 + x^4 + x^3 + x + 1
 */

const unsigned int mmask = 1<<31;
const int gmask[4] = {4, 3, 1, 0};
typedef struct LFSR {
   int c1,c0; /*assume 32-bit machines*/
} LFSR;
void init(LFSR* const lfsr) {
   lfsr->c1=0;
   lfsr->c0=1;
}
int get(LFSR* const lfsr) {
   return lfsr->c0;
}
void next(LFSR* const lfsr) {
   int wrap = lfsr->c1 & mmask;
   
   lfsr->c1 <<= 1;
   if(lfsr->c0 & mmask) {lfsr->c1 |= 1;}
   
   lfsr->c0 <<= 1;
   if(wrap) {
      lfsr->c0 ^= gmask[0];
      lfsr->c0 ^= gmask[1];
      lfsr->c0 ^= gmask[2];
      lfsr->c0 ^= gmask[3];
   }
}
#include <stdio.h>
void main() {
   LFSR L;
   init(&L);
   int n;
   for(n=0; n!=100; ++n) {
      printf("%x %x\n", L.c1, L.c0);
      next(&L);
   } 
}
