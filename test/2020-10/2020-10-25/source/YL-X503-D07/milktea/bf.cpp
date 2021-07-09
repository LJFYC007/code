/***************************************************************
	File name: milktea.cpp
	Author: ljfcnyali
	Create time: 2020年10月25日 星期日 09时24分19秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int n, m, k, a[maxn], b[maxn];
struct node { int op, l, r, val; } Q[maxn];

int main()
{
    freopen("milktea.in", "r", stdin);
    freopen("milktea1.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &k);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, m) 
    { 
        scanf("%d%d%d", &Q[i].op, &Q[i].l, &Q[i].r); 
        if ( Q[i].op == 1 ) scanf("%d", &Q[i].val);
    }
    REP(o, 1, k)
    {
        int l, r; LL ans = 0; scanf("%d%d", &l, &r);
        REP(i, 1, n) b[i] = a[i];
        REP(i, l, r)
        {
            if ( Q[i].op == 1 ) REP(j, Q[i].l, Q[i].r) b[j] += Q[i].val;
            else REP(j, Q[i].l, Q[i].r) ans += b[j];
        }
        cout << ans << endl;
    }
    return 0;
}
