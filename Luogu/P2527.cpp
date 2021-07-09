/***************************************************************
	File name: P2527.cpp
	Author: ljfcnyali
	Create time: 2019年06月24日 星期一 20时23分31秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

LL n, k, a[10010], Max, s;
priority_queue <LL, vector<LL>, greater<LL> > Q;

inline void DFS(LL sum, LL x)
{
    if ( x == n + 1 ) return ;
    DFS(sum, x + 1);
    while ( sum <= 2000000000000 )
    {
        sum *= a[x]; 
        if ( sum > Max && s > k ) return ; 
        Max = max(Max, sum);
        Q.push(sum); ++ s;
        DFS(sum, x + 1);
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cin >> n >> k;
    REP(i, 1, n) { scanf("%lld", &a[i]); if ( a[i] == 1 ) { printf("%lld\n", k); return 0; } }
    DFS(1, 1);
    REP(i, 1, k - 1) Q.pop();
    printf("%lld\n", Q.top());
    return 0;
}
