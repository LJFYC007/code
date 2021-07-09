/***************************************************************
	File name: check.cpp
	Author: ljfcnyali
	Create time: 2020年07月10日 星期五 20时34分25秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, q, a[maxn];
pii Q[maxn];
set<int> Set[maxn];

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    scanf("%d%d", &n, &q);
    REP(i, 1, n) { int x; scanf("%d", &x); Set[i].insert(x); }
    REP(i, 1, q) scanf("%d%d", &Q[i].first, &Q[i].second);
    freopen("output.txt", "r", stdin);
    int cnt; scanf("%d", &cnt);
    REP(i, n + 1, cnt)
    {
        int x, y; scanf("%d%d", &x, &y);
        for ( auto it : Set[x] ) Set[i].insert(it);
        for ( auto it : Set[y] ) Set[i].insert(it);
    }
    for ( auto i : Set[8191] ) printf("%d ", i); puts("");
    printf("%d\n", Set[8191].size());
    return 0;
}
