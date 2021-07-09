/**************************************************************
    Problem: 3921
    User: 2019gz52
    Language: C++
    Result: Accepted
    Time:569 ms
    Memory:25712 kb
****************************************************************/
 
 
#include<bits/stdc++.h>
#define cs const
#define pb push_back
using namespace std;
 
namespace io{
cs int rlen = 1 << 22 | 1; 
inline char gc() {
    static char buf[rlen], *p1, *p2;
    (p1 == p2) && (p2 = (p1 = buf) + fread(buf, 1, rlen, stdin));
    return p1 == p2 ? EOF : *p1++;
} int gi() {
    int x = 0; char c = gc(); while(!isdigit(c)) c = gc();
    while(isdigit(c)) x = (((x << 2) + x) << 1) + (c ^ 48), c = gc();
    return x; 
}
} using namespace io;
 
cs int Mod = 998244353;
int add(int a, int b) {
    return a + b >= Mod ? a + b - Mod : a + b;
}
int dec(int a, int b) {
    return a - b < 0 ? a - b + Mod : a - b;
}
int mul(int a, int b) {
    return 1ll * a * b % Mod;
}
void Add(int &a, int b) {
    a = add(a, b);
}
void Dec(int &a, int b) {
    a = dec(a, b);
}
void Mul(int &a, int b) {
    a = mul(a, b);
}
int ksm(int a, int b) {
    int ans = 1; for(; b; b >>= 1, Mul(a, a))
    if(b & 1) Mul(ans, a); return ans; 
}
 
cs int N = 3e5 + 5; 
int n, m, a[N];
 
#define mid ((l + r) >> 1)
cs int M = N << 2;
struct lll {
    int sm, mt, w;
    lll operator + (cs lll &x) {
        lll y; 
        y.sm = add(sm, x.sm);
        y.mt = mul(mt, x.mt);
        y.w = add(mul(mt, x.w), mul(w, x.mt));
        return y; 
    }
} t[M]; int ta[M];
void up(int x) {
    t[x] = t[x << 1] + t[x << 1 | 1];
}
void build(int x, int l, int r) {
    ta[x] = 1;
    if(l == r) {
        t[x].sm = t[x].mt = a[l];
        t[x].w = 1; return;
    } 
    build(x << 1, l, mid);
    build(x << 1 | 1, mid + 1, r); up(x);
}
void put(int x, int l, int r, int v) {
    Mul(ta[x], v);
    Mul(t[x].sm, v);
    int z = ksm(v, r - l);
    Mul(t[x].w, z);
    Mul(t[x].mt, mul(z, v));
}
void down(int x, int l, int r) {
    if(ta[x] != 1) put(x << 1, l, mid, ta[x]), 
        put(x << 1 | 1, mid + 1, r, ta[x]), ta[x] = 1; 
}
void mdf(int x, int l, int r, int L, int R, int v) {
    if(L <= l && r <= R) return put(x, l, r, v), void(); 
    down(x, l, r);
    if(L <= mid) mdf(x << 1, l, mid, L, R, v);
    if(R > mid) mdf(x << 1 | 1, mid + 1, r, L, R, v); up(x);
}
lll qry(int x, int l, int r, int L, int R) {
    if(L <= l && r <= R) return t[x]; down(x, l, r);
    if(R <= mid) return qry(x << 1, l, mid, L, R);
    if(L > mid) return qry(x << 1 | 1, mid + 1, r, L, R);
    return qry(x << 1, l, mid, L, R) + 
        qry(x << 1 | 1, mid + 1, r, L, R);
}
#undef mid
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
    n = gi(), m = gi();
    for(int i = 1; i <= n; i++) 
        a[i] = gi();
    build(1, 1, n);
    while(m--) {
        int o = gi();
        int l = gi(), r = gi(), k = gi();
        if(o == 1) {
            mdf(1, 1, n, l, r, k);
        }
        if(o == 2) {
            int m = r - l + 1, ans = 0; 
            if(m - k - 1 >= 0 && ((m - k - 1) & 1 ^ 1)) 
                ans = 1;
            lll z = qry(1, 1, n, l, r);
            if(m & 1 ^ 1) z.mt = dec(0, z.mt);
            if(k == 1) Add(ans, z.mt);
            if(k == 2) {
                if(m > 1){
                    if(m & 1) Dec(ans, z.w);
                    else Add(ans, z.w);
                }
                Add(ans, mul(z.sm, z.mt));
            }
            cout << ans << '\n';
        }
    } return 0; 
}
