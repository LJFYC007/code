/*
Problem:	H.cpp
Time:		2020-10-16 18:40
Author:		CraZYali
E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <unordered_set>
#include <set>
#include <vector>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10;

	template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, q;

char s[40];
const int maxN = 3.0e6 + 10;
#include <map>
struct Trie
{
	map <char, int> ch[maxN];
	int cur;
	int dl[maxN], dfs_clock;
	Trie()
	{
		cur = 1;
		dfs_clock = 0;
	}
	int ins(char s[], int n)
	{
		int p = 1;
		REP(j, 1, n)
		{
			int c = s[j] - 'a';
			if (!ch[p][c]) ch[p][c] = ++cur;
			p = ch[p][c];
		}
		return p;
	}
	int siz[maxN];
	void dfs(int p)
	{
		siz[p] = 1;
		dl[p] = ++dfs_clock;
		REP(i, 0, 25) if(ch[p].find(i)!=ch[p].end())
			{
				int y = ch[p][i];
					dfs(y);
					siz[p] += siz[y];
			}
	}
	void build()
	{
		dfs(1);
	}
}t1, t2;

int x[maxn], y[maxn];

namespace fen{
	int s[maxN];
	void add(int x)
	{
		while (x <= t2.cur)
		{
			s[x]++;
			x += x & -x;
		}
	}
	int sum(int x)
	{
		int y = 0;
		while  (x>0)
		{
			y+=s[x];
			x&=(x-1);
		}
		return y;
	}
}

int ans[maxn << 1];
struct Query
{
	int x,l,r,id;
}qry[maxn<<1];
map<int, int> Map;
inline bool cmp(Query A,Query B){return A.x<B.x;}
int main()
{
	file("H");
	n = read<int>();
#define i64 long long
	const unsigned i64 base = 1e9 + 7;
	REP(i, 1, n)
	{
		scanf("%s", s + 1);
		int m = strlen(s + 1);
		unsigned i64 H=0;
		REP(j, 1, m)
		{H=H*base+s[j];
		}
        ++ Map[H];
		x[i] = t1.ins(s, m);
		reverse(s + 1, s + 1 + m);
		y[i] = t2.ins(s, m);
	}
	t1.build();t2.build();
	static int id[maxn];
	REP(i, 1, n) id[i] = i;
	sort(id + 1, id + 1 + n, [&](int i, int j) {return t1.dl[x[i]] < t1.dl[x[j]];});
	int j = 1;
	int q = read<int>();
	int Q= 0;
	REP(i, 1, q)
	{
		scanf("%s", s + 1);
		int m = strlen(s + 1);
        int pos = 0; 
        REP(i, 1, m) if ( s[i] == '*' ) pos = i;
        REP(len, 1, min(pos - 1, m - pos))
        {
            unsigned i64 H=0;
            REP(j, 1, len) if ( s[pos - len + j - 1] != s[pos + j] ) goto Next ;
            REP(j, 1, m) 
            {
                if ( pos <= j && j <= pos + len ) continue ;
                H = H * base + s[j];
            }
            ans[i] -= Map[H];
Next : ;
        }


		int p1 = 1, p2 = 1;
		REP(i, 1, m)
			if (s[i] == '*') break;
			else
			{
				if(t1.ch[p1].find(s[i]-'a')!=t1.ch[p1].end())
				p1 = t1.ch[p1][s[i] - 'a'];//ch[p1][s[i] - 'a'];
				else {p1=0;break;}
			}
		DEP(i, m, 1)
			if (s[i] == '*') break;
			else
			{
				if(t2.ch[p2].find(s[i]-'a')!=t2.ch[p2].end())
				p2 = t2.ch[p2][s[i] - 'a'];//ch[p1][s[i] - 'a'];
				else {p2=0;break;}
			}
		if (!p1 || !p2) continue;
		else
		{
			if(t1.dl[p1]>1)qry[++Q] = (Query){t1.dl[p1] - 1, t2.dl[p2], t2.dl[p2]+t2.siz[p2]-1, -i};
			qry[++Q] = (Query){t1.dl[p1]+t1.siz[p1]-1, t2.dl[p2], t2.dl[p2]+t2.siz[p2]-1, i};
		}
	}
	sort(qry+1,qry+1+Q,cmp);
	REP(i,1,Q)
	{
		while(j<=n&&t1.dl[x[id[j]]]<=qry[i].x)
		{
			fen::add(t2.dl[y[id[j]]]);
			j++;
		}
		int sgn=1,id=qry[i].id;
		if(id<0)id=-id,sgn=-sgn;
		ans[id]+=sgn*(fen::sum(qry[i].r)-fen::sum(qry[i].l-1));
	}
	REP(i,1,q)printf("%d\n",max(0, ans[i]));
	return 0;
}
