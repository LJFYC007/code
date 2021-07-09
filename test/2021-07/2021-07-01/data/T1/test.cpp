#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cctype>
#include<ctime>
using namespace std;
int read()
{
	int x=0,ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return x;
}
struct pt
{
	int x,l,r,id;
	bool operator<(const pt p) const
	{
		return x<p.x;
	}
};
int n,m,len,f[1005][1005],g[15][1005][1005],dp[2005][1005],q[100005][3],head,tail;
int qans[1000005];
vector<pt> val[1005];
char a[15][1005],b[1005];
inline int F(int u,int v,int x,int y)
{
	return g[v][x+1][y]+dp[u][x];
}
/*void solve(int j,int u,int v,int l,int r,int ql,int qr)
{
	if(l>r) return;
//	printf("solve:j=%d,u=%d,v=%d,l=%d,r=%d,ql=%d,qr=%d\n",j,u,v,l,r,ql,qr);
	int mid=(l+r)/2,mx=-1,id=0;
	for(int i=ql;i<=min(qr,mid);i++)
	{
		int q=F(u,v,i,mid);
		if(q>mx)
		{
			mx=q;
			id=i;
		}
	}
	dp[j][mid]=mx;
	if(l==r) return;
	solve(j,u,v,l,mid-1,ql,id);
	solve(j,u,v,mid+1,r,id,qr);
}*/
int main()
{
	//freopen("ex_gcd2.in","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%s",a[i]+1);
	scanf("%s",b+1);
	len=strlen(b+1);
	for(int i=1;i<=n;i++)
	{
		int at=strlen(a[i]+1);
		for(int j=0;j<len;j++)
		{
			for(int k=1;k<=at;k++)
				for(int l=1;l+j<=len;l++)
				{
					f[k][l]=max(f[k-1][l],f[k][l-1]);
					if(a[i][k]==b[l+j]) f[k][l]=max(f[k][l],f[k-1][l-1]+1);
				}
			for(int l=1;l+j<=len;l++)
				g[i][j+1][j+l]=f[at][l];
		}
	//	for(int j=1;j<=len;j++)
	//		for(int l=j;l<=len;l++)
	//			printf("i=%d,j=%d,l=%d,g=%d\n",i,j,l,g[i][j][l]);
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		pt p;
		p.x=read(),p.l=read(),p.r=read();
		p.id=i;
		val[p.l].push_back(p);
	}
	for(int i=1;i<=len;i++)
	{
	//	printf("i=%d\n",i);
		sort(val[i].begin(),val[i].end());
		if(val[i].empty()) continue;
		for(int j=0;j<(1<<n);j++)
			for(int k=0;k<=len;k++)
				dp[j][k]=0;
		int sz=val[i].size(),nw=0;
		for(int j=1;j<(1<<n);j++)
		{
			int u=0,v=0;
			for(int k=1;k<=n;k++)
				if(j&(1<<(k-1)))
				{
					u=j-(1<<(k-1));
					v=k;
				}
		//	solve(j,u,v,i,len,i-1,len);
			head=1,tail=1;
			q[1][0]=i-1;
			q[1][1]=i,q[1][2]=len;
			for(int k=i;k<=len;k++)
			{
				while(head<=tail&&q[head][2]<k) head++;
				q[head][1]=max(q[head][1],k);
				int las=len+1;
				while(head<=tail)
				{
					if(F(u,v,q[tail][0],q[tail][2])>F(u,v,k,q[tail][2])) break;
					if(F(u,v,q[tail][0],q[tail][1])<=F(u,v,k,q[tail][1]))
					{
						las=q[tail][1];
					//	printf("tail=%d,las=%d\n",tail,las);
						tail--;
						continue;
					}
					int l=q[tail][1],r=q[tail][2],mid;
					while(l<=r)
					{
						mid=(l+r)/2;
						if(F(u,v,q[tail][0],mid)<=F(u,v,k,mid)) r=mid-1;
						else l=mid+1;
					}
					las=l;
					break;
				}
				if(las!=len+1)
				{
					//printf("las=%d\n",las);
					q[tail][2]=las-1;
					tail++;
					q[tail][0]=k,q[tail][1]=las,q[tail][2]=len;
				}
				dp[j][k]=F(u,v,q[head][0],k);
				/*printf("i=%d,j=%d,k=%d,u=%d,v=%d,dp=%d,head=%d,tail=%d,q=",i,j,k,u,v,dp[j][k],head,tail);
				for(int l=head;l<=tail;l++)
					printf("(%d,%d,%d) ",q[l][0],q[l][1],q[l][2]);
				printf("\n");
				if(k==i-1&&dp[j][k]) printf("dp=%d,head=%d,tail=%d\n",dp[j][k],head,tail);*/
			}
			while(nw<sz&&val[i][nw].x==j)
			{
				qans[val[i][nw].id]=dp[j][val[i][nw].r];
			//	printf("j=%d,val=%d,dp=%d\n",j,val[i][nw].r,dp[j][val[i][nw].r]);
				nw++;
			}
		}
	}
	fprintf(stderr, "%ld\n", clock());
//	for(int i=1;i<=m;i++)
//		printf("%d\n",qans[i]);
	return 0;
}
