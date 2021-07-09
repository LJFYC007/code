/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年07月12日 星期日 10时26分38秒
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
    freopen("C.in", "w", stdout);
    srand(time(0));
    int n = 4, m = 6, L = 3;
    printf("%d %d\n", n, m); 
    REP(i, 1, n)
    {
        int len = rand() % L + 1;
        REP(j, 1, len) printf("%c", rand() % 3 + 'a');
        printf(" %d\n", rand() % 10 - 5);
    }
    REP(i, 1, m) printf("%c", rand() % 3 + 'a');
    return 0;
}
