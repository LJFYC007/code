/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2019年10月25日 星期五 11时25分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 100010;

int a[maxn];

signed main(int argc, char* argv[])
{
    REP(i, 1, 1000000000) ;
    srand(time(0));
    int n = atoi(argv[1]), S = atoi(argv[2]);
    n = rand() % (n - 5) + 6; S = ((LL)rand() * rand()) % (S - 5) + 6;
    printf("%lld %lld\n", n, S);
    printf("%d %d\n", rand() % 7 + 1, 0);
    printf("%d %d\n", rand() % 10 + 1, 0);
    int x = 10, y = 10;
    REP(i, 3, n)
    {
        x = rand() % 10 + x;
        y = rand() % 10 + y;
        printf("%lld %lld\n", x, y);
    }
    return 0;
}

