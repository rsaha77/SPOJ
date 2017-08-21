#include <map>
#include <set>
#include <list>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <cstdio>
#include <vector>
#include <string>
#include <bitset>
#include <numeric>
#include <utility>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;


inline int inp() {int n=0,s=1;char p=getchar_unlocked();if(p=='-')s=-1;while((p<'0'||p>'9')&&p!=EOF&&p!='-')p=getchar_unlocked();if(p=='-')s=-1,p=getchar_unlocked();while(p>='0'&&p<='9')n=(n<<3)+(n<<1)+(p-'0'),p=getchar_unlocked();return n*s;}
inline void out(int x){if(x<0)putchar_unlocked('-'),x=-x;int ll=0,dd[10];while(x)dd[ll++]=x%10,x/=10;if(!ll)dd[ll++]=0;while(ll--)putchar_unlocked(dd[ll]+48);}


struct arrangeQ {
  int idx, beg, end;
};

bool comp1(const arrangeQ & a, const arrangeQ & b) {
  return a.beg < b.beg;
}

arrangeQ qq[200010];
int arr[30010];
bool flag[30010];  // To mark the first instance of the number present at the index i
int marked[1000010]; // Helper to mark the first instance
list <int> pos[1000010];
int seg[(30010<<2)];
int ans[200010];

void build(int b, int e, int curr) {
  if(b == e) {
    seg[curr] = flag[b];
    return;
  }
  int m = (b+e)>>1;
  int ll = curr<<1;
  int rr = ll+1;
  build(b,m,ll) , build(m+1,e,rr);
  seg[curr] = seg[ll] + seg[rr];
}

void refresh(int b, int e, int curr, int pos) {
  if(pos < b || pos > e) return;
  if(b == e && b == pos) {
    ++seg[curr];
    return;
  }
  ++seg[curr];
  int m = (b+e)>>1;
  int ll = curr<<1;
  int rr = ll+1;
  refresh(b,m,ll,pos) , refresh(m+1,e,rr,pos);
}

int query(int b, int e, int qb, int qe, int curr) {
  if(qe < b || qb > e) return 0;
  if(b >= qb && e <= qe) return seg[curr];
  int m = (b+e)>>1;
  int ll = curr<<1;
  int rr = ll+1;
  return query(b,m,qb,qe,ll) + query(m+1,e,qb,qe,rr);
}

int main() {
  #ifndef ONLINE_JUDGE
  freopen("in.txt","r",stdin);
  #endif
  int n = inp();
  for(int i=1; i<=n; ++i) {
    arr[i] = inp();
    if(!marked[arr[i]]) {
      flag[i] = 1;
      marked[arr[i]] = true;
    }
    pos[arr[i]].push_back(i);
  }
  int Quora = inp();
  for(int i=1; i<=Quora; ++i) {
    qq[i].idx = i;
    qq[i].beg = inp();
    qq[i].end = inp();
  }
  sort(qq+1, qq+1+Quora, comp1);
  build(1,n,1);
  int now = 1;
  for(int i=1; i<=Quora; ++i) {
    while(now < qq[i].beg) {
      pos[arr[now]].pop_front();
      if(!pos[arr[now]].empty()) {
        refresh(1,n,1,pos[arr[now]].front());
      }
      ++now;
    }
    ans[qq[i].idx] = query(1,n,qq[i].beg,qq[i].end,1);
  }
  for(int i=1; i<=Quora; ++i) {
    out(ans[i]);
    puts("");
  }
}
