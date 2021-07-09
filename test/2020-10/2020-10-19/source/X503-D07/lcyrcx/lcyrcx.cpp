/***************************************************************
	File name: lcyrcx.cpp
	Author: ljfcnyali
	Create time: 2020年10月19日 星期一 15时26分30秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1010;

int n, k, a[maxn][maxn], b[maxn][maxn];
char s[maxn];
vector<pii> p;

inline bool Check(int x, int y)
{
    if ( x + k - 1 > n ) return false;
    if ( y + k - 1 > n ) return false;
    REP(j, y, y + k - 1)
        if ( b[x + k - 1][j] - b[x - 1][j] > 0 )
            return false;
    return true;
}

inline void Build()
{
    REP(i, 1, n)
    {
        b[1][i] = a[1][i];
        REP(j, 2, n) b[j][i] = a[j][i] + b[j - 1][i];
    }
}

int main()
{
    freopen("lcyrcx.in", "r", stdin);
    freopen("lcyrcx.out", "w", stdout);
    scanf("%d%d", &n, &k);
    REP(i, 1, n) 
    {
        scanf("%s", s + 1);
        REP(j, 1, n) a[i][j] = s[j] - '0';
    }
    Build();
    REP(i, 1, n) REP(j, 1, n)
    {
        if ( !Check(i, j) ) continue ;
        p.push_back(pii(i, j));
        REP(x, i, i + k - 1) REP(y, j, j + k - 1) a[x][y] = 1;
        Build();
        if ( p.size() == 2 ) goto Finish ;
    }
Finish : ;
    if ( p.size() == 0 ) { puts("yc"); return 0; }
    if ( p.size() == 1 ) { puts("rx"); return 0; }
    int sum = 0;
    REP(i, 1, n) REP(j, 1, n) sum += a[i][j];
    if ( sum % 2 == 0 ) puts("yc");
    else puts("rx");
    return 0;
}
