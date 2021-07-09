#define TASKNAME "large"

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

namespace _buff {

const size_t BUFF = 1 << 21;
char ibuf[BUFF], *ib = ibuf, *ie = ibuf;
char obuf[BUFF], *ob = obuf, *oe = obuf + BUFF;

char getc() {
    if (ib == ie) {
        ib = ibuf;
        ie = ibuf + fread(ibuf, 1, BUFF, stdin);
    }
    return ib == ie ? -1 : *ib++;
}

void flush() {
    fwrite(obuf, 1, ob - obuf, stdout);
    ob = obuf;
}

void putc(char c) {
    if (ob == oe) flush();
    if (!~c) return flush();
    *ob++ = c;
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

void print(LL x) {
    using namespace _buff;
    if (!x) {
        putc('0');
        return;
    }
    if (x < 0) {
        putc('-');
        x = -x;
    }
    static char stk[32];
    unsigned tp = 0;
    for (; x; x /= 10) {
        stk[++tp] = (x % 10) ^ 48;
    }
    while (tp) {
        putc(stk[tp--]);
    }
}

using P = pair<int, int>;
#define fi first
#define se second
const size_t N = 5e5 + 5;

P& operator += (P &p, const int &x) {
    p.fi += x;
    return p;
}

P operator + (const P &x, const P &y) {
    P ret = {min(x.fi, y.fi), 0};
    if (ret.fi == x.fi) ret.se += x.se;
    if (ret.fi == y.fi) ret.se += y.se;
    return ret;
}

#define lc(u) ((u) << 1)
#define rc(u) ((u) << 1 | 1)

struct Node {
    P val;
    int tag1;
    LL cnt, tag2;
    Node() {}
} t[N << 2];

void pushup(int u) {
    t[u].val = t[lc(u)].val + t[rc(u)].val;
    t[u].cnt = t[lc(u)].cnt + t[rc(u)].cnt;
}

void update1(int u, int val) {
    t[u].val += val;
    t[u].tag1 += val;
}

void update2(int u, LL val) {
    t[u].cnt += t[u].val.se * val;
    t[u].tag2 += val;
}

void pushdown(int u) {
    if (t[u].tag1) {
        update1(lc(u), t[u].tag1);
        update1(rc(u), t[u].tag1);
        t[u].tag1 = 0;
    } if (t[u].tag2) {
        if (t[lc(u)].val.fi == t[u].val.fi) {
            update2(lc(u), t[u].tag2);
        } if (t[rc(u)].val.fi == t[u].val.fi) {
            update2(rc(u), t[u].tag2);
        }
        t[u].tag2 = 0;
    }
}

void build(int u, int tl, int tr) {
    t[u].val = {0, 1};
    if (tl + 1 == tr) return;
    int mid = (tl + tr) >> 1;
    build(lc(u), tl, mid);
    build(rc(u), mid, tr);
    pushup(u);
}

void modify1(int u, int tl, int tr, int l, int r, int val) {
    if (tl >= r || tr <= l) return;
    if (l <= tl && tr <= r) {
        return update1(u, val);
    }
    pushdown(u);
    int mid = (tl + tr) >> 1;
    modify1(lc(u), tl, mid, l, r, val);
    modify1(rc(u), mid, tr, l, r, val);
    pushup(u);
}

void modify2(int u, int tl, int tr, int l, int r, LL val) {
    if (tl >= r || tr <= l || t[u].val.fi > 1) return;
    if (l <= tl && tr <= r) {
        update2(u, val);
        return;
    }
    pushdown(u);
    int mid = (tl + tr) >> 1;
    modify2(lc(u), tl, mid, l, r, val);
    modify2(rc(u), mid, tr, l, r, val);
    pushup(u);
}

LL query(int u, int tl, int tr, int l, int r) {
    if (tl >= r || tr <= l) return 0;
    if (l <= tl && tr <= r) {
        return t[u].cnt;
    }
    pushdown(u);
    int mid = (tl + tr) >> 1;
    return query(lc(u), tl, mid, l, r) +
           query(rc(u), mid, tr, l, r);
}

int n, arr[N], idx[N];
vector<P> que[N];
LL ans[N];

int main() {
    freopen(TASKNAME ".in",  "r", stdin);
    freopen(TASKNAME ".out", "w", stdout);
    n = read();
    for (int i = 1; i <= n; ++i) {
        idx[arr[i] = read()] = i;
    }
    int q = read();
    for (int i = 0; i < q; ++i) {
        int l = read(), r = read();
        que[r].emplace_back(l, i);
    }

    build(1, 1, n + 1);
    for (int i = 1; i <= n; ++i) {
        modify1(1, 1, n + 1, 1, i + 1, 1);
        if (arr[i] > 1 && idx[arr[i] - 1] < i) {
            modify1(1, 1, n + 1, 1, idx[arr[i] - 1] + 1, -1);
        } if (arr[i] < n && idx[arr[i] + 1] < i) {
            modify1(1, 1, n + 1, 1, idx[arr[i] + 1] + 1, -1);
        }
        modify2(1, 1, n + 1, 1, i + 1, 1);
        for (unsigned j = 0; j < que[i].size(); ++j) {
            int l = que[i][j].fi, id = que[i][j].se;
            ans[id] = query(1, 1, n + 1, l, i + 1);
        }
    }

    for (int i = 0; i < q; ++i) {
        print(ans[i]);
        _buff::putc('\n');
    }
    _buff::putc(EOF);
    return 0;
}
