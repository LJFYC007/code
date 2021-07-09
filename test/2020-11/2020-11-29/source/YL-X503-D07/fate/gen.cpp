/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali-akioi
	Create time: 2020年11月29日 星期日 10时58分47秒
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
    freopen("fate.in", "w", stdout);
    int n = 500, q = 500, Mod = 239128312;
    printf("%d %d %d\n", n, q, Mod);
    REP(i, 1, q) printf("%d\n", i);
    return 0;
}
