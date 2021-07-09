/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年11月22日 星期日 09时31分08秒
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
    freopen("gcds.in", "w", stdout);
    int n = 10, N = 10; printf("%d\n", n);
    srand(time(0));
    REP(i, 1, n)
    {
        int len = rand() % (n - i + 1) + 1;
        int val = rand() % N + 1;
        int t = N / val;
        REP(j, 1, len) printf("%d ", (rand() % t + 1) * val);
        i += len - 1;
    }
    return 0;
}
