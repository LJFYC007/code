/***************************************************************
	File name: D1.cpp
	Author: ljfcnyali
	Create time: 2020年11月16日 星期一 10时54分44秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 4e5 + 10;

int n, a[maxn], t[maxn], val, b[maxn], ans; 

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) { scanf("%d", &a[i]); ++ t[a[i]]; }
    REP(i, 1, 100) if ( t[i] > t[val] ) val = i;
    REP(i, 1, 100) if ( t[i] == t[val] && i != val ) { printf("%d\n", n); return 0; }
    REP(i, 1, 100)
    {
        if ( i == val ) continue ;
        REP(j, 0, n + n) t[j] = -1;
        REP(j, 1, n) 
            if ( a[j] == val ) b[j] = 1;
            else if ( a[j] == i ) b[j] = -1;
            else b[j] = 0;
        REP(j, 1, n) b[j] += b[j - 1];
        REP(j, 0, n) if ( t[b[j] + n] == -1 ) t[b[j] + n] = j;
        REP(j, 1, n) if ( t[b[j] + n] != -1 ) ans = max(ans, j - t[b[j] + n]);
    }
    printf("%d\n", ans);
    return 0;
}
