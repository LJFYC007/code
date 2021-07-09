/***************************************************************
	File name: string.cpp
	Author: ljfcnyali
	Create time: 2020年09月13日 星期日 08时50分20秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int n, m, Log[maxn], id[maxn][20], f[maxn * 21], tot, a[maxn];
char s[maxn], t[maxn];
vector<int> num[maxn];

inline int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }

inline void Merge(int a, int b, int x)
{
    int fx = find(id[a][x]), fy = find(id[b][x]);
    if ( fx != fy ) f[fx] = fy;
}

inline void merge(int x, int y) 
{ 
    int fx = find(x), fy = find(y); 
    if ( fx != fy ) { f[fx] = fy; } 
}

int main()
{
    freopen("string.in", "r", stdin);
    freopen("string.out", "w", stdout);
    scanf("%s", s + 1); n = str(s + 1);
    REP(i, 2, n) Log[i] = Log[i >> 1] + 1;
    REP(j, 0, 19) REP(i, 1, n - (1 << j) + 1) { id[i][j] = ++ tot; f[tot] = tot; }
    scanf("%d", &m);
    REP(i, 1, m)
    {
        int a, b, l; scanf("%d%d%d", &a, &b, &l);
        Merge(a, b, Log[l]); Merge(a + l - (1 << Log[l]), b + l - (1 << Log[l]), Log[l]);
    }
    for ( int j = 19; j >= 1; -- j ) 
    {
        m = n - (1 << j) + 1;
        REP(i, 1, m) { a[i] = find(id[i][j]); f[id[i][j] + m] = id[i][j] + m; }
        REP(i, 1, m)
        {
            merge(a[i], id[i][j - 1]);
            merge(a[i] + m, id[i + (1 << j - 1)][j - 1]);
        }
    }
    REP(i, 1, n) if ( s[i] == '1' ) t[find(id[i][0])] = '1';
    REP(i, 1, n) if ( t[find(id[i][0])] == '1' ) printf("1"); else printf("0");
    puts("");
    return 0;
}
