/***************************************************************
	File name: butterfly.cpp
	Author: ljfcnyali
	Create time: 2019年10月09日 星期三 19时03分43秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

int n, m;

inline void Solve1()
{
    if ( n % 2 == 0 ) 
        REP(i, 1, n) { REP(j, 1, m) printf("%c", i <= n / 2 ? '(' : ')'); puts(""); }
    else
        REP(i, 1, n) { REP(j, 1, m) printf("%c", j <= m / 2 ? '(' : ')'); puts(""); }
}

inline void Solve2()
{
    if ( n > m )
    {
        REP(i, 1, n / 2) { for ( int j = 1; j <= m; j += 2 ) printf("()"); puts(""); } 
        REP(i, n / 2 + 1, n) { REP(j, 1, m) printf("%c", j <= m / 2 ? '(' : ')'); puts(""); }
    }
    else
    {
        REP(i, 1, n) 
        { 
            REP(j, 1, m)
                if ( j <= m / 2 )
                {
                    if ( i % 2 == 1 ) printf("(");
                    else printf(")");
                }
                else
                {
                    if ( i <= n / 2 ) printf("(");
                    else printf(")");
                }
            puts("");
        }
    }
}

inline void Solve3()
{
    REP(i, 1, n) 
    {
        REP(j, 1, m)
        {
            if ( i == 1 || j == 1 ) printf("(");
            else if ( i == n || j == m ) printf(")");
            else printf("%c", (i % 2 == j % 2) ? '(' : ')');
        }
        puts("");
    }
}
    
int main()
{
    freopen("butterfly.in", "r", stdin);
    freopen("butterfly.out", "w", stdout);
    scanf("%d%d", &n, &m);
    if ( n % 2 == 1 || m % 2 == 1 ) Solve1();
    else if ( n <= 4 || m <= 4 ) Solve2();
    else Solve3();
    return 0;
}

