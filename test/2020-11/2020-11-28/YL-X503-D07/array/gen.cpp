/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali-akioi
	Create time: 2020年11月28日 星期六 09时40分14秒
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
    freopen("array.in", "w", stdout);
    int T = 5000; printf("%d\n", T);
    srand(time(0));
    while ( T -- )
    {
        int n = rand() % 1000 + 1, m = rand() % 200 + 1;
        int k = rand() % 200 + 1, D = rand() % (1000 * m) + 1;
        cout << n << " " << m << " " << k << " " << D << endl;
        REP(i, 1, m) printf("%d ", rand() % 1000 + 1); puts("");
    }
    return 0;
}
