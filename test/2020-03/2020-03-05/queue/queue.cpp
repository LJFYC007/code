#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e6 + 10;
const int Mod = 1e9 + 7;

int n, l, r, tot = 1, last = 1, ans;
struct node { int fa, len, Next[26]; } Tree[maxn];
char s[maxn], t[10];

inline int NewNode()
{
	++ tot; Tree[tot].fa = Tree[tot].len = 0;
	REP(i, 0, 25) Tree[tot].Next[i] = 0;
	return tot;
}

inline void Extand(int c)
{
	int cur = NewNode(); Tree[cur].len = Tree[last].len + 1;
	int p = last; last = cur;
	while ( p && !Tree[p].Next[c] ) { Tree[p].Next[c] = cur; p = Tree[p].fa; }
	if ( !p ) Tree[cur].fa = 1;
	else
	{
		int q = Tree[p].Next[c];
		if ( Tree[p].len + 1 == Tree[q].len ) Tree[cur].fa = q;
		else
		{
			int clone = NewNode(); Tree[clone] = Tree[q]; Tree[clone].len = Tree[p].len + 1;
			while ( p && Tree[p].Next[c] == q ) { Tree[p].Next[c] = clone; p = Tree[p].fa; }
			//ans = (ans - Tree[q].len + Tree[Tree[q].fa].len) % Mod;
			Tree[q].fa = Tree[cur].fa = clone;
			//ans = (ans + Tree[q].len - Tree[clone].len) % Mod;
		}
	}
	ans = (ans + Tree[cur].len - Tree[Tree[cur].fa].len) % Mod;
}

signed main()
{
	freopen("queue.in", "r", stdin);
	freopen("queue.out", "w", stdout);
	scanf("%lld", &n);
	l = 1; int ret = 0;
	REP(i, 1, n)
	{
		scanf("%s", t + 1);
		if ( t[1] == '+' )
		{
			++ r; scanf(" %c", &s[r]);
			Extand(s[r] - 'a');
		}
		else
		{
			++ l; last = 1; tot = ans = 0; NewNode();
			REP(i, l, r) Extand(s[i] - 'a');
		}
		ret = (ret + ans) % Mod;
	}
	printf("%lld\n", (ret + Mod) % Mod);
	return 0;
}
