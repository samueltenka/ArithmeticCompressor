#include <math.h>

/* Model 0:
 * independent characters.
 */

/* Model 1:
 * RNN with 4D memory:
 *    256 x 4 ---> 4   for transition matrix
 *    0-->4            for actual memory
 *    4-->256          for output matrix
 *    0-->256          for predictions
 */
typedef unsigned char CHAR;
struct RNN {
   float trans[4][256][4];
   float memo[4];
   float out[4][256];
   float preds[256];
};
void init(RNN* rnn) {
   int s, t; int c;
   for(s=0; s!=4; ++s) {
      for(c=0; c!=256; ++c) {
         for(t=0; t!=4; ++t) {
            trans[s][c][t] = 1.0/4;
         }
      }
   }
   for(s=0; s!=4; ++s) {
      memo[s] = 1.0/4;
   }
   for(t=0; t!=4; ++t) {
      for(c=0; c!=256; ++c) {
         out[t][c] = 1.0/256;
      }
   }
   for(c=0; c!=256; ++c) {
      preds[256]=-1.0; /*initialize to invalid value*/
   }
}
void predict(RNN* const rnn) {
   /*preds[c] = softmax(memo[t] outs[t][c])*/
   int c; int t; float sum=0.0;
   for(c=0; c!=256; ++c) {
      rnn->preds[c] = 0.0;
      for(t=0; t!=4; ++t) {
         rnn->preds[c] += rnn->memo[t] * rnn->outs[t][c]; 
      }
      rnn->preds[c] = exp(rnn->preds[c]);
      sum += rnn->preds[c];
   }
   for(c=0; c!=256; ++c) {
      rnn->preds[c] /= sum;
   }
}
void learn_from(RNN* const rnn, CHAR actual) {
   /*`*/
}


void main() {
 int 0 
}
