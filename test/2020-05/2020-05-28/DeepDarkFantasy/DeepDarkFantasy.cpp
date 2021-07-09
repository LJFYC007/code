/***************************************************************
	File name: DeepDarkFantasy.cpp
	Author: ljfcnyali
	Create time: 2020年05月28日 星期四 14时11分29秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int n, a[maxn], b[maxn], id[maxn], vis[maxn];
vector<int> p, q, f[maxn];
vector<pii> A, B;

int main()
{
    freopen("DeepDarkFantasy.in", "r", stdin);
    freopen("DeepDarkFantasy.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) { scanf("%d", &a[i]); id[a[i]] = i; }
    REP(i, 1, n)
    {
        if ( vis[i] ) continue ;
        p.clear(); q.clear(); p.push_back(a[i]); 
        int x = a[i]; q.push_back(i);
        while ( a[x] != p[0] ) { q.push_back(x); x = a[x]; p.push_back(x); }
        // for ( auto  i : q ) printf("%d ", i); puts("");
        // for ( auto  i : p ) printf("%d ", i); puts("");
        for ( auto i : p ) vis[i] = p.size();
        if ( p.size() % 2 == 0 ) f[p.size()].push_back(i);
        else 
        {
            int num = q.size() / 2;
            // if ( p.size() == 1 ) { b[q[0]] = p[0]; continue ; } 
            for ( int i = 0; i < p.size(); ++ i ) 
            {
                b[q[i]] = p[(i + num) % p.size()];
                continue ;
                if ( i == p.size() - 2 ) b[q[i]] = p[0];
                else if ( i == p.size() - 1 ) b[q[i]] = p[1];
                else b[q[i]] = p[i + 2];
            }
                // b[q[i + 1 == p.size() ? 0 : i + 1]] = p[i];
        }
    }
    REP(i, 2, n)
    {
        if ( !f[i].size() ) continue ;
        if ( f[i].size() & 1 ) { puts("-1"); return 0; }
        while ( f[i].size() ) 
        {
            int x = f[i].back(); f[i].pop_back();
            int y = f[i].back(); f[i].pop_back();
            A.clear(); B.clear();

            int t = a[x]; A.push_back(pii(t, x)); 
            while ( a[t] != a[x] ) { A.push_back(pii(a[t], t)); t = a[t]; }
            t = a[y]; B.push_back(pii(t, y));
            while ( a[t] != a[y] ) { B.push_back(pii(a[t], t)); t = a[t]; } 

            /*
            for ( auto i : A ) printf("%d ", i.first); puts("");
            for ( auto i : A ) printf("%d ", i.second); puts("");
            for ( auto i : B ) printf("%d ", i.first); puts("");
            for ( auto i : B ) printf("%d ", i.second); puts("");
            */

            REP(j, 0, i - 1)
            {
                b[A[j].second] = B[j == 0 ? i - 1 : j - 1].first;
                b[B[j].second] = A[j].first;
            }
        }
    }
    REP(i, 1, n) printf("%d%c", b[i], i < n ? ' ' : '\n'); 
    fflush(stdout);
    // REP(i ,1, n) { assert(b[b[i]] == a[i]); cerr << i << endl; }
    return 0;
}
