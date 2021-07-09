/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年09月16日 星期三 21时24分43秒
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
    freopen("chocolate.in", "w", stdout);
    int n = 5; printf("%d\n", n);
    srand(time(0));
    REP(i, 1, n)
    {
        int len = rand() % 3;
        REP(j, 1, len) printf("%c", rand() % 4 + 'a');
        printf("#");
        len = rand() % 3;
        REP(j, 1, len) printf("%c", rand() % 4 + 'a');
        printf("\n");
    }
    return 0;
    /*
    int n = 2000; printf("%d\n", n);
    srand(time(0));
    REP(i, 1, n)
    {
        int len = rand() % 10;
        REP(j, 1, len) printf("%c", rand() % 5 + 'a');
        printf("#");
        len = rand() % 10;
        REP(j, 1, len) printf("%c", rand() % 5 + 'a');
        printf("\n");
    }

    int n = 100000; printf("%d\n", n);
    srand(time(0));
    REP(i, 1, n)
    {
        int len = rand() % 10;
        REP(j, 1, len) printf("%c", rand() % 26 + 'a');
        printf("#");
        len = rand() % 10;
        REP(j, 1, len) printf("%c", rand() % 26 + 'a');
        printf("\n");
    }
    */
    return 0;
}
