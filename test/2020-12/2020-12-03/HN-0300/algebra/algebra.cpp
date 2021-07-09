/***************************************************************
	File name: algebra.cpp
	Author: ljfcnyali
	Create time: 2020年12月03日 星期四 08时01分11秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

int n, m, k, a[200][10], cnt, ans, b[10];
map<vector<int>, int> Map[10];

inline void DFS1(int x, int num)
{
    if ( num > k || num + m - x + 1 < k ) return ;
    if ( x == m + 1 ) 
    {
        ++ cnt; REP(i, 1, m) a[cnt][i] = b[i];
        return ;
    }
    b[x] = 0; DFS1(x + 1, num);
    b[x] = 1; DFS1(x + 1, num + 1);
}

inline int DFS2(int x, vector<int> p)
{
    REP(i, 1, m) if ( p[i] > k || p[i] + n - x + 1 < k ) return 0;
    if ( x == n + 1 ) return 1;
    sort(p.begin(), p.end());
    if ( Map[x].count(p) ) return Map[x][p];
    int ret = 0;
    REP(i, 1, cnt)
    {
        REP(j, 1, m) p[j] += a[i][j];
        ret += DFS2(x + 1, p);
        REP(j, 1, m) p[j] -= a[i][j];
    }
    Map[x][p] = ret; return ret;
}

signed main()
{
    freopen("algebra.in", "r", stdin);
    freopen("algebra.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &m, &k);
    DFS1(1, 0); vector<int> p; p.resize(m + 1); 
    printf("%lld\n", DFS2(1, p));
    return 0;
}
