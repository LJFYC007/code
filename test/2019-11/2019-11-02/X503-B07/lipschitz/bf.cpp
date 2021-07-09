/***************************************************************
	File name: lipschitz.cpp
	Author: ljfcnyali
	Create time: 2019年11月02日 星期六 08时33分33秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 100010;

int n, m, a[maxn], Max[maxn << 2];

int main()
{
    freopen("lipschitz.in", "r", stdin);
    freopen("lipschitz1.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d", &a[i]);
    scanf("%d", &m);
    REP(i, 1, m)
    {
        int opt, l, r; scanf("%d%d%d", &opt, &l, &r);
        if ( opt == 0 ) { a[l] = r; continue ; }
        else 
        { 
            int ans = 0; 
            REP(j, l, r - 1) REP(k, j + 1, r)
                ans = max(ans, (abs(a[j] - a[k]) - 1) / (k - j) + 1);
            printf("%d\n", ans); 
        }
    }
    return 0;
}
