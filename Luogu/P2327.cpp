/***************************************************************
	File name: P2327.cpp
    Author: ljfcnyali
	Create time: 2019年06月12日 星期三 14时33分26秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 10010;

int a[maxn], n, ans, p[maxn];
bool flag;

inline bool solve(int num)
{
    p[1] = num;
    flag = true;
    REP(i, 2, n + 1)
    {
        p[i] = a[i - 1] - p[i - 1] - p[i - 2];
        if ( p[i] != 0 && p[i] != 1 ) return false;
        if ( i == n + 1 && p[i] != 0 ) return false;
    }
    return true;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d", &a[i]);
    if ( solve(0) ) ++ ans;
    if ( solve(1) ) ++ ans; 
    printf("%d\n", ans);
    return 0;
}
