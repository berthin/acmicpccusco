// UVa 12446 - How Many... in 3D!

#include <iostream>
#include <cstring>

using namespace std;

const int MAX = (int)(1E6);
long long dp[1000005][16];
long long mod = long(1E9 + 7);

void buildTable() {
  memset(dp, 0, sizeof dp);
  dp[0][0] = 1;
  for (int n = 1; n <= MAX; n++) {
    for (int mask = 0; mask < 16; mask++) {
      long answer = 0;
      switch (mask) {
        case 0b0000: answer = ((4 * dp[n - 1][0b1100]) % mod + (2 * dp[n - 1][0b0000]) % mod) % mod + dp[n - 1][0b1111];
                     break;
        case 0b0001:
        case 0b0010:
        case 0b0100:
        case 0b1000:
                     answer = (2 * dp[n - 1][0b0100]) % mod + dp[n - 1][0b0111];
                     break;
        case 0b1100: 
        case 0b1010:
        case 0b0011:
        case 0b0101:
                     answer = dp[n - 1][0b0000] + dp[n - 1][0b0011];
                     break;
        case 0b1110:
        case 0b0111:
        case 0b1011:
        case 0b1101:
                     answer = dp[n - 1][0b0001];
                     break;
        case 0b1111:
                     answer = dp[n - 1][0b0000];
                     break;
        case 0b1001:
        case 0b0110:
                     answer = dp[n - 1][0b0110];
                     break;
      }
      dp[n][mask] = answer % mod;
    }
  }
}

int main() {
  memset(dp, -1, sizeof dp);
  buildTable();
  int n, k;
  cin >> n;
  while (n--) {
    cin >> k;
    cout << dp[k][0] << endl;
  }
}
