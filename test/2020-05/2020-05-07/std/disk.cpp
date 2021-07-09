#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

#define ll long long

const int N = 200000;
const int INF = 1e9;

int n, k;
int w[N+9];
ll ans;

inline std::pair<int,int> merge(const std::pair<int,int> &p, const std::pair<int,int> &q) {
    std::pair<int,int> ret = w[p.first]+w[p.second] < w[q.first]+w[q.second] ? p : q;
    return ret;
}

inline void getmin(int &x, int y1, int y2) {
    if(w[y1] < w[y2]) x = y1;
    else x = y2;
}

struct data {
    int m1, m2, m3, m4;
    int min, add;
    std::pair<int,int> a1, a2, a3;
    data() {
        m1 = m2 = m3 = m4 = min = add = 0;
    }
    inline friend data operator + (const data &p, const data &q) {
        data r;
        getmin(r.m1, p.m1, q.m1);
        getmin(r.m2, p.m2, q.m2);
        r.min = std::min(p.min, q.min);
        r.a1 = merge(merge(p.a1, q.a1), std::make_pair(p.m1, q.m2));
        r.a3 = merge(merge(p.a3, q.a3), std::make_pair(p.m2, q.m1));
        //m3, m4, a2
        if(p.min < q.min) {
            r.m3 = p.m3;
            getmin(r.m4, q.m2, p.m4);
            r.a2 = merge(merge(p.a2, q.a3), std::make_pair(p.m4, q.m1));
        }
        else if(p.min == q.min) {
            r.m3 = p.m3;
            r.m4 = q.m4;
            r.a2 = merge(merge(p.a2, q.a2), std::make_pair(p.m4, q.m3));
        }
        else {
            r.m4 = q.m4;
            getmin(r.m3, q.m3, p.m1);
            r.a2 = merge(merge(p.a3, q.a2), std::make_pair(p.m2, q.m3));
        }
        return r;
    }
    inline void updadd(int v) {
        min += v, add += v;
    }
}tree[N*4+9];

inline void pushup(int x) {
    tree[x] = tree[x<<1]+tree[x<<1|1];
}

inline void pushdown(int x) {
    if(tree[x].add) {
        int &v = tree[x].add;
        tree[x<<1].updadd(v);
        tree[x<<1|1].updadd(v);
        v = 0;
    }
}

void maketree(int x, int l, int r) {
    if(l == r) {
        data &p = tree[x];
        p.min = p.add = 0;
        p.a1 = p.a2 = p.a3 = std::make_pair(0, 0);
        if(l&1) p.m1 = l;
        else p.m2 = l;
        return ;
    }
    int mid = (l+r)>>1;
    maketree(x<<1, l, mid);
    maketree(x<<1|1, mid+1, r);
    pushup(x);
}

void add(int x, int l, int r, int tl, int tr, int v) {
    if(l == tl && r == tr) {
        tree[x].updadd(v);
        return ;
    }
    pushdown(x);
    int mid = (l+r)>>1;
    if(tr <= mid) add(x<<1, l, mid, tl, tr, v);
    else if(tl > mid) add(x<<1|1, mid+1, r, tl, tr, v);
    else add(x<<1, l, mid, tl, mid, v), add(x<<1|1, mid+1, r, mid+1, tr, v);
    pushup(x);
}

void mdf(int x, int l, int r, int pos) {
    if(l == r) return ;
    pushdown(x);
    int mid = (l+r)>>1;
    if(pos <= mid) mdf(x<<1, l, mid, pos);
    else mdf(x<<1|1, mid+1, r, pos);
    pushup(x);
}

int main() {
    freopen("disk.in", "r", stdin);
    freopen("disk.out", "w", stdout);

    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; ++i)
        scanf("%d", w+i*2-1);
    for(int i = 1; i <= n; ++i)
        scanf("%d", w+i*2);
    w[0] = INF;
    maketree(1, 1, 2*n);
    while(k--) {
        std::pair<int,int> cur = merge(tree[1].a1, tree[1].a2);
        ans += w[cur.first]+w[cur.second];
        if(cur.first&1) add(1, 1, 2*n, cur.first, cur.second-1, 1);
        else add(1, 1, 2*n, cur.first, cur.second-1, -1);
        w[cur.first] = INF, mdf(1, 1, 2*n, cur.first);
        w[cur.second] = INF, mdf(1, 1, 2*n, cur.second);
    }
    std::cout << ans << std::endl;
    
    fclose(stdin);fclose(stdout);
    return 0;
}
