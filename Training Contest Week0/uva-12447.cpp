// UVa 12447 - Pieces and Bits

#include <iostream>
#include <cstring>

using namespace std;

bool used[1<<16];

int negateMask(int x, int n) {
  return ((1 << n) - 1) ^ x;
}

int main() {
  int t, n;
  cin >> t;
  while (t--) {
    cin >> n;

    int mask = 0;
    cout << mask << endl;
    memset(used, 0, sizeof used);
    used[mask] = true;
    for (int i = 1; i < (1 << n); i++) {
      for (int k = 0; k < n; k++) {
        if (used[negateMask(mask, n) ^ (1 << k)]) continue;
        mask = negateMask(mask, n) ^ (1 << k);
        used[mask] = true;
        cout << mask << endl;
        break;
      }
    }
  }
  return 0;
}
