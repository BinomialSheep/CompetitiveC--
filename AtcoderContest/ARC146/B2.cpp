#include <bits/stdc++.h>
// デバッグ用マクロ：https://naskya.net/post/0002/
#ifdef LOCAL
#include <debug_print.hpp>
#define debug(...) debug_print::multi_print(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (static_cast<void>(0))
#endif
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
// #include <atcoder/all>
// using namespace atcoder;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(x) (x).begin(), (x).end()
// #define MAX 10000
#define INFTY (1 << 30)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)

template <typename T>
inline bool chmax(T &a, T b) {
  return ((a < b) ? (a = b, true) : (false));
}
template <typename T>
inline bool chmin(T &a, T b) {
  return ((a > b) ? (a = b, true) : (false));
}

ll llMax(ll a, ll b) { return (a >= b ? a : b); }

struct Solver {
  void solve() {
    /* input */
    int N, M, K;
    cin >> N >> M >> K;
    vl A(N);
    rep(i, N) cin >> A[i];

    /* solve */

    auto isOk = [&](ll value) {
      // valueの最上位桁を求める
      ll div = 1;
      while (div > value) div *= 2;
      vl cost(N);
      rep(i, N) { cost[i] = llMax(0, value - A[i] / div); }

      if (value == 256) debug(cost);

      sort(all(cost));
      ll sum = 0;
      rep(i, K) sum += cost[i];
      assert(sum >= 0);
      if (sum <= M) {
        return true;
      } else {
        return false;
      }
    };

    ll ans = 0;
    for (int i = 32; i >= 0; i--) {
      ans += (1LL << i);
      debug(ans);
      if (isOk(ans)) {
        // 嬉しい
      } else {
        ans -= (1LL << i);
      }
    }
    /* output */
    cout << ans << endl;
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