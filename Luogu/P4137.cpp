/***************************************************************
	File name: P4137.cpp
	Author: ljfcnyali
	Create time: 2019年08月19日 星期一 18时27分16秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 200010;

int a[maxn], n, m, cnt[maxn], ans, block, p[maxn];

struct node
{
    int l, r, id;
    bool operator < (const node &a) const { return p[l] < p[a.l] || (p[l] == p[a.l] && r < a.r); }
} q[maxn];

inline void Add(int x) 
{ 
    ++ cnt[a[x]]; 
    if ( cnt[a[x]] == 1 ) 
    {
        int tmp = a[x];
        if ( ans == tmp ) while ( ++ tmp ) if ( cnt[tmp] == 0 ) { ans = tmp; return ; }
    }
}

inline void Del(int x) { -- cnt[a[x]]; if ( !cnt[a[x]] ) ans = min(ans, a[x]); }

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m); block = sqrt(n);
    REP(i, 1, n) { scanf("%d", &a[i]); p[i] = (i - 1) / block + 1; }
    REP(i, 1, m) { scanf("%d%d", &q[i].l, &q[i].r); q[i].id = i; }
    sort(q + 1, q + m + 1);
    int L = 1, R = 1; ++ cnt[a[1]]; if ( a[1] == 0 ) ans = 1; 
    REP(i, 1, m)
    {
        while ( L < q[i].l ) Del(L ++);
        while ( L > q[i].l ) Add(-- L);
        while ( R < q[i].r ) Add(++ R);
        while ( R > q[i].r ) Del(R --);
        p[q[i].id] = ans;
    }
    REP(i, 1, m) printf("%d\n", p[i]);
    return 0;
}
