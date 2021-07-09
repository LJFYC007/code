/***************************************************************
	File name: biology.cpp
	Author: ljfcnyali
	Create time: 2019年08月01日 星期四 10时30分32秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

int n, k, ans, a[110];
char s[110];

inline void DFS(int x, int sum)
{
    sum %= k;
    if ( x == n + 1 ) { ans = max(ans, sum); return ; }
    DFS(x + 1, sum);
    if ( a[x] == 1 ) DFS(x + 1, sum * 2);
    else DFS(x + 1, sum + 1);
}

int main()
{
    freopen("biology.in", "r", stdin);
    freopen("biology.out", "w", stdout);
    scanf("%d%d", &n, &k);
    k = 1 << k;
    scanf("%s", s);
    REP(i, 1, n) if ( s[i - 1] == 'A' || s[i - 1] == 'G' ) a[i] = 1;
    DFS(1, 0);
    printf("%d\n", ans);
    return 0;
}
