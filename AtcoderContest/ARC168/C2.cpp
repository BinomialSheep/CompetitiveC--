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

// 二項係数（前処理O(n), クエリ毎O(1))
// facなどのコピペも忘れすに
const int nCkMAX = 260000;
ll fac[nCkMAX], finv[nCkMAX], inv[nCkMAX];
class MynCkMod {
  const int MOD;

 public:
  MynCkMod(int mod) : MOD(mod) { COMinit(); };

  // 前処理
  void COMinit() {
    fac[0] = fac[1] = 1;
    finv[0] = finv[1] = 1;
    inv[1] = 1;
    for (int i = 2; i < nCkMAX; i++) {
      fac[i] = fac[i - 1] * i % MOD;
      inv[i] = MOD - inv[MOD % i] * (MOD / i) % MOD;
      finv[i] = finv[i - 1] * inv[i] % MOD;
    }
  }

  // 二項係数計算
  ll COM(int n, int k) {
    if (n < k) return 0;
    if (n < 0 || k < 0) return 0;
    return fac[n] * (finv[k] * finv[n - k] % MOD) % MOD;
  }
};

struct Solver {
  void solve() {
    /* input */
    INT(N, K);
    STR(S);
    using mint = modint998244353;

    MynCkMod nCkMod(998244353);

    vi cnt(3);
    for (auto c : S) cnt[c - 'A']++;
    debug(cnt);
    /* solve */
    int ab = min(cnt[0], cnt[1]);
    int bc = min(cnt[1], cnt[2]);
    int ca = min(cnt[2], cnt[0]);
    int abc = min(ab, bc);
    debug(ab, bc, ca, abc);
    mint ans = 0;
    for (int i1 = 0; i1 <= ab; i1++)
      for (int i2 = 0; i2 <= bc; i2++)
        for (int i3 = 0; i3 <= ca; i3++) {
          // if (i1 + i2 + i3 > K) continue;
          for (int i4 = 0; i4 <= abc; i4++)
            for (int i5 = 0; i5 <= abc; i5++) {
              if (i1 + i2 + i3 + 2 * i4 + 2 * i5 > K) continue;
              if (i1 + i3 + i4 + i5 > cnt[0]) continue;
              if (i1 + i2 + i4 + i5 > cnt[1]) continue;
              if (i2 + i3 + i4 + i5 > cnt[2]) continue;
              debug(i1, i2, i3, i4, i5);
              // どの組をやるか
              int a = cnt[0], b = cnt[1], c = cnt[2];
              // int a2 = cnt[0], b2 = cnt[1], c2 = cnt[2];
              int a2b = i1 + i4;
              int a2c = i3 + i5;
              int b2c = i2 + i4;
              int b2a = i1 + i5;
              int c2a = i3 + i4;
              int c2b = i2 + i5;

              if (a2b + a2c > a) continue;
              if (b2a + b2c > b) continue;
              if (c2b + c2a > c) continue;
              if (c2a + b2a > a) continue;
              if (a2b + c2b > b) continue;
              if (b2c + a2c > c) continue;

              mint tmp = 1;
              tmp *= nCkMod.COM(a, a2b);
              // tmp *= nCkMod.COM(b2, a2b);
              a -= a2b;
              // b2 -= a2b;
              tmp *= nCkMod.COM(a, a2c);
              // tmp *= nCkMod.COM(c2, a2c);
              a -= a2c;  //, c2 -= a2c;
              tmp *= nCkMod.COM(b, b2c);
              // tmp *= nCkMod.COM(c2, b2c);
              b -= b2c;  //, c2 -= b2c;
              tmp *= nCkMod.COM(b, b2a);
              // tmp *= nCkMod.COM(a2, b2a);
              b -= b2a;  //, a2 -= b2a;
              tmp *= nCkMod.COM(c, c2a);
              // tmp *= nCkMod.COM(a2, c2a);
              c -= c2a;  //, a2 -= c2a;
              tmp *= nCkMod.COM(c, c2b);
              // tmp *= nCkMod.COM(b2, c2b);
              c -= c2b;  // , b2 -= c2b;

              assert(a >= 0 && b >= 0 && c >= 0);
              ans += tmp;
              debug(tmp.val());
            }
        }

    /* output */
    out(ans.val());
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