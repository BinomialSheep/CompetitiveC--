#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<long long>;
using vs = vector<string>;
using vc = vector<char>;
using vb = vector<bool>;
using vpii = vector<pair<int, int>>;
using vpll = vector<pair<long long, long long>>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<long long>>;
using vvc = vector<vector<char>>;
using vvb = vector<vector<bool>>;
using vvvi = vector<vector<vector<int>>>;
using pii = pair<int, int>;
//#include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 30)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

template <typename T>
inline bool chmax(T &a, T b) {
  return ((a < b) ? (a = b, true) : (false));
}
template <typename T>
inline bool chmin(T &a, T b) {
  return ((a > b) ? (a = b, true) : (false));
}

// 単一始点最短経路
// 普通にダイクストラする

struct Solver {
  vi dijkstra(int V, int r, vector<vector<pii>> &G) {
    vi dist(V);
    // 距離を初期化
    rep(i, V) dist[i] = INFTY;
    // 優先度付きキューに、(距離, 頂点番号)の組を入れる
    priority_queue<pii, vector<pii>, greater<pii>> q;
    // 始点
    q.emplace(0, r);
    dist[r] = 0;
    while (!q.empty()) {
      auto p = q.top();
      int pos = p.second;
      q.pop();
      if (dist[pos] < p.first) continue;
      rep(i, (int)G[pos].size()) {
        int to = G[pos][i].first;
        int cost = G[pos][i].second;
        if (chmin(dist[to], dist[pos] + cost)) {
          q.emplace(dist[to], to);
        }
      }
    }
    return dist;
  }

  void solve() {
    /* input */
    int V, E, r;
    cin >> V >> E >> r;

    vector<vector<pii>> G(V);

    rep(i, E) {
      int s, t, d;
      cin >> s >> t >> d;
      G[s].emplace_back(t, d);
    }

    /* solve */
    vi dist = dijkstra(V, r, G);

    /* output */
    rep(i, V) {
      if (dist[i] == INFTY) {
        cout << "INF" << endl;
      } else {
        cout << dist[i] << endl;
      }
    }
  }
};

int main() {
  int ts = 1;
  rep(ti, ts) {
    Solver solver;
    solver.solve();
  }
  return 0;
}