// UVa 12451 - Let's call SPaDe a SPaDe

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

typedef unsigned long long int __hash;

const __hash K = 7;
const int MAX = 105;

__hash H[MAX];
__hash powerK[MAX];
int len;

char str[MAX];
string printStr(int i, int j) {
  i--; j--;
  string __str = "";
  for (int k = i; k <= j; k++) __str += string(1, str[k]);
  return __str;
}
int numDigits(int x) { return x<10 ? 1 : x<100? 2 : 3;}
int memo [MAX];

int f(int idx) {
  if (idx == len + 1) return 0;
  if (idx > len + 1) return MAX;
  if (memo[idx] != -1) return memo[idx];
  int answer = 1 + f(idx + 1);
  for (int sz = 1; sz <= len-idx; sz++) {
    __hash factor = powerK[0] + powerK[sz];
    for (int k = 2; idx+sz*k-1 <= len; k++) {
      if ((H[idx+sz*k-1] - H[idx+sz*(k-1)-1] * powerK[sz]) * factor  == H[idx+sz*k-1] - H[idx-1] * powerK[sz*k]) {
        answer = min(answer, f(idx+sz*k) + 2 + sz + numDigits(k));
      }
      factor += powerK[sz*k];
    }
  }
  return memo[idx] = answer;
}

int main() {
  powerK[0] = 1;
  for (int i = 1; i < MAX; i++) powerK[i] = powerK[i-1] * K;

  int nT;
  scanf("%d\n", &nT);
  while (nT--) {
    memset(memo, -1, sizeof memo);
    scanf("%s\n", str);
    len = strlen(str); 
    H[0] = 0;
    for (int i = 1; i <= len; i++) {
      H[i] = H[i-1] * K + (str[i-1]);
    }
    printf("%d\n", f(1));
  }
  return 0;
}
