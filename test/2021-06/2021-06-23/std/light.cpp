#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstdlib>
using namespace std;
int n,q,k,c[200002],num[200002],fk;
int nc0[200002],nr1[200002],dl[10000],len,t1[200002][102],t2[102][200002];
bool ys[200002];
vector<int>gc[200002],gr[200002];
void add(int x,int y){
	gc[x].push_back(y);gr[y].push_back(x); 
}
int main()
{
	scanf("%d%d%d",&n,&k,&q);
	for (int i=1;i<=n;i++)scanf("%d",&c[i]);
	c[n+1]=k+1;fk=4000;
	for (int i=1;i<=n;i++)
	if (c[i]!=c[i+1])add(c[i],c[i+1]);
	for (int i=1;i<=k+1;i++)
	if (gr[i].size()+gc[i].size()>fk){dl[++len]=i;num[i]=len;}
	
	for (int i=1;i<=k+1;i++)
	for (int j=0;j<gc[i].size();j++)
	if (num[gc[i][j]])t1[i][num[gc[i][j]]]++;
	
	for (int i=1;i<=len;i++)
	for (int j=0;j<gc[dl[i]].size();j++)
	t2[i][gc[dl[i]][j]]++;
	
	for (int i=1;i<=k+1;i++)
	for (int j=1;j<=len;j++)
	if (i!=dl[j])nc0[dl[j]]+=t2[j][i];
	int ans=0;
	for (int i=1;i<=q;i++)
	{
		int x;
		scanf("%d",&x);
		if (gr[x].size()+gc[x].size()<=fk)
		{
			if (ys[x]==0)//0->1
			{
				for (int j=0;j<gr[x].size();j++)if (ys[gr[x][j]])ans--;
				for (int j=0;j<gc[x].size();j++)if (!ys[gc[x][j]])ans++;
				for (int j=1;j<=len;j++)
				if (x!=dl[j])
				{
					nc0[dl[j]]-=t2[j][x];
					nr1[dl[j]]+=t1[x][j];
				}
			}
			else //1->0
			{
				for (int j=0;j<gr[x].size();j++)if (ys[gr[x][j]])ans++;
				for (int j=0;j<gc[x].size();j++)if (!ys[gc[x][j]])ans--;
				for (int j=1;j<=len;j++)
				if (x!=dl[j])
				{
					nc0[dl[j]]+=t2[j][x];
					nr1[dl[j]]-=t1[x][j];
				}
			}
		}
		else
		{
			if (ys[x]==0)//0->1
			{
				ans-=nr1[x];ans+=nc0[x];
				for (int j=1;j<=len;j++)
				if (x!=dl[j])
				{
					nc0[dl[j]]-=t2[j][x];
					nr1[dl[j]]+=t1[x][j];
				}
			}
			else //1->0
			{
				ans+=nr1[x];ans-=nc0[x];
				for (int j=1;j<=len;j++)
				if (x!=dl[j])
				{
					nc0[dl[j]]+=t2[j][x];
					nr1[dl[j]]-=t1[x][j];
				}
			}
		}
		printf("%d\n",ans);ys[x]^=1;
	}
	return 0;
}
