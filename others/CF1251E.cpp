/***************************************************************
	File name: CF1251E.cpp
	Author: ljfcnyali
	Create time: 2019年10月25日 星期五 21时43分12秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define int long long
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 3e5 + 10;

int T, n, ans, ret, sum, num;
multiset<int> Set;
vector<int> p[maxn];

inline void read(int &x)
{
    char c = getchar(); x = 0;
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    read(T);
    while ( T -- ) 
    {
        read(n); 
        ans = num = 0; sum = n;
        REP(i, 0, n) p[i].clear(); Set.clear();
        REP(i, 1, n) { int x, y; read(x); read(y); p[x].push_back(y); }
        for ( int i = n - 1; i >= 0; -- i ) 
        {
            sum -= p[i].size();
            ret = i - sum;
            for ( auto it : p[i] ) Set.insert(it);
            while ( num < ret ) 
            {
                ans += *Set.begin(); Set.erase(Set.begin());
                ++ num; 
            }
        }
        cout << ans << endl;
    }
    return 0;
}
