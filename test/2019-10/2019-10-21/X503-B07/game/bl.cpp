/***************************************************************
	File name: bl.cpp
	Author: ljfcnyali
	Create time: 2019年10月21日 星期一 11时43分34秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 20;

int n, a[maxn], b[maxn], ans[maxn], num, sum, c[maxn];
bool use[maxn];

inline void Check()
{
    REP(i, 1, n) if ( c[i] < ans[i] ) return ; else if ( c[i] > ans[i] ) break ; 
    REP(i, 1, n) ans[i] = c[i];
}

inline void DFS(int x)
{
    if ( x == n + 1 ) 
    { 
        if ( num == sum ) Check(); 
        else if ( num > sum ) { REP(i, 1, n) ans[i] = c[i]; sum = num; }
        return ; 
    }
    REP(i, 1, n)
        if ( !use[i] ) 
        {
            use[i] = true;
            c[x] = b[i];
            if ( c[x] > a[x] ) ++ num;
            DFS(x + 1);
            if ( c[x] > a[x] ) -- num;
            use[i] = false;
        }
}

int main()
{
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, n) scanf("%d", &b[i]);
    DFS(1);
    REP(i, 1, n) printf("%d ", ans[i]); puts("");
    return 0;
}
