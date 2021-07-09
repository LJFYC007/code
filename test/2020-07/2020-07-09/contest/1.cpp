/***************************************************************
	File name: contest.cpp
	Author: ljfcnyali
	Create time: 2020年07月09日 星期四 15时51分04秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const int maxm = 1e6 + 1e5;

int n, m, a[maxn], k, b[maxn];
bool vis[32];
vector<int> p[maxm];
priority_queue<pii, vector<pii>, greater<pii> > Q;

inline int Find(int x, int pos) { return *upper_bound(p[x].begin(), p[x].end(), pos); }

int main()
{
    freopen("contest.in", "r", stdin);
    freopen("contest1.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, n) { scanf("%d", &a[i]); a[i] ^= a[i - 1]; }
    REP(i, 1, n) p[a[i]].push_back(i);       
    REP(i, 0, maxm - 1) { p[i].push_back(n + 1); sort(p[i].begin(), p[i].end()); }
    while ( m -- ) 
    {
        int op; scanf("%d", &op);
        while ( !Q.empty() ) Q.pop(); mem(vis);
        scanf("%d", &k); 
        REP(i, 1, k) 
        {
            scanf("%d", &b[i]);
            int pos = p[b[i]].front();
            printf("%d\n", pos);
            if ( pos != n + 1 ) Q.push(pii(pos, 1 << i - 1));
        }
        bool flag = false;
        while ( !Q.empty() ) 
        {
            pii u = Q.top(); Q.pop();
            if ( a[u.first] == a[n] ) { flag = true; break ; }
            if ( vis[u.second] ) continue ; vis[u.second] = true;
            REP(i, 1, k)
            {
                if ( (u.second >> i - 1) & 1 ) continue ;
                int pos = Find(a[u.first] ^ b[i], u.first);
                printf("%d\n", pos);
                if ( pos != n + 1 ) Q.push(pii(pos, u.second | (1 << i - 1)));
            }
        }
        if ( flag == true ) puts("yes");
        else puts("no");
    }
    return 0;
}
