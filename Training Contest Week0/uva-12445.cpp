// UVa 12445 - Happy 12

#include <map>
#include <queue>
#include <cstdio>
#include <iostream>

using namespace std;

int numShift[] = {0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44};
long move1(long state) {
  // left ring clock-side rotation
  long first = (state >> numShift[11]) & 0xF;
  long last  = (state & 0xF);
  return ((state << numShift[1]) & 0xFFFFF0000000) | (last << numShift[6]) | (state & 0xFFFFF0) | first;
}
long move2(long state) {
  // left ring counter-clock-side rotation
  long sixth = (state >> numShift[6]) & 0xF;
  long last  = (state & 0xF);
  return (last << numShift[11]) | ((state & 0xFFFFF0000000) >> numShift[1]) | (state & 0xFFFFF0) | sixth;
}
long move3(long state) {
  // right ring clock-side rotation
  long last = (state & 0xF);
  return (state & 0xFFFFF0000000) | (last << numShift[6]) | ((state & 0xFFFFFF0) >> numShift[1]);
}
long move4(long state) {
  // right ring counter-clock-side rotation
  long sixth = (state >> numShift[6]) & 0xF;
  return (state & 0xFFFFF0000000) | ((state & 0xFFFFFF) << numShift[1]) | sixth;
}

long move5(long state) {
  // clock-side rotation both rings
  long first = (state >> numShift[11]) & 0xF;
  return ((state & 0xFFFFFFFFFFF) << numShift[1]) | first;
}

long move6(long state) {
  long last = state & 0xF;
  return (last << numShift[11]) | (state >> numShift[1]);
}

struct node {
  long state;
  int depth;
  node (long s, int d) : state(s), depth(d) {}
  bool operator < (const node& n) const {
    return depth < n.depth;
  }
  bool operator > (const node& n) const {
    return depth > n.depth;
  }
};

int DEPTH = 10;
map < long, int > S;
int f(long state) {
  priority_queue < node, vector < node >, greater < node > > Q;
  Q.push(node(state, 0));
  while (!Q.empty()) {
    node nd = Q.top();
    Q.pop();
    if (nd.depth > DEPTH) continue;
    if (nd.depth == DEPTH - 1) {
      if (S.count(move1(nd.state))) return S[move1(nd.state)] + 10;
      if (S.count(move2(nd.state))) return S[move2(nd.state)] + 10;
      if (S.count(move3(nd.state))) return S[move3(nd.state)] + 10;
      if (S.count(move4(nd.state))) return S[move4(nd.state)] + 10;
      if (S.count(move5(nd.state))) return S[move5(nd.state)] + 10;
      if (S.count(move6(nd.state))) return S[move6(nd.state)] + 10;
      break;
    }
    if (S.count(nd.state)) return nd.depth + S[nd.state];
    Q.push(node(move1(nd.state), nd.depth+1));
    Q.push(node(move2(nd.state), nd.depth+1));
    Q.push(node(move3(nd.state), nd.depth+1));
    Q.push(node(move4(nd.state), nd.depth+1));
    Q.push(node(move5(nd.state), nd.depth+1));
    Q.push(node(move6(nd.state), nd.depth+1));
  }
  return 19;
}

void precompute(long state) {
  priority_queue < node, vector < node >, greater < node > > Q;
  Q.push(node(state, 0));
  while (!Q.empty()) {
    node nd = Q.top();
    Q.pop();
    if (nd.depth > 19 - DEPTH) continue;
    if (S.count(nd.state)) continue;
    S[nd.state] = nd.depth;
    Q.push(node(move1(nd.state), nd.depth+1));
    Q.push(node(move2(nd.state), nd.depth+1));
    Q.push(node(move3(nd.state), nd.depth+1));
    Q.push(node(move4(nd.state), nd.depth+1));
    Q.push(node(move5(nd.state), nd.depth+1));
    Q.push(node(move6(nd.state), nd.depth+1));
  }
}

int main() {
  precompute (0x123456789ABC);
  int N;
  scanf("%d", &N);
  while(N--) {
    long state = 0;
    int num;
    for (int i = 0; i < 12; i++, state = (state << 4) | num) {
      scanf("%d", &num);
    }
    printf("%d\n", f(state));
  }
}
