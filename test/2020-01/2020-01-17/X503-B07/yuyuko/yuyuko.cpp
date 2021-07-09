/***************************************************************
	File name: yuyuko.cpp
	Author: ljfcnyali
	Create time: 2020年01月17日 星期五 14时43分55秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int n, m, k, a[20], f[maxn], r[maxn], g[1000][maxn / 10], tot;
vector<pii> p[maxn];
vector<int> A, B;
bool use[maxn];

inline int Merge1(int x, int y)
{
    if ( y ) 
    {
        if ( !use[x] ) 
        {
            ++ tot; use[x] = true;
            for ( auto i : p[x] ) g[tot][i.first] = i.second;
            x = tot;
        }
        if ( !use[y] ) 
        {
            ++ tot; use[y] = true;
            for ( auto i : p[y] ) g[tot][i.first] = i.second;
            y = tot;
        }
    }
}

inline int Merge(int x, int y)
{
    if ( use[x] || use[y] || !y ) return Merge1(x, y);
    return Merge2(x, y);
}

int main()
{
    freopen("yuyuko.in", "r", stdin);
    freopen("yuyuko.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &k);
    REP(i, 1, k) scanf("%d", &a[i]);
    REP(i, 1, n) REP(j, 1, k) { int x; scanf("%d", &x); p[i].push_back(pii(x, a[j])); }
    REP(i, 1, n) A.push_back(i);
    random_shuffle(p + 1, p + n + 1);
    while ( n ) 
    {
        if ( n & 1 ) { int x = A.back(); A.pop_back(); Merge(x, 0); }
        n >>= 1;
        while ( A.size() ) 
        {
            int x = A.back(); A.pop_back();
            int y = A.back(); A.pop_back();
            B.push_back(Merge(x, y));
        }
        swap(A, B);
    }
    return 0;
}
