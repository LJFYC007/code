/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年11月08日 星期日 20时59分22秒
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
    freopen("input.txt", "w", stdout);
    int n = 4, m = 5; printf("%d %d\n", n, m);
    REP(i, 1, n) printf("%d ", rand() % 5 + 1); puts("");
    REP(i, 1, m) printf("%d %d\n", rand() % n + 1, rand() % n + 1);
    return 0;
}
