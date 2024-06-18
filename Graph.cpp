#include <bits/stdc++.h>
using namespace std;

//                               Disjoint Set
class DisjointSet{
    vector<int>rank,parent;  //Array rank is maintained to keep our tree of limited height
    public:
    DisjointSet(int n){
        rank.resize(n+1,0);
        parent.resize(n+1);
        for(int i = 0;i<=n;i++){
            parent[i] = i;
        }
    }
    int findUltParent(int node){
        if(parent[node]==node){
            return node;
        }
        parent[node] = findUltParent(parent[node]);
        return parent[node];
    }
    void unionByRank(int u,int v){
        int ultParU = findUltParent(u);
        int ultParV = findUltParent(v);
        if(ultParU==ultParV){
            return;
        }
        if(rank[ultParU]<rank[ultParV]){
            parent[ultParU] = ultParV;
        }
        else if(rank[ultParU]>rank[ultParV]){
            parent[ultParV] = ultParU;
        }
        else{
            parent[ultParV] = ultParU;
            rank[ultParU]++;
        }
    }
};


//                       Strongly connected components(kosaraju algorithm)
// dfs with optional stack (toposort)
void dfs(int node,vector<vector<int>>&adj,vector<bool>&visited,stack<int>*st=NULL){
    visited[node] = true;
    for(auto it:adj[node]){
        if(!visited[it]){
            dfs(it,adj,visited,st);
        }
    }
    if(st)st->push(node);
}
int kosaraju(int n,vector<vector<int>>&adj){
    // step 1 : sort on basis of time in stack
    stack<int>st;
    vector<bool>visited(n,false);
    for(int i = 0;i<n;i++){
        if(!visited[i]){
            dfs(i,adj,visited,&st);
        }
    }

    // step 2 : reverse the graph
    vector<vector<int>>rev(n);
    for(int i = 0;i<n;i++){
        visited[i] = false;
        for(auto it:adj[i]){
            rev[it].push_back(i);
        }
    }

    // step 3 : count scc
    int scc = 0;
    while(!st.empty()){
        int node = st.top();
        st.pop();
        if(!visited[node]){
            scc++;
            dfs(node,rev,visited);
        }
    }

    return scc;

}

int main(){
    vector<vector<int>>adj = {{1,2},{0,2},{}};
    cout<<kosaraju(3,adj);
}