#include <bits/stdc++.h>
using namespace std;

#define mem(a, b) memset(a, b, sizeof(a))
typedef long long ll;
typedef long double ld;

const double eps = 1e-8;
const double inf = 1e20;
const double pi = acos(-1.0);

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

int sgn(double x) {
    if (fabs(x) < eps)
        return 0;
    if (x < 0)
        return -1;
    else
        return 1;
}

inline double sqr(double x) { return x * x; }

struct Point {
    double x, y;
    Point() {}
    Point(double _x, double _y) : x(_x), y(_y) {}

    void input() { scanf("%lf %lf", &x, &y); }
    void output() { printf("%.10lf %.10lf\n", x, y); }
    bool operator==(Point b) const { return sgn(x - b.x) == 0 && sgn(y - b.y) == 0; }
    bool operator<(Point b) const { return sgn(x - b.x) == 0 ? sgn(y - b.y) < 0 : sgn(x - b.x) < 0; }
    Point operator+(const Point &b) const { return Point(x + b.x, y + b.y); }
    Point operator-(const Point &b) const { return Point(x - b.x, y - b.y); }
    Point operator*(const double &k) const { return Point(x * k, y * k); }
    Point operator/(const double &k) const { return Point(x / k, y / k); }

    double operator*(const Point &b) const { return x * b.x + y * b.y; }  // dot product
    double operator^(const Point &b) const { return x * b.y - y * b.x; }  // cross product of 2d points
    double len() { return hypot(x, y); }                                  // length from origin
    double len2() { return x * x + y * y; }
    double dis(Point p) { return hypot(x - p.x, y - p.y); }  // distance from p
    // ����pa pb�нǣ�����㿴a,b���ɵļн�
    double rad(Point a, Point b) {
        Point p = *this;
        return fabs(atan2(fabs((a - p) ^ (b - p)), (a - p) * (b - p)));
    }
    Point rotleft() {
        return Point(-y, x);  // ��ʱ����ת90
    }
    Point rotright() {
        return Point(y, -x);  // ˳ʱ����ת90
    }
    // ���ŵ�p��ʱ����תangle
    Point rotate(Point p, double angle) {
        Point v = (*this) - p;
        double c = cos(angle);
        double s = sin(angle);
        return Point(p.x + v.x * c - v.y * s, p.y + v.x * s + v.y * c);
    }
};

struct Line {
    Point u, v;
    Line() {}
    Line(Point _u, Point _v) : u(_u), v(_v) {}
    bool operator==(Line l) { return (u == l.u) && (v == l.v); }

    void input() {
        u.input();
        v.input();
    }
    double length() { return u.dis(v); }

    // ralation of point and line(segment): ���ֱ��(�߶�)��ϵ
    // 1:left  2:right  3:on segment  4: on line front  5:on line back
    int relation(Point p) {
        int c = sgn((p - u) ^ (v - u));
        if (c < 0)
            return 1;
        else if (c > 0)
            return 2;
        else {  // on (line or segment)
            if (sgn((p - u) * (p - v)) <= 0)
                return 3;  // on segment
            if (sgn((p - u) * (v - u)) > 0)
                return 4;  // on_line_front
            else
                return 5;  // on_line_back
        }
    }

    // relation of two lines ֱ����ֱ�߹�ϵ
    // 0:ƽ�� 1:�غ�  2:����  3:����
    int line_relation(Line l) {
        if (sgn((v - u) * (l.v - l.u)) == 0)
            return 2;
        // ���Ϊ0 ����������(ƽ��or�غ�)
        if (sgn((v - u) ^ (l.v - l.u)) == 0)
            return l.relation(u) > 2;
        return 3;
    }

    // �����߶��ཻ�ж�
    // 2 �淶�ཻ 1 �ǹ淶�ཻ 0 ���ཻ
    int segcrossseg(Line l) {
        int d1 = sgn((v - u) ^ (l.u - u));
        int d2 = sgn((v - u) ^ (l.v - u));
        int d3 = sgn((l.v - l.u) ^ (u - l.u));
        int d4 = sgn((l.v - l.u) ^ (v - l.u));
        if ((d1 ^ d2) == -2 && (d3 ^ d4) == -2)
            return 2;
        return (d1 == 0 && sgn((l.u - u) * (l.u - v)) <= 0) ||
               (d2 == 0 && sgn((l.v - u) * (l.v - v)) <= 0) ||
               (d3 == 0 && sgn((u - l.u) * (u - l.v)) <= 0) ||
               (d4 == 0 && sgn((v - l.u) * (v - l.v)) <= 0);
    }

    // ����ֱ�ߵĽ���
    // Ҫ��֤��ֱ�߲�ƽ�л��غ�
    Point crosspoint(Line l) {
        double a1 = (l.v - l.u) ^ (u - l.u);
        double a2 = (l.v - l.u) ^ (v - l.u);
        return Point((u.x * a2 - v.x * a1) / (a2 - a1), (u.y * a2 - v.y * a1) / (a2 - a1));
    }

    // dis: point to line �㵽ֱ�ߵľ���
    double dispointtoline(Point p) { return fabs((p - u) ^ (v - u)) / length(); }

    // dis : point to seg �㵽�߶εľ���
    double dispointtoseg(Point p) {
        if (sgn((p - u) * (v - u)) < 0 || sgn((p - v) * (u - v)) < 0)
            return min(p.dis(u), p.dis(v));
        return dispointtoline(p);
    }
    // dis: seg to seg �߶ε��߶εľ���
    double dissegtoseg(Line l) {
        if (segcrossseg(l))
            return 0;  // �߶��ཻ���������0
        return min(min(dispointtoseg(l.u), dispointtoseg(l.v)),
                   min(l.dispointtoseg(u), l.dispointtoseg(v)));
    }

    // project point p on line(u,v) ��p��ֱ���ϵ�ͶӰ
    Point project(Point p) {
        return u + (((v - u) * ((v - u) * (p - u))) / ((v - u).len2()));
        // return p*
    }
    // ��p����ֱ�ߵĶԳƵ�
    Point symmetry(Point p) {
        Point q = project(p);  // �����е�
        return Point(2 * q.x - p.x, 2 * q.y - p.y);
    }
};
/*
bool same_plane(Node a,Node b,Node c,Node d) {
    Node u = a - b;
    Node v = a - c;
    Node w = a - d;
    return (u ^ v) * w == 0;
}

bool same_line(Node a,Node b,Node c) {
    Node u = a - b;
    Node v = a - c;
    return (u ^ v) == zero;
}

ld angle(Node a,Node b,Node c) {
    Node u = b - a;
    Node v = c - a;
    ll dot = u * v;
    Node cross = u ^ v;
    return sgn(cross) * ld(dot) / dis(cross);
}

bool same_circle(Node a,Node b,Node c,Node d) {
    if(same_line(a,b,c) || same_line(a,b,d) || same_line(b,c,d)) return false;

    auto ag1 = angle(a,b,c);
    auto ag2 = angle(d,c,b);
    return sgn(ag1+ag2) == 0;
}

*/
const int maxp = 105;
struct Polygon {
    int n;  // size of polygon
    Point p[maxp];
    Line l[maxp];
    void input(int _n) {
        n = _n;
        for (int i = 0; i < n; i++) p[i].input();
    }
    void output() {
        printf("%d\n", n);
        for (int i = 0; i < n; i++) p[i].output();
    }
    void add(Point q) {
        p[n++] = q;  // add a point at the end of the list
    }
    void getline() {  // populate line array
        for (int i = 0; i < n; i++) l[i] = Line(p[i], p[(i + 1) % n]);
    }

    bool isconvex() {  // �ж��ǲ���͹��
        bool s[2];
        mem(s, false);
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            int k = (j + 1) % n;
            s[sgn((p[j] - p[i]) ^ (p[k] - p[i])) + 1] = true;
            if (s[0] && s[2])
                return false;
        }
        return true;
    }
    // �жϵ����������εĹ�ϵ
    // 3:����  2:����  1:�ڲ�  0:�ⲿ  (�ڵ��� һ�� �ڱ���)
    int point_relation(Point q) {
        for (int i = 0; i < n; i++)
            if (p[i] == q)
                return 3;
        getline();
        for (int i = 0; i < n; i++)
            if (l[i].relation(q) == 3)
                return 2;

        int cnt = 0;
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            int k = sgn((q - p[j]) ^ (p[i] - p[j]));
            int u = sgn(p[i].y - q.y);
            int v = sgn(p[j].y - q.y);
            if (k > 0 && u < 0 && v >= 0)
                cnt++;
            if (k < 0 && v < 0 && u >= 0)
                cnt--;
        }
        return cnt != 0;
    }

    double getCircumference() {
        double sum = 0;
        for (int i = 0; i < n; i++) sum += p[i].dis(p[(i + 1) % n]);
        return sum;
    }
    double getArea() {
        double sum = 0;
        for (int i = 0; i < n; i++) sum += (p[i] ^ p[(i + 1) % n]);
        return fabs(sum) / 2;
    }

    struct cmp {
        Point q;
        cmp(const Point &q0) { q = q0; }
        bool operator()(const Point &aa, const Point &bb) {
            Point a = aa, b = bb;
            int d = sgn((a - q) ^ (b - q));
            if (d == 0)
                return sgn(a.dis(q) - b.dis(q)) < 0;
            return d > 0;
        }
    };
    // ��������
    // �����ҵ������½ǵĵ㣬��Ҫ����Point�� < ������
    void norm() {
        Point mi = p[0];
        for (int i = 0; i < n; i++) mi = min(mi, p[i]);
        sort(p, p + n, cmp(mi));
    }
    // �õ�͹�� Andrew
    // �õ���͹������ĵĵ����� 0~n-1
    void getConvex(Polygon &convex) {
        sort(p, p + n);
        convex.n = n;
        for (int i = 0; i < min(n, 2); i++) convex.p[i] = p[i];
        if (convex.n == 2 && (convex.p[0] == convex.p[1]))
            convex.n--;
        if (n <= 2)
            return;
        int &top = convex.n;
        top = 1;
        for (int i = 2; i < n; i++) {
            while (top && sgn((convex.p[top] - p[i]) ^ (convex.p[top - 1] - p[i])) <= 0) top--;
            convex.p[++top] = p[i];
        }
        int temp = top;
        convex.p[++top] = p[n - 2];
        for (int i = n - 3; i >= 0; i--) {
            while (top != temp && sgn((convex.p[top] - p[i]) ^ (convex.p[top - 1] - p[i])) <= 0) top--;
            convex.p[++top] = p[i];
        }
        if (convex.n == 2 && (convex.p[0] == convex.p[1]))
            convex.n--;

        convex.norm();  // ԭ���õ�����˳ʱ��ĵ㣬�������ʱ��
    }
    void Graham(Polygon &convex) {
        norm();
        int &top = convex.n;
        top = 0;
        if (n == 1) {
            top = 1;
            convex.p[0] = p[0];
            return;
        }
        if (n == 2) {
            top = 2;
            convex.p[0] = p[0];
            convex.p[1] = p[1];
            if (convex.p[0] == convex.p[1])
                top--;
            return;
        }
        convex.p[0] = p[0];
        convex.p[1] = p[1];
        top = 2;
        for (int i = 2; i < n; i++) {
            while (top > 1 && sgn((convex.p[top - 1] - convex.p[top - 2]) ^ (p[i] - convex.p[top - 2])) <= 0) top--;
            convex.p[top++] = p[i];
        }
        if (convex.n == 2 && (convex.p[0] == convex.p[1]))
            convex.n--;
    }
};

void solve() {
    int n;
    scanf("%d", &n);
    Polygon k;
    k.input(n);
    Polygon convex;
    // k.getConvex(convex);
    convex.output();
}

int main() {
    solve();
    return 0;
}
