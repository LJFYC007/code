/***************************************************************
	File name: 1.cpp
	Author: ljfcnyali
	Create time: 2020年12月19日 星期六 10时57分13秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, k, a[10];

inline void DFS(int x)
{
    if ( x == 7 )
    {
        if ( a[x] == k ) 
        {
            REP(i, 1, 7) printf("%d ", a[i]); puts("");
        }
        return ;
    }
    REP(i, 1, x) { a[x + 1] = a[x] + a[i]; DFS(x + 1); }
}

int main()
{
    scanf("%d", &k);
    a[1] = 1; DFS(1);
    return 0;
}
