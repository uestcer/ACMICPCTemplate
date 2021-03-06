const int MAXEDGE=50000;
const int MAXN=3000;
const int inf=0x3fffffff;
struct edges {
  int cap,to,next,flow;
} edge[MAXEDGE+100];
struct nodes {
  int head,label,pre,cur;
} node[MAXN+100];
int L,N;
int gap[MAXN+100];
void init(int n) {
  L=0;
  N=n;
  for (int i=0; i<N; i++)
    node[i].head=-1;
}
void add_edge(int x,int y,int z,int w) {
  edge[L].cap=z;
  edge[L].flow=0;
  edge[L].to=y;
  edge[L].next=node[x].head;
  node[x].head=L++;
  edge[L].cap=w;
  edge[L].flow=0;
  edge[L].to=x;
  edge[L].next=node[y].head;
  node[y].head=L++;
}
int maxflow(int s,int t) {
  memset(gap,0,sizeof(gap));
  gap[0]=N;
  int u,ans=0;
  for (int i=0; i<N; i++) {
    node[i].cur=node[i].head;
    node[i].label=0;
  }
  u=s;
  node[u].pre=-1;
  while (node[s].label<N) {
    if (u==t) {
      int min=inf;
      for (int i=node[u].pre; i!=-1; i=node[edge[i^1].to].pre)
        if (min>edge[i].cap-edge[i].flow)
          min=edge[i].cap-edge[i].flow;
      for (int i=node[u].pre; i!=-1; i=node[edge[i^1].to].pre) {
        edge[i].flow+=min;
        edge[i^1].flow-=min;
      }
      u=s;
      ans+=min;
      continue;
    }
    bool flag=false;
    int v;
    for (int i=node[u].cur; i!=-1; i=edge[i].next) {
      v=edge[i].to;
      if (edge[i].cap-edge[i].flow &&
          node[v].label+1==node[u].label) {
        flag=true;
        node[u].cur=node[v].pre=i;
        break;
      }
    }
    if (flag) {
      u=v;
      continue;
    }
    node[u].cur=node[u].head;
    int min=N;
    for (int i=node[u].head; i!=-1; i=edge[i].next)
      if (edge[i].cap-edge[i].flow && node[edge[i].to].label<min)
        min=node[edge[i].to].label;
    gap[node[u].label]--;
    if (!gap[node[u].label]) return ans;
    node[u].label=min+1;
    gap[node[u].label]++;
    if (u!=s) u=edge[node[u].pre^1].to;
  }
  return ans;
}

