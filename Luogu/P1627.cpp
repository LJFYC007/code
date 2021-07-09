/***************************************************************
	File name: P1627.cpp
	Author: ljfcnyali
	Create time: 2019年06月22日 星期六 14时28分10秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 100010;

map<int, int> Map;

int n, m, a[maxn], q, sum, ans;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m); 
    REP(i, 1, n) { scanf("%d", &a[i]); if ( a[i] == m ) q = i; }
    REP(i, q, n) { if ( a[i] > m ) ++ sum; if ( a[i] < m ) -- sum; ++ Map[sum]; }
    sum = 0;
    for ( int i = q; i >= 1; -- i )
    { 
        if ( a[i] > m ) ++ sum; 
        if ( a[i] < m ) -- sum; 
        ans += Map[0 - sum]; 
    }
    printf("%d\n", ans);
    return 0;
}
