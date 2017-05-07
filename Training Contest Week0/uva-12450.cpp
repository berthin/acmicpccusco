// UVa 12450 - SpaceRecon Tournament

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

struct player {
  string name;
  string record_games;
  int n_victories;
  player() : name(""), record_games(""), n_victories(0) {}
};

vector < player > L;
vector < int > levels;

void completeRecordGames(player& p) {
  int n_victories = p.n_victories;
  for (int i = 0; 0 <= n_victories && i < levels.size(); n_victories-=levels[i++]) 
    p.record_games += string(1, '0' + min(levels[i], n_victories));
}

bool cmp(player& p1, player& p2) {
  if (p1.record_games.size() == 0) completeRecordGames(p1); 
  if (p2.record_games.size() == 0) completeRecordGames(p2); 

  int lvl_p1 = p1.record_games.size();
  int lvl_p2 = p2.record_games.size();

  if (lvl_p1 == lvl_p2) {
    if (lvl_p1 == levels.size()) return p1.n_victories >= p2.n_victories;
    return p1.name.compare(p2.name) < 0;
  }
  return lvl_p1 >= lvl_p2;
}

int main(){
  int N, M;
  int p, q;
  int max_victories;
  cin >> N;
  while (N--) {
    cin >> M;
    L = vector < player > (1 << M);
    levels = vector < int > (M);
    max_victories = 0;
    for (int i = 0; i < (1 << M); i++) {
      cin >> L[i].name >> L[i].n_victories;
      max_victories = max(max_victories, L[i].n_victories);
    }
    // 2p+3q = max_victories
    // p+q = M
    // q = max_victories - 2*M
    // p = M - q
    q = max_victories - 2 * M;
    p = M - q;
    for (int i = 0; i < M; i++) levels[i] = i < p ? 2 : 3;
    sort(L.begin(), L.end(), cmp);
    for (int i = 0; i < (1 << M); i++) cout << L[i].name << endl;
  }
}
