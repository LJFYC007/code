/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年11月27日 星期五 09时26分20秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int p[maxn], f[maxn];

int main()
{
    freopen("dierti.in", "w", stdout);
    int n = 800000; printf("%d\n", n);
    srand(time(0));
    puts("0");
    REP(i, 2, n) printf("%d\n", rand() % (i - 1) + 1);
    // REP(i, 2, n) printf("%d\n", rand() % (i - 1) + 1);
    return 0;
}
