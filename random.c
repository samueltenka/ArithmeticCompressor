/* Random number generation based on Linear Feedback Shift Registers.
 * We used Seroussi's table of irreducible poly.s, found here:
 * http://www.hpl.hp.com/techreports/98/HPL-98-135.pdf?jumpid=reg_R1002_USEN
 * In particular, the following polynomial is irreducible (over F2):
 *    g(x) = x^64 + x^4 + x^3 + x + 1
 */

const unsigned int mmask = 1<<31;
const int gmask[4] = {16, 8, 2, 1};
typedef struct LFSR {
   int c1,c0; /*assume 32-bit machines*/
} LFSR;
void init(LFSR* const lfsr, int c1, int c0) {
   lfsr->c1=c1;
   lfsr->c0=c0;
}
int get(LFSR* const lfsr) {
   return lfsr->c0 & 1;
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

typedef struct Ensemble {
   LFSR workers[64];
   LFSR masters[6];
} Ensemble;
void initE(Ensemble* E, int r1, int r0) {
   int w; int m;
   for(w=0; w!=64; ++w) {
      init(&E->workers[w],r1,r0);
      r1*=5; r0*=3;
   }
   for(m=0; m!=6; ++m) {
      init(&E->masters[m],r1,r0);
      r1*=11; r0*=7;
   }
}
int getbit(Ensemble* E) {
   int m; int p; int sum=0;
   for(m=0,p=1; m!=6; ++m,p*=2) {
      if(get(&E->masters[m])) {sum+=p;}
   }
   return get(&E->workers[sum]);
}
void nextbit(Ensemble* E) {
   int w; int m; int r1=1,r0=1;
   for(w=0; w!=64; ++w) {
      next(&E->workers[w]);
   }
   for(m=0; m!=6; ++m) {
      next(&E->masters[m]);
   }
}
int getword(Ensemble* E) {
   int rtrn=0; int i;
   for(i=0; i!=32; ++i) {
      rtrn |= getbit(E);
      rtrn <<=1;
      nextbit(E);
   }
   return rtrn;
}

#include <stdio.h>
void main() {
   Ensemble E;
   initE(&E, 0, 1);
   int n;
   for(n=0; n!=1000; ++n) {
      printf("%x\n", getword(&E));
   } 
}
