/***************************************************************
	File name: LibreOJ_3342.cpp
	Author: ljfcnyali
	Create time: 2021年01月09日 星期六 09时51分21秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 1e9;

int T, n, m, k;
bool flag;
struct node 
{ 
    int a, b, x, y; 
    node ( int f1 = 0, int f2 = 0, int f3 = 0, int f4 = 0 ) { a = f1; x = f2; b = f3; y = f4; } 
} ;
vector<node> ans;
bitset<5010 * 1000> Set[510];
vector<pii> A, B;

inline void Solve(int n, int m, int k, vector<pii> a)
{
    if ( n == 1 ) { ans.push_back(node(a.back().second, a.back().first)); return ; } 
    sort(a.begin(), a.end());
    if ( m < n - 1 ) 
    {
        int Delta = n * k; Set[0].reset(); Set[0][Delta] = 1;
        REP(i, 0, n - 1) 
            if ( a[i].first - k >= 0 ) Set[i + 1] = Set[i] | (Set[i] << a[i].first - k);
            else Set[i + 1] = Set[i] | (Set[i] >> k - a[i].first);
        if ( !Set[n][Delta - k] ) { flag = true; return ; } 
        int now = Delta - k; A.clear(); B.clear();
        for ( int i = n - 1; i >= 0; -- i ) if ( Set[i][now - (a[i].first - k)] )
        {
            A.push_back(a[i]); now -= a[i].first - k;
        }
        else B.push_back(a[i]);
        Solve(A.size(), A.size() - 1, k, A);
        Solve(B.size(), B.size() - 1, k, B);
        return ;
    }
    if ( m == n - 1 ) 
    {
        multiset<pii> Set; for ( auto it : a ) Set.insert(it);
        while ( !Set.empty() )
        {
            pii x = *Set.begin(); Set.erase(Set.find(x));
            if ( x.first < k )
            {
                pii y = *(-- Set.end());
                if ( y.first + x.first < k ) { flag = true; return ; } 
                Set.erase(Set.find(y));
                ans.push_back(node(x.second, x.first, y.second, k - x.first));
                if ( y.first > k - x.first ) Set.insert(pii(y.first - k + x.first, y.second));
            }
            else 
            {
                ans.push_back(node(x.second, k));
                if ( x.first > k ) Set.insert(pii(x.first - k, x.second));
            }
        }
        return ; 
    }
    while ( m >= n ) 
    {
        ans.push_back(node(a.back().second, k));
        a[a.size() - 1].first -= k; -- m; 
        sort(a.begin(), a.end()); 
    }
    Solve(n, m, k, a);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &T);
    while ( T -- )
    {
        scanf("%d%d%d", &n, &m, &k);
        vector<pii> a; REP(i, 1, n) { int x; scanf("%d", &x); a.push_back(pii(x, i)); }
        flag = false; ans.clear(); Solve(n, m, k, a);
        if ( flag ) puts("-1");
        else for ( auto it : ans ) 
        {
            if ( it.b ) printf("%d %d %d %d\n", it.a, it.x, it.b, it.y);
            else printf("%d %d\n", it.a, it.x);
        }
    }
    return 0;
}
