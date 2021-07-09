#include<bits/stdc++.h>

using namespace std;

int read()
{
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = 0; c = getchar(); }
	while(isdigit(c)) { x = (x << 3) + (x << 1) + (c ^ 48); c = getchar(); }
	return f ? x : -x;
}

int lazy[8000005], rev[8000005];

void paint(int o, int dep, int mask)
{
	lazy[o] ^= mask;
	if(mask & (1 << dep)) rev[o] ^= 1;
}	

void pushdown(int o, int dep)
{
	if(!lazy[o]) return ;
	paint(o << 1, dep + 1, lazy[o]);
	paint(o << 1 | 1, dep + 1, lazy[o]);
	lazy[o] = 0;
}

void upt(int o, int dep, int l, int r, int x, int y, int d)
{
	if(x <= l && r <= y)
	{
		paint(o, dep, 1 << d);
		return ;
	}
	pushdown(o, dep);
	int mid = (l + r) >> 1;
	if(!rev[o])
	{
		if(x <= mid) upt(o << 1, dep + 1, l, mid, x, y, d);
		if(y > mid) upt(o << 1 | 1, dep + 1, mid + 1, r, x, y, d);
	}
	else 
	{
		if(x <= mid) upt(o << 1 | 1, dep + 1, mid + 1, r, x - l + mid + 1, y - l + mid + 1, d);
		if(y > mid) upt(o << 1, dep + 1, l, mid, x - mid - 1 + l, y - mid - 1 + l, d);
	}
}

int que(int o, int dep, int l, int r, int pos)
{
	if(l == r) return l;
	pushdown(o, dep);
	int mid = (l + r) >> 1;
	if(!rev[o])
	{
		if(pos <= mid) return que(o << 1, dep + 1, l, mid, pos);
		else return que(o << 1 | 1, dep + 1, mid + 1, r, pos);
	}
	else 
	{
		if(pos <= mid) return que(o << 1 | 1, dep + 1, mid + 1, r, pos - l + mid + 1);
		else return que(o << 1, dep + 1, l, mid, pos + l - mid - 1);
	}
}

int main()
{
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	int n = read(), q = read(); 
	while(q--)
	{
		int opt = read();
		if(opt == 1)
		{
			int l = read(), r = read();
			for(int i = 0; i < n; ++i)
			{
				int x = max(l, (1 << i)) - (1 << i), y = min((1 << i + 1) - 1, r) - (1 << i);
				if(x <= y)
					upt(1, 0, 0, (1 << i) - 1, x, y, i);
			}
		}
		else 
		{
			int x = read();
			printf("%d\n", que(1, 0, 0, (1 << n) - 1, --x) + 1);
		}
	}
	return 0;
}
