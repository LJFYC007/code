/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2020年10月22日 星期四 10时11分19秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int r, m, a[maxn], ans;

inline void DFS(int x, int n)
{
    if ( x == n + 1 ) 
    {
        int ret = 0;
        REP(i, 1, n) REP(j, i + 1, n)
            if ( a[i] == a[j] ) ret = max(ret, max(i, n - j + 1));
        if ( ret == m )
            ++ ans;
        return ;
    }
    REP(i, 1, r) { a[x] = i; DFS(x + 1, n); }
}

int main()
{
    freopen("a.in", "r", stdin);
    freopen("a2.out", "w", stdout);
    cin >> r >> m;
    DFS(1, 6);
    // REP(n, m, 12) DFS(1, n);
    printf("%d\n", ans);
    return 0;
}
