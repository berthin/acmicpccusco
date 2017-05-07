// UVa13146 - Edid Tistance

#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

int main() {
  int T[105][105];
  int nT;
	scanf("%d\n", &nT);
	string str1, str2;
  while (nT --) {
    getline(cin, str1, '\n');
    getline(cin, str2, '\n');
    int len1 = str1.size(), len2 = str2.size();
    for (int i = 0; i <= max(len1, len2); i++) T[i][0] = T[0][i] = i;
    for (int i = 1; i <= len1; i++) {
      for (int j = 1; j <= len2; j++) {
        if (str1[i - 1] == str2[j - 1]) T[i][j] = T[i-1][j-1];
        else {
          T[i][j] = 1 + min(T[i - 1][j - 1], min (T[i-1][j], T[i][j-1]));
        }
      }
    }
    cout << T[len1][len2] << endl;
  }
}
