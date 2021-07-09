/***************************************************************
	File name: P3674.cpp
	Author: ljfcnyali
	Create time: 2019年10月24日 星期四 21时47分52秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( register int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 100010;
const int N = 100000;

int n, m, a[maxn], sum[maxn], pos[maxn], Block;
bool ans[maxn];
bitset<maxn> s1, s2, s;

struct node
{
    int opt, l, r, x, id;
    bool operator < (const node &a) const { return pos[l] < pos[a.l] || (pos[l] == pos[a.l] && ((pos[l] & 1) ? r < a.r : r > a.r)); }
} q[maxn];

inline void add(const int x) { ++ sum[a[x]]; if ( sum[a[x]] == 1 ) { s1.set(a[x]); s2.set(N - a[x]); } }

inline void del(const int x) { -- sum[a[x]]; if ( !sum[a[x]] ) { s1.reset(a[x]); s2.reset(N - a[x]); } }

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    Block = sqrt(n);
    REP(i, 1, n) { scanf("%d", &a[i]); pos[i] = (i - 1) / Block; }
    REP(i, 1, m) { scanf("%d%d%d%d", &q[i].opt, &q[i].l, &q[i].r, &q[i].x); q[i].id = i; }
    sort(q + 1, q + m + 1);
    int L = 1, R = 0;
    REP(i, 1, m)
    {
        while ( L < q[i].l ) del(L ++);
        while ( L > q[i].l ) add(-- L);
        while ( R < q[i].r ) add(++ R);
        while ( R > q[i].r ) del(R --);
        if ( q[i].opt == 1 ) ans[q[i].id] = (s1 & (s1 << q[i].x)).any();
        if ( q[i].opt == 2 ) ans[q[i].id] = (s1 & (s2 >> (N - q[i].x))).any();
        if ( q[i].opt == 3 ) 
        {
            for ( int j = 1; j * j <= q[i].x; ++ j ) 
            {
                if ( q[i].x % j != 0 ) continue ;
                if ( sum[j] && sum[q[i].x / j] ) ans[q[i].id] = true;
            }
        }
    }
    REP(i, 1, m) printf("%s\n", ans[i] ? "hana" : "bi");
    return 0;
}
