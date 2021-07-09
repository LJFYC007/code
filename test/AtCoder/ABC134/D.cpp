/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2019年07月20日 星期六 20时13分42秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 200010;

int n, a[maxn], sum;
bool vis[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n); REP(i, 1, n) scanf("%d", &a[i]);
    for ( int i = n; i >= 1; -- i )
    {
        int s = 0;
        for ( int j = i + i; j <= n; j += i ) s += vis[j];
        if ( s % 2 != a[i] ) { vis[i] = true; ++ sum; }
    }
    printf("%d\n", sum); REP(i, 1, n) if ( vis[i] ) printf("%d ", i); puts("");
    return 0;
}
