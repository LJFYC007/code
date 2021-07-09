/***************************************************************
	File name: vegetable.cpp
	Author: ljfcnyali
	Create time: 2020年11月17日 星期二 10时34分20秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define y1 hhakioi
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, q, a[110][110], sum[110][110], ans[maxn]; 
struct node { int x1, y1, x2, y2; } Q[maxn];
vector<pii> p[maxn];

int main()
{
    freopen("vegetable.in", "r", stdin);
    freopen("vegetable.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &q);
    REP(i, 1, n) REP(j, 1, m) { scanf("%d", &a[i][j]); p[a[i][j]].push_back(pii(i, j)); }
    REP(i, 1, q) scanf("%d%d%d%d", &Q[i].x1, &Q[i].y1, &Q[i].x2, &Q[i].y2);
    REP(o, 1, maxn - 10)
    {
        if ( !p[o].size() ) continue ;
        mem(sum); for ( auto it : p[o] ) sum[it.first][it.second] = 1;
        REP(i, 1, n) REP(j, 1, m) sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
        REP(i, 1, q)
        {
            int x = sum[Q[i].x2][Q[i].y2] - sum[Q[i].x2][Q[i].y1 - 1] - sum[Q[i].x1 - 1][Q[i].y2] + sum[Q[i].x1 - 1][Q[i].y1 - 1];
            ans[i] += x * x;
        }
    }
    REP(i, 1, q) printf("%d\n", ans[i]);
    return 0;
}
