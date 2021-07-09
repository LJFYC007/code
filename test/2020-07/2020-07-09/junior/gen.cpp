/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年07月09日 星期四 10时30分38秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int main()
{
    freopen("junior.in", "w", stdout);
    int T = 10, n = 30 - 1;
    printf("%d\n", T);
    srand(time(0));
    while ( T -- ) 
    {
        REP(i, 0, 7) printf("%d", rand() % 2); puts("");
        REP(i, 1, n)
        {
            int x = rand() % 3;
            if ( x <= 1 ) printf("%d", x);
            else printf("?");
        }
        puts("");
    }
    return 0;
}
