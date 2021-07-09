/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2020年11月19日 星期四 19时28分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int T, n, a[maxn], f[maxn], size[maxn];
multiset<int> Set;

inline int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &T);    
    while ( T -- ) 
    {
        scanf("%d", &n);
        REP(i, 1, n) { int x; scanf("%d", &x); a[x] = i; } 
        Set.clear();
        REP(i, 1, n) { f[i] = i; size[i] = 1; Set.insert(1); }
        f[n + 1] = n + 1;

        REP(i, 1, n)
        {
            if ( size[a[i]] != *(-- Set.end()) ) { puts("No"); goto Next ; }
            Set.erase(Set.find(size[a[i]]));
            int x = find(a[i] + 1);
            if ( x != n + 1 ) Set.erase(Set.find(size[x]));
            f[a[i]] = x; size[x] += size[a[i]];
            if ( x != n + 1 ) Set.insert(size[x]);
        }
        puts("Yes");
Next : ;
    }
    return 0;
}
