/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年10月16日 星期五 19时12分47秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int INF = 0x3f3f3f3f;

int n, m, id[31], f[1 << 16], g[31], h[31], a[31], s[31], b[31], dfn[31];
vector<int> p[31];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    while ( ~scanf("%d", &n) ) 
    {
        REP(i, 1, n) p[i].clear();
        REP(i, 1, n) { scanf("%d", &a[i]); p[a[i]].push_back(i); }
        REP(i, 1, n) b[i] = 1;
        REP(i, 1, n) 
        {
            if ( p[i].size() == 1 ) ++ b[p[i][0]];
            if ( p[i].size() > 1 ) { id[++ m] = i; dfn[i] = m; }
            else dfn[i] = 0;
        }
        REP(i, 0, (1 << m) - 1) f[i] = INF; f[0] = 0;
        REP(i, 0, (1 << m) - 1)
        {
            int pos = 1;
            REP(j, 1, m) if ( (i >> j - 1) & 1 ) pos += p[id[j]].size();
            REP(j, 1, n) 
                if ( dfn[a[j]] && ((i >> dfn[a[j]] - 1) & 1) ) b[j] = b[j - 1];
                else b[j] = b[j - 1] + 1;
            if ( i == 0 ) 
            {
                REP(j, 1, n) printf("%d ", b[j]); puts("");
            }
            REP(j, 1, m) 
            {
                if ( (i >> j - 1) & 1 ) continue ;
                int sum = 0;
                for ( auto k : p[id[j]] ) printf("%d ", k); puts("");
                for ( int k = 0; k < p[id[j]].size(); ++ k ) sum += abs(b[p[id[j]][k]] - b[pos + k]);
                if ( i == 0 && j == 2 ) cerr << id[j] << " " << sum << endl;
                f[i | (1 << j - 1)] = min(f[i | (1 << j - 1)], f[i] + sum);
            }
        }
        cout << f[2] << endl;
        printf("%d\n", f[(1 << m) - 1]);
    }
    return 0;
}
