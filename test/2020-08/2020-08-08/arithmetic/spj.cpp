#include<bits/stdc++.h>
using namespace std;
char s[50000],s1[10000];
int st[39900],len,top;
stack<char>sta;
map<int,int>vis;
int n,fk[105023];
int main()
{
	freopen("arithmetic.in","r",stdin);
	freopen("arithmetic.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		cin>>fk[i];
		vis[fk[i]]++;
	}
	while(~scanf("%s",s)){
		while(!sta.empty())sta.pop();
		for(int i=1;i<=n;++i)vis[fk[i]]=0;
		for(int i=1;i<=n;++i)vis[fk[i]]++;
		int n=strlen(s);
		for(int i=0;i<n;++i)cerr<<s[i];
		cerr<<endl;
		len=0;
		for(register int i=0;i<n;i++)
		{
			if((s[i]<'0' || s[i]>'9') && s[i]!='+' && s[i]!='-' && s[i]!='*' && s[i]!='/' && s[i]!='^' && s[i]!='(' && s[i]!=')')
				continue;
			if(s[i]=='(')
			{
				sta.push(s[i]);
				continue;
			}
			if(s[i]>='0' && s[i]<='9')
			{
				while(s[i]>='0' && s[i]<='9')
					s1[len++]=s[i++];
				i--;
				s1[len++]=' ';
			}
			if(s[i]=='+' || s[i]=='-')
			{
				while(!sta.empty() && sta.top()!='(')
				{
					s1[len++]=sta.top();
					sta.pop();
				}
				sta.push(s[i]);
				continue;
			}
			if(s[i]=='*' || s[i]=='/')
			{
				while(!sta.empty() && (sta.top()=='*' || sta.top()=='/' || sta.top()=='^'))
				{
					s1[len++]=sta.top();
					sta.pop();
				}
				sta.push(s[i]);
				continue;
			}
			if(s[i]=='^')
			{
				sta.push(s[i]);
				continue;
			}
			if(s[i]==')')
			{
				while(sta.top()!='(')
				{
					s1[len++]=sta.top();
					sta.pop();
				}
				sta.pop();
			}
		}
		while(!sta.empty())
		{
			if(sta.top()!='(')
				s1[len++]=sta.top();
			sta.pop();
		}
		top=0;
		for(register int i=0,tmp,m;i<len;i++)
			switch(s1[i])
			{
				case ' ':
					break;
				case '+':
					st[top-1]=st[top-1]+st[top];
					top--;
					if(!top)
					{
						st[1]=st[0];
						top=1;
					}
					break;
				case '-':
					st[top-1]=st[top-1]-st[top];
					top--;
					if(!top)
					{
						st[1]=st[0];
						top=1;
					}
					break;
				case '*':
					st[top-1]=st[top-1]*st[top];
					top--;
					if(!top)
					{
						st[1]=st[0];
						top=1;
					}
					break;
				default:
					m=0;
					while(s1[i]>='0' && s1[i]<='9')
						m=(m<<3)+(m<<1)+s1[i++]-48;
					st[++top]=m;
					vis[m]--;
					if(vis[m]<0){puts("ERROR!");return 0;}
					i--;
			}
		printf("%d\n",st[1]);
	}
	return 0;
}

