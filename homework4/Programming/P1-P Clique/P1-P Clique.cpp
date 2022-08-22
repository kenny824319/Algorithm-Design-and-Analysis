#include"ypglpk.hpp"
#include<bits/stdc++.h>
#define MAX_N 80
//discussion with b08902149 徐晨祐 & b08501098 柯晨緯
using namespace std;
class GraphNode{
	public:
		vector<int> adjacency;
		GraphNode(){}
};

void Bron_Kerbosch(bitset<MAX_N> P, bitset<MAX_N> R, bitset<MAX_N> X, vector<GraphNode> &graph, vector<bitset<MAX_N>> &clique){
    if((P | X).none()){
        clique.push_back(R);
        return;
    }
    int u = -1, nbrs_size = -1;
    bitset<MAX_N> one = 1;
    bitset<MAX_N> temp = P | X;
    for(int i = 0;i < int(graph.size());i++)
        if(temp[i] && int(graph[i].adjacency.size()) > nbrs_size){
            nbrs_size = graph[i].adjacency.size();
            u = i;
        }
    bitset<MAX_N> nbrs_u = 0;
    for(int i = 0;i < int(graph[u].adjacency.size());i++) nbrs_u |= (one << graph[u].adjacency[i]);
    bitset<MAX_N> updatedP = P ^ (P & nbrs_u); 
    while(updatedP.any()){
        int v = updatedP._Find_first();
        one = 1;
        bitset<MAX_N> nbrs_v = 0;
        for(int i = 0;i < int(graph[v].adjacency.size());i++) nbrs_v |= (one << graph[v].adjacency[i]);
        Bron_Kerbosch(P & nbrs_v, R | (one << v), X & nbrs_v, graph, clique);
		updatedP[v] = 0;
        P[v] = 0;
        X[v] = 1;
    }
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while(T--){
		int N, M;
		cin >> N >> M;
		vector<GraphNode> graph(N);
		for(int i = 0;i < M;i++){
			int u, v;
			cin >> u >> v;
			graph[u].adjacency.push_back(v);
			graph[v].adjacency.push_back(u);
		}
		bitset<MAX_N> R = 0, P = 0, X = 0;
		for(int i = 0;i < N;i++) P[i] = 1;
		vector<bitset<MAX_N>> clique;
		Bron_Kerbosch(P, R, X, graph, clique);
		int clique_sz = clique.size();
		vector<bool> isinit(clique_sz, true);
		vector<vector<double>> A(2 * clique_sz + N, vector<double>(clique_sz, 0));
		vector<double> B(2 * clique_sz + N, 0);
		vector<double> C(clique_sz, -1);
		vector<vector<int>> clique_set(clique_sz, vector<int>({}));
		for(int i = 0;i < clique_sz;i++){
			A[i][i] = 1;
			A[i+clique_sz][i] = -1;
			B[i] = 1;
			B[i+clique_sz] = 0;
		}
		for(int i = 0;i < clique_sz;i++)
			for(int j = 0;j < N;j++){
				if(clique[i][j]){
					clique_set[i].push_back(j);
					A[j+2*clique_sz][i] = -1;
					B[j+2*clique_sz] = -1;
				}
			}

		vector<double> opt = ypglpk::mixed_integer_linear_programming(A, B, C, isinit).second;
		vector<bool> is_used(N, false);
		vector<vector<int>> ans;
		for(int i = 0;i < int(opt.size());i++)
			if(opt[i]){
				vector<int> tmp;
				for(int j = 0;j < int(clique_set[i].size());j++)
					if(!is_used[clique_set[i][j]]){
						is_used[clique_set[i][j]] = true;
						tmp.push_back(clique_set[i][j]);
					}
				if(tmp.size()) ans.push_back(tmp);
			}
		cout << ans.size() << '\n';
		for(int i = 0;i < int(ans.size());i++){
			cout << ans[i].size() << ' ';
			for(auto it : ans[i]) cout << it << ' ';
			cout << '\n';
		}
	}
}