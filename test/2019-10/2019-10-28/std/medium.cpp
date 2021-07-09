#define TASKNAME "medium"

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

namespace _buff {

const size_t BUFF = 1 << 19;
char ibuf[BUFF], *ib = ibuf, *ie = ibuf;
char getc() {
    if (ib == ie) {
        ib = ibuf;
        ie = ibuf + fread(ibuf, 1, BUFF, stdin);
    }
    return ib == ie ? -1 : *ib++;
}

}

LL read() {
    using namespace _buff;
    LL ret = 0;
    bool pos = true;
    char c = getc();
    for (; (c < '0' || c > '9') && c != '-'; c = getc()) {
        assert(~c);
    }
    if (c == '-') {
        pos = false;
        c = getc();
    }
    for (; c >= '0' && c <= '9'; c = getc()) {
        ret = (ret << 3) + (ret << 1) + (c ^ 48);
    }
    return pos ? ret : -ret;
}

const size_t N = 2e3 + 5;

struct Point {
    int x, y;

    Point(int x = 0, int y = 0) :
        x(x), y(y) {}

    Point operator - (const Point &p) const {
        return Point(x - p.x, y - p.y);
    }

    LL operator % (const Point &p) const {
        return (LL) x * p.y - (LL) y * p.x;
    }
};

int n, h[N];
int dp[N][N];
Point stk[N]; int tp;

void add(Point p) {
    while (tp && stk[tp].x == p.x) {
        if (stk[tp].y > p.y) {
            --tp;
        } else {
            return;
        }
    }
    while (tp > 1 && (stk[tp] - stk[tp - 1]) % (p - stk[tp]) <= 0) {
        --tp;
    }
    stk[++tp] = p;
}

void solve() {
    n = read(); int m = read();
    generate_n(h, n, read);
    sort(h, h + n, greater<int>());

    for (int i = 1; i <= m; ++i) {
        fill(dp[i], dp[i] + n + 1, 2e9);
        tp = 0;
        for (int j = n - i; j >= 0; --j) {
            add(Point(h[j], h[j] * j + dp[i - 1][j + 1]));
            int p = 1, l = 2, r = tp, mid;
            while (l <= r) {
                mid = (l + r) >> 1;
                if (Point(stk[mid] - stk[mid - 1]) % Point(1, j - 1) >= 0) {
                    l = mid + 1;
                    p = mid;
                } else {
                    r = mid - 1;
                }
            }
            dp[i][j] = stk[p].y - stk[p].x * (j - 1);
        }
    }
    printf("%d\n", dp[m][0]);
}

int main() {
    freopen(TASKNAME ".in",  "r", stdin);
    freopen(TASKNAME ".out", "w", stdout);
    int t = read();
    while (t--) {
        solve();
    }
    return 0;
}
