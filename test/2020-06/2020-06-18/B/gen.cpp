/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年05月24日 星期日 10时25分40秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

bool vis[maxn];

int main()
{
    freopen("B.in", "w", stdout);
    srand(time(0));
    int n = 100000, m = 1000;
    printf("%d\n", n);
    REP(i, 1, m) printf("%c", rand() % 4 + 'A');
    puts("");
    return 0;
}
