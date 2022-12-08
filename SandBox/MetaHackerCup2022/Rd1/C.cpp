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

/* 幾何学的オブジェクトのまとめ */

// 点とベクトル
class Point {
 public:
  double x, y;
  Point(double x = 0, double y = 0) : x(x), y(y) {}

  /* --- メンバ関数 --- */
  // ベクトルの大きさ
  double norm() { return x * x + y * y; }
  double abs() { return sqrt(norm()); }

  /* --- クラス関数 --- */
  // ベクトルの大きさ
  static double norm(Point p) { return p.x * p.x + p.y * p.y; }
  static double abs(Point p) { return sqrt(norm(p)); }
  // ベクトルの内積
  static double dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }
  // ベクトルの外積
  static double cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }

  // ベクトルの直行判定
  static bool isOrthogonal(Point p1, Point p2) {
    // Θが90度か-90度 ⇔ cosΘが0なので内積を利用
    return equal(dot(p1, p2), 0.0);
  }
  // 2直線を通る4点の直行判定
  static bool isOrthogonal(Point a1, Point a2, Point b1, Point b2) {
    return isOrthogonal(a1 - a2, b1 - b2);
  }
  // ベクトルの平行判定
  static bool isParallel(Point p1, Point p2) {
    // Θが0度か180度の時 ⇔ sinΘが0なので外積を利用
    return equal(cross(p1, p2), 0.0);
  }
  // 2直線を通る4点の平行判定
  static bool isParallel(Point a1, Point a2, Point b1, Point b2) {
    return isParallel(a1 - a2, b1 - b2);
  }
  // 射影
  static Point project(Point p1, Point p2, Point p) {
    // 射影とは、点pからベクトル(p2-p1)に垂線を引いた時の交点x
    Point base = p2 - p1;
    // rは比率。|x-p1|/|p2-p1|。詳しくは螺旋本16.3
    double r = dot(p - p1, base) / base.norm();
    return p1 + base * r;
  }
  // 反射
  static Point reflect(Point p1, Point p2, Point p) {
    // 反射とは、ベクトル(p2-p1)を対称軸とした点pと線対称の点x
    // pからp1p2への射影へのベクトルを2倍すればいい
    return p + (project(p1, p2, p) - p) * 2.0;
  }
  // 点と点の距離
  static double getDistance(Point a, Point b) { return abs(a - b); }
  // 点pと直線abの距離
  static double getDistanceLP(Point a, Point b, Point p) {
    return abs(cross(b - a, p - a) / abs(b - a));
  }
  // 点pと線分abの距離(Sはsegment)
  static double getDistanceSP(Point a, Point b, Point p) {
    // 線分と端点-点pの為す角が90度を超えたら端点と点の距離を返す
    if (dot(b - a, p - a) < 0.0) return abs(p - a);
    if (dot(a - b, p - b) < 0.0) return abs(p - b);
    // そうでなければ線との距離を返す
    return getDistanceLP(a, b, p);
  }
  // 線分abと線分cdの距離
  static double getDistanceSS(Point a, Point b, Point c, Point d) {
    // 線分が交差してたら距離0
    if (intersect(a, b, c, d)) return 0.0;
    // 線分abと点c, 線分abと点d, 線分cdと点a, 線分cdと点bのmin
    return min(min(getDistanceSP(a, b, c), getDistanceSP(a, b, d)),
               min(getDistanceSP(c, d, a), getDistanceSP(c, d, b)));
  }
  // ベクトルabとacの位置判定（Counter-ClockWise)
  static int ccw(Point a, Point b, Point c) {
    const int COUNTER_CLOCKWISE = 1;  // a, b, cが半時計回り
    const int CLOCKWISE = -1;         // a, b, cが時計回り
    const int ONLINE_BACK = 2;        // c, a, bの順で同一直線上
    const int ONLINE_FRONT = -2;      // a, b, cの順で同一直線上
    const int ON_SEGMENT = 0;         // a, c, bの順で直線上
    Point ab = b - a;
    Point ac = c - a;
    if (cross(ab, ac) > EPS) return COUNTER_CLOCKWISE;
    if (cross(ab, ac) < -EPS) return CLOCKWISE;
    if (dot(ab, ac) < -EPS) return ONLINE_BACK;
    if (ab.norm() < ac.norm()) return ONLINE_FRONT;
    return ON_SEGMENT;
  }

  // 線分abと線分cdの交差判定
  static bool intersect(Point a, Point b, Point c, Point d) {
    // 点c,dが線分abの逆側（含線上)かつ点a,bが線分cdの逆側（含線上)なら交差
    return (ccw(a, b, c) * ccw(a, b, d) <= 0 &&
            ccw(c, d, a) * ccw(c, d, b) <= 0);
  }
  // 線分の交点
  static Point getCrossPoint(Point a1, Point a2, Point b1, Point b2) {
    // 外積と図形的考察によって交点を境とした比率を求めている（螺旋本16.8）
    Point base = b2 - b1;
    double d1 = abs(cross(base, a1 - b1));
    double d2 = abs(cross(base, a2 - b1));
    double t = d1 / (d1 + d2);
    return a1 + (a2 - a1) * t;
  }

  /* --- 演算子のオーバーロード --- */
  // ベクトルの基本演算
  Point operator+(Point p) { return Point(x + p.x, y + p.y); }
  Point operator-(Point p) { return Point(x - p.x, y - p.y); }
  Point operator*(double k) { return Point(x * k, y * k); }
  Point operator/(double k) { return Point(x / k, y / k); }

  // 点の不等式（ここではx座標の大きさ。x座標が等しければy座標の大きさ）
  bool operator<(const Point &p) const { return x != p.x ? x < p.x : y < p.y; }
  // 点の等式
  bool operator==(const Point &p) const {
    // fabsは小数点用の絶対値計算
    // EPSはマクロで定義した1e-10。小数点の誤差を考慮
    return fabs(x - p.x) < EPS && fabs(y - p.y) < EPS;
  }
};
typedef Point Vector;

//線分と直線
struct Segment {
  Point p1, p2;
  Segment(Point p1, Point p2) : p1(p1), p2(p2) {}

  // 直行判定
  static bool isOrthogonal(Segment s1, Segment s2) {
    return equal(Point::cross(s1.p2 - s1.p1, s2.p2 - s2.p1), 0.0);
  }
  // 平行判定
  static bool isParallel(Segment s1, Segment s2) {
    return equal(Point::cross(s1.p2 - s1.p1, s2.p2 - s2.p1), 0.0);
  }
  // 射影
  static Point project(Segment s, Point p) {
    Vector base = s.p2 - s.p1;
    double r = Point::dot(p - s.p1, base) / Point::norm(base);
    return s.p1 + base * r;
  }
  // 反射
  static Point reflect(Segment s, Point p) {
    return p + (project(s, p) - p) * 2;
  }
  // 線分と点の距離
  static double getDistanceSP(Segment s, Point p) {
    return Point::getDistanceSP(s.p1, s.p2, p);
  }
  // 線分と線分の距離
  static double getDistanceSS(Segment s1, Segment s2) {
    return Point::getDistanceSS(s1.p1, s1.p2, s2.p1, s2.p2);
  }
  // 線分と線分の交差判定
  static bool intersect(Segment s1, Segment s2) {
    return Point::intersect(s1.p1, s1.p2, s2.p1, s2.p2);
  }
  // 線分の交点
  static Point getCrossPoint(Segment s1, Segment s2) {
    return Point::getCrossPoint(s1.p1, s1.p2, s2.p1, s2.p2);
  }
};
typedef Segment Line;

// 円
class Circle {
 public:
  Point c;
  double r;
  // 中心座標:Point, 半径:double
  Circle(Point c = Point(), double r = 0.0) : c(c), r(r) {}

  // なす角 argment
  static double arg(Vector p) { return atan2(p.y, p.x); }
  // 極座標
  static Point polar(double a, double r) {
    return Point(cos(r) * a, sin(r) * a);
  }
  // 円と線分の交点（2つあると仮定）
  static pair<Point, Point> getCrossPoints(Circle c, Segment l) {
    // prは円の中心から線分への射影
    Point pr = Segment::project(l, c.c);
    // eはp1p2の単位ベクトル
    Point e = (l.p2 - l.p1) / Point::abs(l.p2 - l.p1);
    // baseは円の内側の線分の長さの半分
    double base = sqrt(c.r * c.r - Point::norm(pr - c.c));
    return make_pair(pr + e * base, pr - e * base);
  }

  // 円と円の交点（2つあると仮定）
  static pair<Point, Point> getCross(Circle c1, Circle c2) {
    // 中心間と2交点の三角形の各辺がd, c1.r,
    // c2.rなことを利用し余弦定理（螺旋16.10）
    double d = Point::abs(c1.c - c2.c);
    double a = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2 * c1.r * d));
    double t = arg(c2.c - c1.c);
    return make_pair(c1.c + polar(c1.r, t + a), c1.c + polar(c1.r, t - a));
  }
};

// 多角形
class Polygon {
 public:
  vector<Point> pointVec;
  Polygon(vector<Point> pointVec) : pointVec(pointVec) {}

  // 点の内包判定
  static int contains(Polygon polygon, Point p) {
    vector<Point> g = polygon.pointVec;
    // 凸とは限らない多角形と点が与えられた時、点が多角形の中にあるか判定するアルゴリズム（螺旋本16.11）
    const int IN = 2;   // 内包
    const int ON = 1;   // 線上
    const int OUT = 0;  // 内包の外
    // 点からx軸正方向に水平な半直線を引き、多角形の辺との交点が奇数なら内包している
    int n = g.size();
    bool isContain = false;
    for (int i = 0; i < n; i++) {
      // a, bは点pから、ある辺g[i]g[i+1]の端点へのベクトル
      Point a = g[i] - p, b = g[(i + 1) % n] - p;
      // 点pが線上 ⇔ ベクトルaとbが同一直線上で逆向き ⇔ 外積が0で内積が0以下
      if (Point::abs(Point::cross(a, b)) < EPS && Point::dot(a, b) < EPS)
        return 1;
      // abのうちy座標が小さいベクトルをaとしても一般性は失われない
      if (a.y > b.y) swap(a, b);
      //交差する ⇔（abが半直線をまたいで逆側 ∧ aからbに半時計回り）
      // ⇔ （点pを起点としたベクトルaのy座標が負でbのy座標が正∧abの外積が正)
      // 内包判定を反転することで交差回数の偶奇を表す
      if (a.y < EPS && EPS < b.y && Point::cross(a, b) > EPS)
        isContain = !isContain;
    }
    return (isContain ? 2 : 0);
  }

  // 凸包の生成（アンドリューのアルゴリズム）
  static Polygon andrewScan(Polygon polygon) {
    vector<Point> s = polygon.pointVec;
    vector<Point> u, l;
    if (s.size() < 3) return Polygon(s);
    // x, yを基準に昇順にソート
    sort(s.begin(), s.end());

    // 点a, b, cが時計回り（反時計回り）なことを表す定数
    const int CLOCK = -1;
    const int C_CLOCK = 1;

    // 凸包の上部を生成
    u.push_back(s[0]);
    u.push_back(s[1]);
    for (int i = 2; i < s.size(); i++) {
      // 凸包 ⇔ 包の隣接2辺が時計回り
      // が維持できるまで辺を撤去してから新しい辺を加える
      // 凸包の辺上の点を含みたくない場合は!= CLOCKに置き換える
      for (int n = u.size();
           n >= 2 && Point::ccw(u[n - 2], u[n - 1], s[i]) == C_CLOCK; n--) {
        u.pop_back();
      }
      u.push_back(s[i]);
    }

    // 凸包の下部を生成
    l.push_back(s[s.size() - 1]);
    l.push_back(s[s.size() - 2]);
    for (int i = s.size() - 3; i >= 0; i--) {
      // 凸包の辺上の点を含みたくない場合は!= CLOCKに置き換える
      for (int n = l.size();
           n >= 2 && Point::ccw(l[n - 2], l[n - 1], s[i]) == C_CLOCK; n--) {
        l.pop_back();
      }
      l.push_back(s[i]);
    }

    // x座標最小点から、半時計回りになるように凸包の列を生成
    // 上部は右向きに、下部は左向きに追加したので、下部を逆順に列挙してから上部を逆順で列挙すればよい
    reverse(l.begin(), l.end());
    for (int i = u.size() - 2; i >= 1; i--) l.push_back(u[i]);

    return Polygon(l);
  }
};

struct Solver {
  void solve() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    rep(ti, T) {
      /* input */
      int N, K, D;
      cin >> N >> K >> D;
      vector<Point> P(N, Point());
      rep(i, N) cin >> P[i].x >> P[i].y;
      Polygon ans = Polygon::andrewScan(Polygon(P));


      

      // debug(ans.pointVec.size());
      // for (auto p : ans.pointVec) {
      //   debug(p.y, p.x);
        
      // }

      /* solve */

      /* output */
      // printf("Case #%d: %s\n", ti + 1, ans.c_str());
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