/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年11月30日 星期一 19时45分23秒
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
    freopen("input.txt", "w", stdout);
    int n = 3; printf("%d %d\n", n, 3);
    srand(time(0));
    REP(i, 1, n)
    {
        int l = rand() % 8, r = rand() % 8;
        cout << min(l, r) << " " << max(l, r) << endl;
    }
    REP(i, 1, 3) cout << rand() % 5 + 1 << " "; cout << endl;
    return 0;
}
