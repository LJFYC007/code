/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年06月12日 星期五 08时02分48秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

char s[maxn];

int main()
{
    freopen("B.in", "w", stdout);
    srand(time(0));
    int n = 10, m = 20, now = 0;
    printf("%d %d\n", n, m);
    REP(i, 1, m) s[i] = rand() % 4 + 'a';
    REP(i, 1, n - 1)
    {
        int x = rand() % 2;
        if ( x == 0 )
        {
            int len = rand() % 5 + 1;
            len = min(len, m - now);
            if ( !len ) x = 1;
            else
            {
                REP(j, now + 1, now + len) printf("%c", s[j]);
                puts("");
                now += len;
            }
        }
        if ( x == 1 )
        {
            int len = rand() % 5 + 1;
            REP(j, 1, len) printf("%c", rand() % 4 + 'a');
            puts("");
        }
    }
    if ( now != m ) { REP(i, now + 1, m) printf("%c", s[i]); puts(""); }
    else 
    {
        int len = rand() % 5 + 1;
        REP(j, 1, len) printf("%c", rand() % 4 + 'a');
        puts("");
    }
    return 0;
}
