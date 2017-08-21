#ifdef ONLINE_JUDGE
#include <bits/stdc++.h>
using namespace std;
#else
#include "header.h"
#include "debug.h"
#endif
#define SS(n) scanf("%s",n)
#define pn puts("");
#define ps putchar(' ')
#define sz(s) int((s).size())
#define rep(i,a,b) for(int(i)=a;(i)<=(b);++(i))
#define per(i,b,a) for(int(i)=b;(i)>=(a);--(i))
#define clr(a) memset(a,0,sizeof(a))
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
inline int inp() {int n=0,s=1;char p=getchar_unlocked();if(p=='-')s=-1;while((p<'0'||p>'9')&&p!=EOF&&p!='-')p=getchar_unlocked();if(p=='-')s=-1,p=getchar_unlocked();while(p>='0'&&p<='9')n=(n<<3)+(n<<1)+(p-'0'),p=getchar_unlocked();return n*s;} void out(int x){if(x<0)putchar_unlocked('-'),x=-x;int ll=0,dd[10];while(x)dd[ll++]=x%10,x/=10;if(!ll)dd[ll++]=0;while(ll--)putchar_unlocked(dd[ll]+48);}
inline char _inp(){register char c; c = getchar_unlocked(); while (c<33) c = getchar_unlocked();return c;}
const int N = 2e4 + 2;
const int inf = INT_MAX;

int par[N];
int siz[N];
bool mark[N];
int edge[N][3];

inline int getPar(int x) {
	if(par[x] != x) par[x] = getPar(par[x]);
	return par[x];
}

inline void unite(int x, int y) {
	if(siz[x] >= siz[y]) par[y] = x, siz[x] += siz[y];
	else par[x] = y, siz[y] += siz[x];
}

int main()
{
	#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	#endif
	int testCase, t=inp();
	for(testCase=1; testCase<=t; ++testCase)
	{
		int n = inp();
		for(int i=1; i<=n; ++i) siz[i] = 1, par[i] = i, mark[i] = 0;
		for(int i=1; i<n; ++i) {
			int u = inp(), v = inp();
			edge[i][1] = u, edge[i][2] = v;
		}
		int Quora = inp();
		vector <int> quo;
		for(int qq = 1; qq <= Quora; ++qq) {
			char ch = _inp();
			if(ch == 'R') {
				int remv = inp();
				mark[remv] = 1;
				quo.pb(remv);
			}
			else quo.pb(-1);
		}
		int cnt = n*(n-1)/2;
		for(int i=1; i<=n-1; ++i) {
			if(!mark[i]) {
				int u = edge[i][1], v = edge[i][2];
				int x = getPar(u), y = getPar(v);
				cnt -= siz[x]*siz[y];
				unite(x,y);
			}
		}
		vector <int> ans;
		while(!quo.empty()) {
			if(quo.back() == -1) {
				ans.pb(cnt);
			} else {
				int eno = quo.back();
				int u = edge[eno][1], v = edge[eno][2];
				int x = getPar(u), y = getPar(v);
				cnt -= siz[x]*siz[y];
				unite(x,y);
			}
			quo.pop_back();
		}
		while(!ans.empty()) {
			out(ans.back());
			putchar_unlocked('\n');
			ans.pop_back();
		}
		putchar_unlocked('\n');
	}
}
				
		

