/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2019年10月31日 星期四 08时29分43秒
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
    freopen("life.in", "w", stdout);
    srand(time(0));
    int n = 10, m = 10; 
    printf("%d %d\n", n, m);
    REP(i, 1, n) printf("%d ", rand() % 3); puts("");
    int l = 0, r = 0;
    REP(i, 1, m)
    {
        l = l + rand() % 2; r = r + rand() % 2;
        while ( r < l ) ++ r;
        printf("%d %d %d\n", l, r, rand() % 10 + 1);
    }
    return 0;
}
