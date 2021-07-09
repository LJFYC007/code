/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2019年12月17日 星期二 20时43分56秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

int main()
{
    freopen("c.in", "w", stdout);
    srand(time(0));
    int n = 10, m = 100;
    printf("1\n%d %d\n", n, m);
    int N = n; n = 0;
    REP(i, 1, N)
    {
        int opt = rand() % 5;
        if ( opt == 0 ) { printf("IF %d %d\n", rand() % m + 1, rand() % m + 1); ++ n; }
        else if ( opt == 1 ) { printf("IG %d %d\n", rand() % m + 1, rand() % m + 1); ++ n; }
        else if ( opt == 4 ) 
        {
            int l = rand() % m, r = rand() % m;
            if ( l > r ) swap(l, r);
            printf("QU %d %d\n", l, r);
        }
        else
        {
            -- n;
            if ( n < 0 ) 
            {
                int l = rand() % m, r = rand() % m;
                if ( l > r ) swap(l, r);
                printf("QU %d %d\n", l, r);
            }
            else if ( opt == 2 ) puts("DF");
            else if ( opt == 3 ) puts("DG");
        }
    }
    return 0;
}
