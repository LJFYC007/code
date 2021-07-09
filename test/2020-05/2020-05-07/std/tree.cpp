#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

#define ll long long

const int N = 1000, K = 2050;
const int FULL = 1e9;
const int MOD = 998244353;

int n, k;
int a[N+9];
int fac[K+9];
int inv[K+9];
struct graph {
    int sz, head[N+9], to[N*2+9], p[N*2+9], ne[N*2+9];
    graph() {
        sz = 1, memset(head, 0, sizeof head);
    }
    inline void addedge(int u, int v, int _p) {
        to[sz] = v, p[sz] = _p, ne[sz] = head[u], head[u] = sz++;
        to[sz] = u, p[sz] = _p, ne[sz] = head[v], head[v] = sz++;
    }
}g;
int f[N+9][K+9];
int A[K+9], B[K+9], C[K+9];
int w[K+9];
int ans;

inline int fpm(int a, int b) {
    int ret = 1;
    while(b) {
        if(b&1) ret = 1ll*ret*a%MOD;
        a = 1ll*a*a%MOD, b >>= 1;
    }
    return ret;
}

inline void DFT(int *A, int n, int flag) {
    for(int i = 0; i < n; ++i) {
        int s = i, p = 0;
        for(int j = 1; j < n; j <<= 1)
            p = p<<1|(s&1), s >>= 1;
        if(p < i) std::swap(A[i], A[p]);
    }
    int wn = fpm(3, (MOD-1)/n);
    w[0] = w[n] = 1;
    for(int i = 1; i < n; ++i)
        w[i] = 1ll*w[i-1]*wn%MOD;
    for(int l = 2; l <= n; l <<= 1)
        for(int i = 0; i < n; i += l)
            for(int j = 0; j < (l>>1); ++j) {
                int u = A[i+j], v = 1ll*A[i+j+(l>>1)]*(flag==1?w[n/l*j]:w[n-n/l*j])%MOD;
                A[i+j] = (u+v)%MOD, A[i+j+(l>>1)] = (u-v+MOD)%MOD;
            }
    if(flag == -1) {
        int invn = fpm(n, MOD-2);
        for(int i = 0; i < n; ++i)
            A[i] = 1ll*A[i]*invn%MOD;
    }
}

inline void mult(int *a, int *b) {
    int N = 1;
    while(N <= 2*k) N <<= 1;
    std::fill(A, A+N, 0);
    std::fill(B, B+N, 0);
    std::fill(C, C+N, 0);
    for(int i = 0; i <= k; ++i) {
        A[i] = 1ll*a[i]*inv[i]%MOD;
        B[i] = 1ll*b[i]*inv[i]%MOD;
    }
    DFT(A, N, 1), DFT(B, N, 1);
    for(int i = 0; i < N; ++i) C[i] = 1ll*A[i]*B[i]%MOD;
    DFT(C, N, -1);
}

void dfs(int now, int fa, int fp) {
    f[now][0] = 1;
    for(int i = 1; i <= k; ++i)
        f[now][i] = 1ll*f[now][i-1]*a[now]%MOD;
    for(int i = g.head[now], to; i; i = g.ne[i])
        if((to = g.to[i]) != fa) {
            int p = g.p[i];
            dfs(to, now, p);
            mult(f[now], f[to]);
            for(int j = 0; j <= k; ++j) {
                f[now][j] = 1ll*f[now][j]*(1-p+MOD)%MOD;
                (f[now][j] += 1ll*p*fac[j]%MOD*C[j]%MOD) %= MOD;
            }
        }
    (ans += 1ll*f[now][k]*(1-fp+MOD)%MOD) %= MOD;
}

int main() {
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);

    scanf("%d%d", &n, &k);
    fac[0] = inv[0] = 1;
    for(int i = 1; i <= k; ++i) {
        fac[i] = 1ll*fac[i-1]*i%MOD;
        inv[i] = fpm(fac[i], MOD-2);
    }
    for(int i = 1; i <= n; ++i)
        scanf("%d", a+i);
    for(int i = 1; i < n; ++i) {
        int u, v, p, q;
        scanf("%d%d%d%d", &u, &v, &p, &q);
        g.addedge(u, v, 1ll*p*fpm(q, MOD-2)%MOD);
    }
    dfs(1, 0, 0);
    printf("%d\n", ans);
    
    fclose(stdin);fclose(stdout);
    return 0;
}
