/***************************************************************
	File name: CF1203E.cpp
	Author: ljfcnyali
	Create time: 2019年08月14日 星期三 21时07分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 150010;

int n, a[maxn], cnt;
bool vis[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d", &a[i]);
    sort(a + 1, a + n + 1);
    REP(i, 1, n)
    {
        if ( a[i] > 1 && !vis[a[i] - 1] ) { ++ cnt; vis[a[i] - 1] = true; }
        else if ( !vis[a[i]] ) { vis[a[i]] = true; ++ cnt; }
        else if ( !vis[a[i] + 1] ) { vis[a[i] + 1] = true; ++ cnt; }
    }
    printf("%d\n", cnt);
    return 0;
}
