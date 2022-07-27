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

struct Solver {
  void solve() {
    /* input */
    int N, K;
    cin >> N >> K;
    vl A(K);
    rep(i, K) cin >> A[i];
    vl X(N);
    vl Y(N);
    rep(i, N) cin >> X[i] >> Y[i];

    /* solve */
    ll maxDist = -1;
    rep(i, N) {
      ll minDist = (1LL << 60);
      rep(j, K) {
        ll dist = (X[i] - X[A[j] - 1]) * (X[i] - X[A[j] - 1]);
        dist += (Y[i] - Y[A[j] - 1]) * (Y[i] - Y[A[j] - 1]);
        chmin(minDist, dist);
      }
      chmax(maxDist, minDist);
    }

    /* output */
    cout.precision(10);
    cout << fixed << sqrt((double)maxDist) << endl;
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