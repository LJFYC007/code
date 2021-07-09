/***************************************************************
	File name: F.cpp
	Author: ljfcnyali
	Create time: 2019年07月20日 星期六 20时37分11秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 100;

int ans[maxn], a[maxn], h[maxn];

inline void js(int n)
{
    int sum = 0;
    REP(i, 1, n) sum += abs(i - a[i]);
    ++ ans[sum];
}

inline void DFS(int x, int n)
{
    if ( x == n + 1 ) { js(n); return ; }
    REP(i, 1, n) if ( !h[i] ) { h[i] = 1; a[x] = i; DFS(x + 1, n); h[i] = 0; }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    REP(n, 1, 10)
    {
        mem(ans); mem(h);
        DFS(1, n);
        REP(i, 0, n * n) printf("%d ", ans[i]); puts("");
    }
    return 0;
}
