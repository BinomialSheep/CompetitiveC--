#pragma region header
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

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(x) (x).begin(), (x).end()
#define INT(...)   \
  int __VA_ARGS__; \
  in(__VA_ARGS__)
#define LL(...)   \
  ll __VA_ARGS__; \
  in(__VA_ARGS__)
#define STR(...)      \
  string __VA_ARGS__; \
  in(__VA_ARGS__)
#define Sort(a) sort(all(a))
#define VEC(type, name, size) \
  vector<type> name(size);    \
  in(name)
[[maybe_unused]] void print() {}
template <class T, class... Ts>
void print(const T& t, const Ts&... ts);
template <class... Ts>
void out(const Ts&... ts) {
  print(ts...);
  cout << '\n';
}

namespace IO {
#define VOID(a) decltype(void(a))
struct S {
  S() {
    cin.tie(nullptr)->sync_with_stdio(0);
    fixed(cout).precision(12);
  }
} S;
template <int I>
struct P : P<I - 1> {};
template <>
struct P<0> {};
template <class T>
void i(T& t) {
  i(t, P<3>{});
}
void i(vector<bool>::reference t, P<3>) {
  int a;
  i(a);
  t = a;
}
template <class T>
auto i(T& t, P<2>) -> VOID(cin >> t) {
  cin >> t;
}
template <class T>
auto i(T& t, P<1>) -> VOID(begin(t)) {
  for (auto&& x : t) i(x);
}
template <class T, size_t... idx>
void ituple(T& t, index_sequence<idx...>) {
  in(get<idx>(t)...);
}
template <class T>
auto i(T& t, P<0>) -> VOID(tuple_size<T>{}) {
  ituple(t, make_index_sequence<tuple_size<T>::value>{});
}
template <class T>
void o(const T& t) {
  o(t, P<4>{});
}
template <size_t N>
void o(const char (&t)[N], P<4>) {
  cout << t;
}
template <class T, size_t N>
void o(const T (&t)[N], P<3>) {
  o(t[0]);
  for (size_t i = 1; i < N; i++) {
    o(' ');
    o(t[i]);
  }
}
template <class T>
auto o(const T& t, P<2>) -> VOID(cout << t) {
  cout << t;
}
template <class T>
auto o(const T& t, P<1>) -> VOID(begin(t)) {
  bool first = 1;
  for (auto&& x : t) {
    if (first)
      first = 0;
    else
      o(' ');
    o(x);
  }
}
template <class T, size_t... idx>
void otuple(const T& t, index_sequence<idx...>) {
  print(get<idx>(t)...);
}
template <class T>
auto o(T& t, P<0>) -> VOID(tuple_size<T>{}) {
  otuple(t, make_index_sequence<tuple_size<T>::value>{});
}
#undef VOID
}  // namespace IO
#define unpack(a) \
  (void)initializer_list<int> { (a, 0)... }
template <class... Ts>
void in(Ts&... t) {
  unpack(IO::i(t));
}
template <class T, class... Ts>
void print(const T& t, const Ts&... ts) {
  IO::o(t);
  unpack(IO::o((cout << ' ', ts)));
}
#undef unpack
// #define MAX 10000
#define INFTY (1 << 30)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)

template <typename T>
inline bool chmax(T& a, T b) {
  return ((a < b) ? (a = b, true) : (false));
}
template <typename T>
inline bool chmin(T& a, T b) {
  return ((a > b) ? (a = b, true) : (false));
}

#define YESNO(yes, no)                          \
  void yes(bool i = 1) { out(i ? #yes : #no); } \
  void no() { out(#no); }
YESNO(first, second)
YESNO(First, Second)
YESNO(Yes, No)
YESNO(YES, NO)
YESNO(possible, impossible)
YESNO(POSSIBLE, IMPOSSIBLE)
#pragma endregion header
#include <atcoder/all>
using namespace atcoder;

struct Solver {
  void solve() {
    /* input */
    LL(N);
    INT(A1, A2, A3);
    using mint = modint998244353;

    /* solve */
    auto f = [](int n, int MOD) {
      ll now = 1;
      rep(i, n) now *= 2;
      return now % MOD;
    };

    int sz = 0;
    {
      ll tmp = 1;
      rep(i, 100) {
        tmp *= 2;
        if (tmp > N) {
          sz = i + 1;
          break;
        }
      }
    }
    debug(sz);

    vector dp(A1,
              vector(A2, vector(A3, vector(2, vector(2, vector(2, mint(0)))))));
    dp[0][0][0][0][0][0] = 1;
    rep(i, sz) {
      vector p(
          A1, vector(A2, vector(A3, vector(2, vector(2, vector(2, mint(0)))))));
      int flag = (N >> i & 1) ? 1 : 0;
      rep(a1, A1) rep(a2, A2) rep(a3, A3) rep(b1, 2) rep(b2, 2) rep(b3, 2) {
        // 0, 0, 0
        if (flag) {
          p[a1][a2][a3][1][1][1] += dp[a1][a2][a3][b1][b2][b3];
        } else {
          p[a1][a2][a3][b1][b2][b3] += dp[a1][a2][a3][b1][b2][b3];
        }
        // 1, 1, 0
        if (flag) {
          p[(a1 * 2 + f(i, A1)) % A1][(a2 * 2 + f(i, A2)) % A2][a3][b1][b2]
           [1] += dp[a1][a2][a3][b1][b2][b3];
        } else {
          if (!b1 && !b2) {
            p[(a1 * 2 + f(i, A1)) % A1][(a2 * 2 + f(i, A2)) % A2][a3][b1][b2]
             [b3] += dp[a1][a2][a3][b1][b2][b3];
          }
        }
        // 1, 0, 1
        if (flag) {
          p[(a1 * 2 + f(i, A1)) % A1][a2][(a3 * 2 + f(i, A3)) % A3][b1][1]
           [b3] += dp[a1][a2][a3][b1][b2][b3];
        } else {
          if (!b1 && !b3) {
            p[(a1 * 2 + f(i, A1)) % A1][a2][(a3 * 2 + f(i, A3)) % A3][b1][b2]
             [b3] += dp[a1][a2][a3][b1][b2][b3];
          }
        }
        // 0, 1, 1
        if (flag) {
          p[a1][(a2 * 2 + f(i, A2)) % A2][(a3 * 2 + f(i, A3)) % A3][1][b2]
           [b3] += dp[a1][a2][a3][b1][b2][b3];
        } else {
          if (!b2 && !b3) {
            p[a1][(a2 * 2 + f(i, A2)) % A2][(a3 * 2 + f(i, A3)) % A3][b1][b2]
             [b3] += dp[a1][a2][a3][b1][b2][b3];
          }
        }
      }
      swap(dp, p);

      // if (i == 0) {
      //   rep(a1, A1) rep(a2, A2) rep(a3, A3) rep(b1, 2) rep(b2, 2) rep(b3, 2)
      //   {
      //     if ((!a1 && !a2 && !a3 && b1 && b2 && b3) ||
      //         (a1 == 1 && a2 == 1 && a3 == 0 && !b1 && !b2 && b3) ||
      //         (a1 == 1 && a2 == 0 && a3 == 1 && !b1 && b2 && !b3) ||
      //         (a1 == 0 && a2 == 1 && a3 == 1 && b1 && !b2 && !b3)) {
      //       assert(dp[a1][a2][a3][b1][b2][b3].val() == 1);
      //     } else {
      //       assert(dp[a1][a2][a3][b1][b2][b3].val() == 0);
      //     }
      //   }
      // }
      // if (i == 1) {
      //   rep(i3, A1) rep(j, A2) rep(k, A3) rep(i2, 2) rep(j2, 2) rep(k2, 2) {
      //     if (dp[i3][j][k][i2][j2][k2].val())
      //       debug(i3, j, k, i2, j2, k2, dp[i3][j][k][i2][j2][k2].val());
      //   }
      // }
    }
    /* output */

    out(dp[0][0][0][1][1][1].val());
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