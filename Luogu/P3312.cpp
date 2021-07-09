/***************************************************************
	File name: P3312.cpp
	Author: ljfcnyali
	Create time: 2019年09月02日 星期一 18时49分31秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 100010;

int T, miu[maxn], prime[maxn], tot, Max = 100000;
int f[maxn], g[maxn], c[maxn], ans[maxn];
bool vis[maxn];
struct node
{
    int n, m, a, id;
    bool operator < (const node &x) const { return a < x.a; } 
} q[20010];
struct node1
{
    int pos, val;
    bool operator < (const node1 &a) const { return val < a.val; }
} F[maxn];

inline int lowbit(int x) { return x & -x; }

inline void Modify(int pos, int val)
{
    for ( int i = pos; i <= Max; i += lowbit(i) ) 
        c[i] += val;
}

inline int Query(int pos)
{
    int sum = 0;
    for ( int i = pos; i >= 1; i -= lowbit(i) ) 
        sum += c[i];
    return sum;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &T);
    REP(i, 1, T) scanf("%d%d%d", &q[i].n, &q[i].m, &q[i].a), q[i].id = i;
    sort(q + 1, q + T + 1);
    f[1] = g[1] = miu[1] = 1;
    REP(i, 2, Max)
    {
        if ( !vis[i] ) { g[i] = f[i] = i + 1; miu[i] = -1; prime[++ tot] = i; }
        for ( int j = 1; j <= tot && i * prime[j] <= Max; ++ j )
        {
            vis[i * prime[j]] = true;
            if ( i % prime[j] == 0 ) 
            {
                miu[i * prime[j]] = 0;
                g[i * prime[j]] = g[i] * prime[j] + 1;
                f[i * prime[j]] = f[i] / g[i] * g[i * prime[j]];
                break ;
            }
            miu[i * prime[j]] = -miu[i];
            g[i * prime[j]] = 1 + prime[j];
            f[i * prime[j]] = f[i] * f[prime[j]];
        }
    }
    REP(i, 1, Max) F[i].pos = i, F[i].val = f[i];
    sort(F + 1, F + Max + 1);
    int now = 1;
    REP(o, 1, T)
    {
        while ( now <= Max && F[now].val <= q[o].a ) 
        {
            for ( int j = F[now].pos; j <= Max; j += F[now].pos ) 
                Modify(j, F[now].val * miu[j / F[now].pos]);
            ++ now;
            // cerr << now << " " << F[now].val << " " << F[now].pos << endl;
        }
        int i = 1;
        while ( i <= min(q[o].n, q[o].m) ) 
        {
            int j = min(q[o].n / (q[o].n / i), q[o].m / (q[o].m / i));
            // cerr << i << " " << j << endl;
            ans[q[o].id] += (Query(j) - Query(i - 1)) * (q[o].n / i) * (q[o].m / i);
            i = j + 1;
            // cerr << i << " " << j << endl;
        }
        ans[q[o].id] &= ~(1 << 31);
    }
    REP(i, 1, T) printf("%d\n", ans[i]);
    return 0;
}
