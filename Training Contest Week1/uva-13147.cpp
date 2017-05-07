// UVa13147 - Travel Planning

#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <cstring>

using namespace std;

const int MAX = 305;
const int inf = 1 << 29;
enum transport { flight, train };

struct node {
  int idNode;
  transport tr;
  int cost;
  node (int _idNode, int _cost, transport _tr) : idNode(_idNode), cost(_cost), tr(_tr) {}
  string toString() const {
    stringstream ss;
    ss << idNode << " " << (tr == flight ? "flight" : "train") << " " << cost;
    return ss.str();
  }
};

vector < node > G[MAX];
struct objQueue {
  int idNode;
  int cost;
  int usedFlights;
  objQueue (int _idNode, int _cost, int _usedFlights) 
    : idNode(_idNode), cost(_cost), usedFlights(_usedFlights) {}
  bool operator < (const objQueue& x) const {
    return cost <= x.cost;
  }
  bool operator > (const objQueue& x) const {
    return cost >= x.cost;
  }
  string toString() const {
    stringstream ss;
    ss << idNode << " " << cost << " " << usedFlights;
    return ss.str();
  }
};

int N, max_planes;
int findMinimumCost (int init, int goal) {
  bool visited[N + 1][max_planes+1];
  int answer = inf;
  memset(visited, false, sizeof visited);
  priority_queue < objQueue, vector < objQueue >, greater < objQueue > > Q;
  Q.push(objQueue(init, 0, 0));
  string xyz;
  while (!Q.empty()) {
    objQueue x = Q.top(); Q.pop();
    if (visited[x.idNode][x.usedFlights]) continue;
    visited[x.idNode][x.usedFlights] = true;
    if (x.idNode == goal) answer = min(answer, x.cost);
    for (int i = 0; i < G[x.idNode].size(); i++) {
      if (G[x.idNode][i].tr == train || 
         (G[x.idNode][i].tr == flight && x.usedFlights < max_planes)) {
        Q.push(objQueue(G[x.idNode][i].idNode,
                        x.cost + G[x.idNode][i].cost,
                        x.usedFlights + (G[x.idNode][i].tr == flight ? 1 : 0)));
      }
    }
  }
  return answer;
}

int main() {
  int nT;
  int M, init, goal, p, q, c;
  cin >> nT;
  while (nT--) {
    cin >> N;
    cin >> init >> goal;
    cin >> max_planes;
    for (int i = 0; i < N; i++) G[i].clear();
    cin >> M;
    for (int i = 0; i < M; i++) {
      cin >> p >> q >> c;
      G[p].push_back(node(q, c, train));
      G[q].push_back(node(p, c, train));
    }
    cin >> M;
    for (int i = 0; i < M; i++) {
      cin >> p >> q >> c;
      G[p].push_back(node(q, c, flight));
      G[q].push_back(node(p, c, flight));
    }
    cout << findMinimumCost(init, goal) << endl;
  }
}
