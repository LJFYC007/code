/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2020年10月11日 星期日 17时23分38秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int T, n;
char s[maxn];
multiset<pii> Set1;
multiset<int> Set2;

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
        scanf("%s", s + 1);
        Set1.clear();             
        Set2.clear();
        for ( int l = 1, r; l <= n; l = r + 1 )
        {
            r = l;
            while ( s[r + 1] == s[l] && r < n ) ++ r;
            if ( l != r ) Set1.insert(pii(l, r - l + 1));
            else Set2.insert(l);
        }
        int ans = 0;
        while ( !Set1.empty() || !Set2.empty() ) 
        {
            if ( !Set1.empty() ) 
            {
                auto it = Set1.begin();
                int pos = it -> first, len = it -> second;
                Set1.erase(it);
                -- len;
                if ( len == 1 ) Set2.insert(pos);
                else Set1.insert(pii(pos, len));
            }
            else Set2.erase(-- Set2.end());
            int pos1 = n + 1, pos2 = n + 1;
            if ( !Set1.empty() ) pos1 = (*Set1.begin()).first;
            if ( !Set2.empty() ) pos2 = *Set2.begin();
            if ( min(pos1, pos2) <= n ) 
            {
                if ( pos1 < pos2 ) Set1.erase(Set1.begin());
                else Set2.erase(Set2.begin());
            }
            ++ ans;
        }
        printf("%d\n", ans);
    }
    return 0;
}
