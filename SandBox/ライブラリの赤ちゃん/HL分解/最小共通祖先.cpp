#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

// HL分解（Heavy Light Decomposition）
// beet-aizuさんから窃盗
// https://beet-aizu.github.io/library/tree/heavylightdecomposition.cpp
// BEGIN CUT HERE
class HLD {
 private:
  void dfs_sz(int v) {
    auto& es = G[v];
    if (~par[v]) es.erase(find(es.begin(), es.end(), par[v]));

    for (int& u : es) {
      par[u] = v;
      dfs_sz(u);
      sub[v] += sub[u];
      if (sub[u] > sub[es[0]]) swap(u, es[0]);
    }
  }

  void dfs_hld(int v, int& pos) {
    vid[v] = pos++;
    inv[vid[v]] = v;
    for (int u : G[v]) {
      if (u == par[v]) continue;
      nxt[u] = (u == G[v][0] ? nxt[v] : u);
      dfs_hld(u, pos);
    }
  }

 public:
  vector<vector<int>> G;

  // vid: vertex -> idx
  // inv: idx -> vertex
  vector<int> vid, nxt, sub, par, inv;

  HLD(int n) : G(n), vid(n, -1), nxt(n), sub(n, 1), par(n, -1), inv(n) {}

  void add_edge(int u, int v) {
    G[u].emplace_back(v);
    G[v].emplace_back(u);
  }

  void build(int r = 0) {
    int pos = 0;
    dfs_sz(r);
    nxt[r] = r;
    dfs_hld(r, pos);
  }

  int lca(int u, int v) {
    while (1) {
      if (vid[u] > vid[v]) swap(u, v);
      if (nxt[u] == nxt[v]) return u;
      v = par[nxt[v]];
    }
  }

  template <typename F>
  void for_each(int u, int v, const F& f) {
    while (1) {
      if (vid[u] > vid[v]) swap(u, v);
      f(max(vid[nxt[v]], vid[u]), vid[v] + 1);
      if (nxt[u] != nxt[v])
        v = par[nxt[v]];
      else
        break;
    }
  }

  template <typename F>
  void for_each_edge(int u, int v, const F& f) {
    while (1) {
      if (vid[u] > vid[v]) swap(u, v);
      if (nxt[u] != nxt[v]) {
        f(vid[nxt[v]], vid[v] + 1);
        v = par[nxt[v]];
      } else {
        if (u != v) f(vid[u] + 1, vid[v] + 1);
        break;
      }
    }
  }
};
// END CUT HERE

// 最小共通祖先（LCA）
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C&lang=ja
// メソッドがあるので出力するだけ

int main() {
  /* input */
  int N;
  cin >> N;
  HLD G(N);

  rep(i, N) {
    int K;
    cin >> K;
    rep(j, K) {
      int c;
      cin >> c;
      G.add_edge(i, c);
    }
  }
  /* preprocessing */
  G.build();

  /* query */
  int Q;
  cin >> Q;
  while (Q--) {
    int u, v;
    cin >> u >> v;
    cout << G.lca(u, v) << endl;
  }
  return 0;
}