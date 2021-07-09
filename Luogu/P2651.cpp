/***************************************************************
	File name: P2651.cpp
	Author: ljfcnyali
	Create time: 2019年06月24日 星期一 10时15分05秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

inline int gcd(int a, int b)
{
    if ( !b ) return a;
    return gcd(b, a % b); 
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int T, n;
    scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%d", &n);
        int a, b; scanf("%d%d", &a, &b);
        b = b / gcd(a, b);
        REP(i, 3, n)
        {
            int x; scanf("%d", &x);
            b = b / gcd(b, x);
        }
        if ( b == 1 ) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
