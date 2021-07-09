#include<bits/stdc++.h>
#define M 3005
using namespace std;
const int oo=1e9;
inline void Rd(int &x){
	char c;x=0;
	while((c=getchar())<48);
	do x=(x<<3)+(x<<1)+(c^48);
	while((c=getchar())>47);
}
int n,m;
struct node{
	int l,r,w;
	bool operator <(const node &_)const{
		return r<_.r;
	}
}A[M];
int dp[M][M];
void Min(int &x,int y){
	if(y<x)x=y;
}
int main(){
	freopen("intervals.in","r",stdin);
	freopen("intervals.out","w",stdout);
	for(int _=(Rd(_),_);_;_--){
		Rd(n),Rd(m);
		for(int i=1;i<=n;i++)Rd(A[i].l),Rd(A[i].r),Rd(A[i].w);
		sort(A+1,A+n+1);
		for(int i=1;i<=n;i++)
			for(int j=0;j<=m;j++)dp[i][j]=oo;
		for(int i=1;i<=n;i++)
			if(A[i].l==1)
				for(int j=1;j<=A[i].r;j++)dp[i][j]=A[i].w;
		int ans=oo;
		for(int i=2;i<=n;i++){
			for(int j=1;j<i;j++)
				if(A[j].r+1==A[i].l)
					Min(dp[i][A[i].l],max(dp[j][A[j].r],A[i].w));
				else if(A[j].r>=A[i].l&&A[j].r+1<=A[i].r)
					Min(dp[i][A[j].r+1],max(dp[j][A[i].l],A[i].w+A[j].w));
			for(int j=1;j<=A[i].r;j++)Min(dp[i][j],dp[i][j-1]);
			if(A[i].r==m)Min(ans,dp[i][m]);
		}
		if(ans>=oo)ans=-1;
		printf("%d\n",ans);
	}
	return 0;
}
