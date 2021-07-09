/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年10月02日 星期五 08时36分24秒
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
    freopen("string.in", "w", stdout);
    srand(time(0));
    int n = 100000, m = 99999;
    printf("%d %d\n", n, m);
    REP(i, 1, n) printf("%c", rand() % 26 + 'a'); puts("");
    REP(i, 1, m)
    {
        int l = rand() % n + 1, r = rand() % n + 1;
        if ( l > r ) swap(l, r);
        printf("%d %d %d\n", l, r, rand() % 2);
    }
    return 0;
}
