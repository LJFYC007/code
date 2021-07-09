/***************************************************************
	File name: HaHa
	Author: ljfcnyali
	Create time: 2019年11月10日 20时21分30秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 10010;

int n, m;
vector<int> a[maxn], b[maxn];

int main()
{
    scanf("%d%d", &n, &m);
    REP(i, 1, n) REP(j, 1, m) { int x; scanf("%d", &x); a[i + j].push_back(x); }
    REP(i, 1, n) REP(j, 1, m) { int x; scanf("%d", &x); b[i + j].push_back(x); }
    REP(i, 2, n + m) 
    {
        sort(a[i].begin(), a[i].end());
        sort(b[i].begin(), b[i].end());
        if ( a[i] != b[i] ) { puts("NO"); return 0; }
    }
    puts("YES");
    return 0;
}
