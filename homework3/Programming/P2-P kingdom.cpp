#include<bits/stdc++.h>
#define ll long long
using namespace std;
//reference : https://github.com/PetarV-/Algorithms/blob/master/Graph%20Algorithms/Kosaraju's%20Algorithm.cpp
//非常感謝b08501098 柯晨緯的幫忙!

struct Node{
    vector<int> adj;
    vector<int> rev_adj;
};
class GraphNode{
	public:
	  int id;
	  vector<int> adjacency;
	  int discovered;
	  GraphNode(){}
	  GraphNode(int id):id(id), discovered(0){}
};

stack<int> S;
vector<bool> visited;;
vector<int> component;
vector<GraphNode> SCC_Graph;
int numComponents;


void kosaraju_dfs_1(vector<Node> &Graph, int x){
    visited[x] = true;
    for(int i = 0;i < Graph[x].adj.size();i++)
        if(!visited[Graph[x].adj[i]]) 
			kosaraju_dfs_1(Graph, Graph[x].adj[i]);
    S.push(x);
}

void kosaraju_dfs_2(vector<vector<int>> &components, vector<Node> &Graph, int x){
    components[numComponents].push_back(x);
	component[x] = numComponents;
    visited[x] = true;
    for(int i = 0;i < Graph[x].rev_adj.size();i++)
        if(!visited[Graph[x].rev_adj[i]]) 
			kosaraju_dfs_2(components, Graph, Graph[x].rev_adj[i]);
}
class Info{
	public:
		bool find;
		int sink;
		Info(bool find, int sink):find(find), sink(sink){}
};

Info dfs(int x, unordered_set<int> &sink){
	SCC_Graph[x].discovered = 1;
	if(sink.count(x)){
		sink.erase(x);
		return Info(true, x);
	}
	for(int i = 0;i < SCC_Graph[x].adjacency.size();i++){
		int next = SCC_Graph[x].adjacency[i];
		if(SCC_Graph[next].discovered == 0){
			Info res = dfs(next, sink);
			if(res.find)
				return res;
		}
	}
	return Info(false, -1);
}

void sol(vector<Node> &Graph, int flag){
	int n = Graph.size() - 1;
    for (int i = 1;i <= n;i++)
        if(!visited[i]) 
			kosaraju_dfs_1(Graph, i);
		
    visited.assign(n+1, false);
    numComponents = 0;
	vector<vector<int>> components(n, vector<int>({}));
    while (!S.empty()){
        int v = S.top(); 
		S.pop();
        if (!visited[v]){
            kosaraju_dfs_2(components, Graph, v);
            numComponents++;
        }
    }
	for(int i = 0;i < numComponents;i++)
		SCC_Graph.push_back(GraphNode(i));
	vector<int> indegree_table(numComponents, 0);
	vector<int> outdegree_table(numComponents, 0);
	for(int i = 1;i <= n;i++){
		int v1, v2;
		v1 = component[i];
		for(int j = 0;j < Graph[i].adj.size();j++){
			v2 = component[Graph[i].adj[j]];
			if(v1 != v2){
				SCC_Graph[v1].adjacency.push_back(v2);
				outdegree_table[v1]++;
				indegree_table[v2]++;
			}
		}	
	}
	int indegree_0 = 0;
	int outdegree_0 = 0;
	vector<int> isolated_point;
	if(numComponents == 1)
		cout << 0 << '\n';
	else{
		unordered_set<int> source;
		unordered_set<int> sink;
		for(int i = 0;i < indegree_table.size();i++)
			if(!indegree_table[i]){
				indegree_0++;
				if(!outdegree_table[i])
					isolated_point.push_back(i);
				else
					source.insert(i);
			}
		for(int i = 0;i < outdegree_table.size();i++)
			if(!outdegree_table[i]){
				outdegree_0++;
				if(indegree_table[i])
					sink.insert(i);
			}
		cout << max(indegree_0, outdegree_0) << '\n';
		if(!flag) return;
		vector<pair<int, int>> source_sink;
		vector<int> source_erase;
		for(auto it : source){
			Info res = dfs(it, sink);
			if(res.find){
				source_sink.push_back({it, res.sink});
				source_erase.push_back(it);
			}
		}
		for(auto it : source_erase)
			source.erase(it);
		vector<pair<int, int>> res_edge;
		int len = source_sink.size()-1;
		for(int i = 0;i < len;i++){//接鏈
			res_edge.push_back({components[source_sink[i].second][0], components[source_sink[i+1].first][0]});
		}
		if(source_sink.size() == 0 && isolated_point.size())//沒鏈但有多個孤立點
			res_edge.push_back({components[isolated_point[isolated_point.size()-1]][0], components[isolated_point[0]][0]});
		else if(source_sink.size() && isolated_point.size() == 0)//有鏈但沒孤立點
			res_edge.push_back({components[source_sink[source_sink.size()-1].second][0], components[source_sink[0].first][0]});
		else if(source_sink.size() && isolated_point.size()){//有超過一條鏈且有多個孤立點
			res_edge.push_back({components[source_sink[source_sink.size()-1].second][0], components[isolated_point[0]][0]});
			res_edge.push_back({components[isolated_point[isolated_point.size()-1]][0], components[source_sink[0].first][0]});
		}
		len = isolated_point.size()-1;
		for(int i = 0;i < len;i++){//接孤立點
			res_edge.push_back({components[isolated_point[i]][0], components[isolated_point[i+1]][0]});
		}
		auto source_itr = source.begin();
		auto sink_itr = sink.begin();
		while(source_itr != source.end() && sink_itr != sink.end()){
			res_edge.push_back({components[*sink_itr][0], components[*source_itr][0]});
			source_itr = source.erase(source_itr);
			sink_itr = sink.erase(sink_itr);
		}
		source_itr = source.begin();
		sink_itr = sink.begin();
		while(source_itr != source.end()){
			res_edge.push_back({res_edge[0].first, components[*source_itr][0]});
			source_itr = source.erase(source_itr);
		}
		while(sink_itr != sink.end()){
			res_edge.push_back({components[*sink_itr][0], res_edge[0].first});
			sink_itr = sink.erase(sink_itr);
		}
		for(auto it : res_edge)
			cout << it.first << ' ' << it.second << '\n';
	}
	SCC_Graph.clear();
	return;
}


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int t, flag;
	cin >> t >> flag;
	
	while(t--){
		int node_num, edge_num;
		cin >> node_num >> edge_num;
		vector<Node> Graph(node_num+1);
		visited.assign(node_num+1, false);
		component.assign(node_num+1, 0);
		for(int i = 0;i < edge_num;i++){
			int v1, v2;
			cin >> v1 >> v2;
			Graph[v1].adj.push_back(v2);
			Graph[v2].rev_adj.push_back(v1);
		}
		sol(Graph, flag);
	}
	
}