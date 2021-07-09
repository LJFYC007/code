/***************************************************************
	File name: flower.cpp
	Author: ljfcnyali
	Create time: 2020年11月17日 星期二 09时21分09秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, a[maxn], lim = 4000, ans[maxn], st[17][maxn], lg[maxn];
struct data 
{ 
    int l, r, id;
    data ( int a = 0, int b = 0, int c = 0 ) { l = a; r = b; id = c; }
} ;
vector<data> Q[maxn];

inline int Get(int l, int r)
{
    int x = lg[r - l + 1];
    return max(st[x][l], st[x][r - (1 << x) + 1]);
}

int main()
{
    freopen("flower.in", "r", stdin);
    freopen("flower.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, n) scanf("%d", &a[i]);
    if ( n <= 4000 )
    {
        REP(i, 1, m)
        {
            int l, r, k; scanf("%d%d%d", &l, &r, &k);
            int Max = 0;
            REP(j, l, r) Max = max(Max, a[j] % k);
            printf("%d\n", Max);
        }
        return 0;
    }
    REP(i, 1, m) { int l, r, k; scanf("%d%d%d", &l, &r, &k); Q[k].push_back(data(l, r, i)); }
    lg[2] = 1; REP(i, 3, n) lg[i] = lg[i >> 1] + 1;
    REP(k, 1, lim)
    {
        if ( !Q[k].size() ) continue ;
        REP(i, 1, n) { st[0][i] = a[i] % k; REP(j, 1, 16) st[j][i] = 0; }
        REP(j, 1, 16) REP(i, 1, n - (1 << j - 1)) st[j][i] = max(st[j - 1][i], st[j - 1][i + (1 << j - 1)]);
        for ( auto it : Q[k] ) ans[it.id] = Get(it.l, it.r);
    }
    REP(i, 1, m) printf("%d\n", ans[i]); 
    return 0;
}
