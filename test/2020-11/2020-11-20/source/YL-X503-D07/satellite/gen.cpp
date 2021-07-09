/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年11月20日 星期五 16时36分02秒
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
    freopen("satellite.in", "w", stdout);
    int n = 1000, q = 200, w = 1000, h = 1000;
    // int n = 2000, q = 200000, w = 1000000000, h = 1000000000;
    srand(time(0));
    cout << n << " " << q << " " << w << " " << h << " " << rand() << " " << rand() << " " << rand() << endl;
    REP(i, 1, n) printf("%d %d %d\n", rand(), rand() % w + 1, rand() % h + 1);
    REP(i, 1, q) printf("%d %d\n", rand() % w + 1, rand() % h + 1);
    return 0;
}
