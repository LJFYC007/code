/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年10月07日 星期三 10时36分09秒
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
    freopen("sage.in", "w", stdout);
    int T = 10; printf("%d\n", T);
    REP(i, 1, T)
    {
        int m = rand() % 20000 + 10;
        int a = rand() % m - 1;
        int b = rand() % m + m;
        printf("%d %d %d %d %d %d\n", m, rand() % 1000000000, a, b, rand() % 1000000000, rand() % 1);
    }
    return 0;
}
