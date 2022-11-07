/***************************************************************
	File name: d.cpp
	Author: ljfcnyali
	Create time: 2019年11月10日 星期日 20时44分16秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int n, m, p[maxn], d[maxn];
vector<int> a[maxn];

int main()
{
    scanf("%d%d", &n, &m);
    REP(i, 1, n) { scanf("%d", &p[i]); d[p[i]] = i; }
    REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); a[u].push_back(v); }
    for ( int j = n - 1; j >= 1; -- j ) 
    {
        int x = p[j];
        sort(a[x].begin(), a[x].end(), [](int a, int b) { return d[a] < d[b]; });
        for ( auto i : a[x] ) if ( d[i] == d[x] + 1 ) { ++ d[x]; -- d[i]; }
    }
    printf("%d\n", n - d[p[n]]);
    return 0;
}
