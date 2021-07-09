/***************************************************************
	File name: CF1030C.cpp
	Author: ljfcnyali
	Create time: 2019年08月16日 星期五 14时28分01秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 110;

int n, a[maxn];

inline bool Check(int x)
{
    int sum = 0, num = 0;
    REP(i, 1, n)
    {
        if ( sum == x ) { sum = a[i]; ++ num; continue ; }
        sum += a[i];
        if ( sum > x ) return false;
    }
    if ( num <= 1 ) return false;
    if ( sum != x && sum != 0 )return false;
    return true;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n); getchar();
    REP(i, 1, n) a[i] = getchar() - '0';
    REP(i, 0, 900) if ( Check(i) ) { puts("YES"); return 0; }
    puts("NO");
    return 0;
}
