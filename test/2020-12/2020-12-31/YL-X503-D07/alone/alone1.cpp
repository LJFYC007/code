/***************************************************************
	File name: alone.cpp
	Author: ljfcnyali
	Create time: 2020年12月31日 星期四 10时41分32秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, a[1010][1010], Ans;
vector<int> p, q;

inline bool Check()
{
    for ( int i = 0; i < q.size(); ++ i ) for ( int j = i + 1; j < q.size(); ++ j ) 
        if ( a[q[i]][q[j]] ) return false;
    return true;
}

int main()
{
    int op; scanf("%d", &op);
    scanf("%d%d", &n, &m);
    REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); a[u][v] = a[v][u] = true; }     
    REP(i, 1, (1 << n) - 1) 
    {
        q.clear();
        REP(j, 1, n) if ( (i >> j - 1) & 1 ) q.push_back(j);
        if ( q.size() <= Ans ) continue ;
        if ( Check() ) { Ans = q.size(); p = q; }
    }
    printf("%d\n", Ans);
    for ( auto it : p ) cout << it << endl;
    return 0;
}
