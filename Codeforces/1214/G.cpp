/***************************************************************
	File name: G.cpp
	Author: ljfcnyali
	Create time: 2020年10月10日 星期六 09时42分49秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2010;

int n, m, q, pd[maxn];
bitset<2010> a[maxn], b, c;
multiset<pii> Set;
multiset<int> ans;

inline bitset<2010> Get(int x, int l, int r)
{
    if ( l > r ) return c;
    return (a[x] >> l - 1) & (b << r - l + 1).flip();
}

inline void Maintain(int pre, int it)
{
    if ( pd[it] == -1 ) ans.erase(it);
    if ( (a[pre] | a[it]) == a[it] ) pd[it] = pre;
    else { pd[it] = -1; ans.insert(it); }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &q);
    REP(i, 1, n) { a[i].reset(); Set.insert(pii(0, i)); }
    pd[1] = 0; REP(i, 2, n) pd[i] = i - 1; 
    b.set();
    REP(i, 1, q)
    {
        c.reset();
        int x, l, r; scanf("%d%d%d", &x, &l, &r);
        auto it = Set.lower_bound(pii(a[x].count(), x));
        if ( pd[x] == -1 ) ans.erase(x);
        if ( it != -- Set.end() ) 
        { 
            auto nxt = it; ++ nxt; Set.erase(it); 
            if ( nxt != Set.begin() )
            {
                it = nxt; -- it;
                Maintain(it -> second, nxt -> second); 
            }
            else 
            { 
                int t = nxt -> second;
                if ( pd[t] == -1 ) { ans.erase(t); pd[t] = 0; }
            }
        }
        else Set.erase(it);
        a[x] = Get(x, 1, l - 1) | ((Get(x, l, r) | (b << r - l + 1)).flip() << l - 1) | (Get(x, r + 1, m) << r);
        Set.insert(pii(a[x].count(), x)); 
        it = Set.lower_bound(pii(a[x].count(), x));
        if ( it != Set.begin() ) { auto pre = it; -- pre; Maintain(pre -> second, it -> second); }
        if ( it != -- Set.end() ) { auto nxt = it; ++ nxt; Maintain(it -> second, nxt -> second ); }
        // printf("%d\n", q);
        // for ( auto it : ans ) printf("%d %d\n", it.first, it.second);
        // puts("");
        if ( !ans.size() ) puts("-1");
        else 
        {
            // for ( auto it : Set ) printf("%d %d\n", it.first, it.second);
            int x = *ans.begin(), y = (*(-- Set.lower_bound(pii(a[x].count(), x)))).second;
            // cout << x << " " << y << endl;
            // cout << a[x] << " " << a[y] << endl;
            c = a[x] ^ a[y];
            int pos1 = c._Find_first();
            if ( a[x][pos1] == 0 ) c = a[x] & c; else c = a[y] & c;
            int pos2 = c._Find_next(pos1);
            printf("%d %d %d %d\n", min(x, y), pos1 + 1, max(x, y), pos2 + 1);
        }
    }
    return 0;
}
