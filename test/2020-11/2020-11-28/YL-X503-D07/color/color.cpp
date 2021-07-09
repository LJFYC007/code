/***************************************************************
	File name: color.cpp
	Author: ljfcnyali-akioi
	Create time: 2020年11月28日 星期六 08时55分54秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n;

int main()
{
    freopen("color.in", "r", stdin);
    freopen("color.out", "w", stdout);
    scanf("%d", &n);

    if ( n == 1 ) 
    {
        puts("1"); puts("1");
        return 0;
    }
    if ( n == 2 ) 
    {
        puts("1"); puts("1 1");
        return 0;
    }
    if ( n == 3 ) 
    {
        puts("2"); puts("1 1 2");
        return 0;
    }
    if ( n == 4 ) 
    {
        puts("2"); puts("1 1 2 2");
        return 0;
    }
    if ( n == 5 ) 
    {
        puts("3"); puts("1 1 2 2 3");
        return 0;
    }
    if ( n == 6 ) 
    {
        puts("3"); puts("1 1 2 2 3 3");
        return 0;
    }

    puts("4");
    REP(i, 1, n) printf("%d ", i % 4 + 1);
    puts("");
    return 0;
}
