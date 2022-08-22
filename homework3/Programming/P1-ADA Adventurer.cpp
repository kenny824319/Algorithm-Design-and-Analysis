#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

//discuss with b05504066 李旻翰 and b08902149 徐晨祐
using namespace std;

class GraphNode{
	public:
	  int id;
	  vector<int> adjacency;
	  int discovered;
	  GraphNode(){}
	  GraphNode(int id):id(id), discovered(0){}
};
class Info{
	public:
		int id;
		int edge_num;
};
vector<GraphNode> BFS_list;
vector<int> parent;
Info BFS(int start, int flag){
	Info res;
	queue<int> q;
	q.push(start);
	BFS_list[start-1].discovered = 1;
	
	int curr_id, adj_id;
	int step = 0;
	vector<int> tmp({start});
	while(!q.empty()){
		int size = q.size();
		while(size--){
			curr_id = q.front();
			q.pop();
			for(int i = 0; i < BFS_list[curr_id-1].adjacency.size(); i++){
				adj_id = BFS_list[curr_id-1].adjacency[i];
				if(BFS_list[adj_id-1].discovered == 0){
					tmp.push_back(adj_id);
					if(flag) parent[adj_id - 1] = curr_id - 1;
					BFS_list[adj_id-1].discovered = 1;
					q.push(adj_id);
				}
			}
		}
		step++;
	}
	for(auto it : tmp)
		BFS_list[it-1].discovered = 0;
	
	res.id = curr_id - 1;
	res.edge_num = step - 1;
	return res;
}
Info find_diameter(int root){
	Info x_info = BFS(root, 0);
	Info y_info = BFS(x_info.id+1, 1);
	return y_info;
}
int My_ceil(int num){
	return (num % 2) ? num / 2 + 1 : num / 2;
}
void sol(Info res){
	int backtrack = res.id;
	vector<int> diameter_node_array;
	while(backtrack != -1){
		BFS_list[backtrack].discovered = 1;
		diameter_node_array.push_back(backtrack + 1);
		backtrack = parent[backtrack];
	}
	int n = diameter_node_array.size();
	deque<int> pos_array(n, 0), neg_array(n, 0);
	Info tmp;
	int ans;
	for(int i = 1;i < n - 1;i++){
		ans = max(pos_array[i-1], i);
		for(auto it : BFS_list[diameter_node_array[i]-1].adjacency)
			if(BFS_list[it-1].discovered == 0){
				tmp = BFS(it, 0);
				ans = max(ans, tmp.edge_num + 1 + i);
			}
		pos_array[i] = ans;	
	}
	for(int i = n-2;i > 0;i--){
		ans = max(neg_array[i+1], n - 1 - i);
		for(auto it : BFS_list[diameter_node_array[i]-1].adjacency)
			if(BFS_list[it-1].discovered == 0){
				tmp = BFS(it, 0);
				ans = max(ans, tmp.edge_num + n - i);
			}
		neg_array[i] = ans;	
	}
	ans = n - 1;
	for(int i = 0;i < n-1;i++)
		ans = min(ans, max({pos_array[i], neg_array[i+1], My_ceil(pos_array[i])+My_ceil(neg_array[i+1])+1}));
	cout << ans;

}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int v1, v2;
	int node_num;
	cin >> node_num;
	if(node_num < 4)
		cout << node_num - 1;
	else{
		parent.resize(node_num, -1);
		for(int i = 1; i <= node_num; i++)
			BFS_list.push_back(GraphNode(i));
		for(int i = 0; i < node_num-1; i++){
			cin >> v1 >> v2;
			BFS_list[v1-1].adjacency.push_back(v2);
			BFS_list[v2-1].adjacency.push_back(v1);
		}
		Info res = find_diameter(1);
		sol(res);
	}
}