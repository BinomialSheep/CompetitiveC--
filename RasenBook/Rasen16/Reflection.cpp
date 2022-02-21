#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INTFY (1 << 29)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)

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

  // 直行判定（Θが90度か-90度 ⇔ cosΘが0なので内積を利用）
  static bool isOrthogonal(Point p1, Point p2) {
    return equal(dot(p1, p2), 0.0);
  }
  // 直行判定（直線A, Bを通る点が2点ずつ与えられた場合）
  static bool isOrthogonal(Point a1, Point a2, Point b1, Point b2) {
    return isOrthogonal(a1 - a2, b1 - b2);
  }
  // 平行判定（Θが0度か180度の時 ⇔ sinΘが0なので外積を利用）
  static bool isParallel(Point p1, Point p2) {
    return equal(cross(p1, p2), 0.0);
  }
  // 平行判定（直線A, Bを通る点が2点ずつ与えられた場合）
  static bool isParallel(Point a1, Point a2, Point b1, Point b2) {
    return isParallel(a1 - a2, b1 - b2);
  }
  // 射影（点pからベクトル(p2-p1)に垂線を引いた時の交点x）
  static Point project(Point p1, Point p2, Point p) {
    Point base = p2 - p1;
    // rは比率。|x-p1|/|p2-p1|。詳しくは螺旋本16.3
    double r = dot(p - p1, base) / base.norm();
    return p1 + base * r;
  }
  // 反射（ベクトル(p2-p1)を対称軸とした点pと線対称の点x）
  static Point reflect(Point p1, Point p2, Point p) {
    // pからp1p2への射影へのベクトルを2倍すればいい
    return p + (project(p1, p2, p) - p) * 2.0;
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
};
typedef Segment Line;

int main() {
  int xp1, yp1, xp2, yp2;
  cin >> xp1 >> yp1 >> xp2 >> yp2;
  Point p1(xp1, yp1), p2(xp2, yp2);
  int q;
  cin >> q;
  vector<Point> ans(q);
  int xp0, yp0;
  Point p0;
  rep(i, q) {
    cin >> xp0 >> yp0;
    p0.x = xp0;
    p0.y = yp0;
    ans[i] = Point::reflect(p1, p2, p0);
  }

  cout.precision(15);
  rep(i, q) cout << ans[i].x << " " << ans[i].y << endl;

  return 0;
}