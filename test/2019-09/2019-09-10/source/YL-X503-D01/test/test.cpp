#include<bits/stdc++.h>
using namespace std;
double f[1024][105][105];
double x[15],y[15],c[500005];
double a[105],z[105];
double sx[1024];
int s[105];
const double eps=1e-15;
double qmax(double a,double b){return a-b>eps?a:b;}
double sqr(double a){return a*a;}
int main(){
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;++i){
		scanf("%lf",x+i);
		x[i]=1+x[i]/100;
	}
	for(int i=1;i<=m;++i)scanf("%lf",y+i);
	for(int i=1;i<k;++i){
		scanf("%lf",c+i);
		c[i]=1-c[i]/100;
	}
	if(n==0){
		double a,z,_y,ans=0;
		int s;
		int lsx=0;
		for(int i=1;i<=k;++i){
			scanf("%lf%d%lf",&a,&s,&z);
			_y=y[s];
			if(lsx)_y=_y*c[i-lsx];
			double w=1-sqr(qmax(1-_y/z,0));
			if(w<0.64-eps)lsx=i;
			ans+=w*a;
		}
		printf("%.2lf\n",ans);
	}
	else{
		for(int i=0;i<1<<n;++i){
			sx[i]=1;
			for(int j=0;j<n;++j)if(i&(1<<j))sx[i]*=x[j+1];
		}
		for(int i=1;i<=k;++i){
			scanf("%lf%d%lf",a+i,s+i,z+i);
		}
		int S=(1<<n)-1;
		double _y;
		int lsx;
		for(int i=0;i<S;++i)for(int j=0;j<=k;++j)for(int k=0;k<=j;++k)f[i][j][k]=-1e9;
		f[0][0][0]=0;
		for(int i=0;i<k;++i)for(int j=0;j<=i;++j)for(int w=0;w<1<<n;++w){
			if(f[w][i][j]>=0)
			for(int it=S^w;;it=(it-1)&(S^w)){
				_y=y[s[i+1]]*sx[it];
				if(j)_y=_y*c[i+1-j];	
				double xw=1-sqr(qmax(1-_y/z[i+1],0));
				lsx=j;
				if(xw<0.64-eps)lsx=i+1;
				f[w|it][i+1][lsx]=qmax(f[w|it][i+1][lsx],f[w][i][j]+xw*a[i+1]);
				if(it==0)break;
			}
		}
		double mx=0;
		for(int i=0;i<=k;++i)mx=mx-f[S][k][i]>eps?mx:f[S][k][i];
		printf("%.2lf\n",mx);
	}
	return 0;
}
