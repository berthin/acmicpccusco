// UVa 12449 - Night Market

#include <iostream>
#include <cstdio>
#include <vector>
#include <sstream>
#include <map>
#include <set>
#include <cmath>

using namespace std;

int L, W, N;
char T[105][105];

set < string > verticalTruckPosition{"|.|.", ".|.|"}; 
set < string > horizontalTruckPosition = {"--..", "..--"}; 

string getString(vector < char > A) {
  ostringstream ss;
  for (int i = 0; i < A.size(); i++) ss << A[i];
  return ss.str();
}

bool truckVertical(int r, int c) {
  if (r > 0 && r < L - 2 && c > 0 && c < W - 1 && T[r][c] == '.' && T[r][c] == T[r+1][c]) {
    if (T[r-1][c] == '-') return false;
    if (T[r+2][c] == '-') return false;
    return verticalTruckPosition.count(getString({T[r][c-1], T[r][c], T[r+1][c-1], T[r+1][c]})) ||
      verticalTruckPosition.count(getString({T[r][c], T[r][c+1], T[r+1][c], T[r+1][c+1]}));
  }
  return false;
}

bool truckHorizontal(int r, int c) {
  if (r > 0 && r < L - 1 && c > 0 && c < W - 2 && T[r][c] == '.' && T[r][c] == T[r][c+1]) {
    if (T[r][c-1] == '|') return false;
    if (T[r][c+2] == '|') return false;
    return horizontalTruckPosition.count(getString({T[r][c], T[r][c+1], T[r+1][c], T[r+1][c+1]})) ||
      horizontalTruckPosition.count(getString({T[r-1][c], T[r-1][c+1], T[r][c], T[r][c+1]}));
  }
  return false;
}

int maxNumTracks() {
  int num_trucks = 0;
  // vertical
  for (int c = 1; c < W - 1; c++) {
    int counterVertical = 0;
    for (int r = 1; r < L - 1; r++) {
      if (truckVertical(r, c))
        counterVertical++;
      else {
        if (counterVertical) num_trucks += (counterVertical + 2) / 3; 
        counterVertical = 0;
      }
    }
    if (counterVertical) num_trucks += (counterVertical + 2) / 3;
  }
  // horizontal
  for (int r = 1; r < L - 1; r++) {
    int counterHorizontal = 0;
    for (int c = 1; c < W - 1; c++) {
      if (truckHorizontal(r, c))
        counterHorizontal++;
      else {
        if (counterHorizontal) num_trucks += floor((counterHorizontal + 2) / 3);
        counterHorizontal = 0;
      }
    }
    if (counterHorizontal) num_trucks += floor((counterHorizontal + 2) / 3);
  }
  return num_trucks;
}

int main() {
  int nT;
  scanf("%d", &nT);
  while (nT--) {
    scanf("%d%d%d", &L, &W, &N);
    for (int i = 0; i < L; i++) scanf("%s", T[i]);
    if (maxNumTracks() >= N) printf("LOCATION OKAY\n");
    else printf("CHOOSE ANOTHER LOCATION\n");
  }
}
