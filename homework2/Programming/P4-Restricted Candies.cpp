#include <iostream>
#include <queue>

using namespace std;
class node{
	public:
		int start_index;
		int end_index;
		long long pair_sum;
		node(int start_index, int end_index, long long pair_sum): start_index(start_index), end_index(end_index), pair_sum(pair_sum){}
		node(){}
};
class info{
	public:
		int prev_index;
		int next_index;
		int tag;
		info(int prev_index, int next_index): prev_index(prev_index), next_index(next_index), tag(0){}
		info(){}
};
vector<long long> pre_process(vector<long long> &num){
	auto res = vector<long long>({});
	int before_state = ((num[0] > 0)? 1 : 0);
	int cur_state;
	long long cur_max = num[0];
	int n = num.size();
	for(int i = 1;i < n;i++){
		cur_state = ((num[i] > 0)? 1 : 0);
		if(cur_state != before_state){
			res.push_back(cur_max);
			cur_max = num[i];
		}
		else{
			cur_max = max(num[i], cur_max);
		}
		before_state = cur_state;
	}
	res.push_back(cur_max);
	return res;
}
struct cmp {
    bool operator()(node a, node b){
        return a.pair_sum > b.pair_sum;
    }
};
void helper(vector<long long> &num, int orig_n){
	auto ans = vector<long long>(orig_n, 0);
	int n = num.size();
	long long total_n  = 0;
	long long total_n_1 = 0;
	auto info_table_n = vector<info>(n);
	auto info_table_n_1 = vector<info>(n);
	priority_queue<node, vector<node>, cmp> pq_n;
	priority_queue<node, vector<node>, cmp> pq_n_1;
	for(int i = 0;i < n;i++){
		total_n += num[i];
		pq_n.push(node(i, (i+1)%n, num[i]+num[(i+1)%n]));
		info_table_n[i] = info((i-1+n)%n, (i+1)%n);
	}
	if(n > 0)
		ans[n-1] = total_n;
	if(n-1 > 0){
		total_n_1 = total_n - min(num[n-1], num[0]);
		ans[n-2] = total_n_1;
	}
	if(n-1 > 1){		
		for(int i = 0;i < n-1;i++){
			if(num[n-1] < num[0]){
				pq_n_1.push(node(i, (i+1)%(n-1), num[i]+num[(i+1)%(n-1)]));
				info_table_n_1[i] = info((i-1+n-1)%(n-1), (i+1)%(n-1));
			}
			else{
				pq_n_1.push(node(i+1, (i+1)%(n-1)+1, num[i+1]+num[(i+1)%(n-1)+1]));
				info_table_n_1[i+1] = info((i-1+n-1)%(n-1)+1, (i+1)%(n-1)+1);
			}
		}
	}
	for(int i = n-2;i > 0;i -= 2){
		while(!pq_n.empty()){
			auto cur_pair = pq_n.top();
			if(info_table_n[cur_pair.start_index].tag == 0 && info_table_n[cur_pair.end_index].tag == 0){
				int new_start_index = info_table_n[cur_pair.start_index].prev_index;
				int new_end_index = info_table_n[cur_pair.end_index].next_index;
				info_table_n[cur_pair.start_index].tag = 1;
				info_table_n[cur_pair.end_index].tag = 1;
				info_table_n[new_start_index].next_index = new_end_index;
				info_table_n[new_end_index].prev_index = new_start_index;
				pq_n.pop();
				pq_n.push(node(new_start_index, new_end_index, num[new_start_index]+num[new_end_index]));
				total_n -= cur_pair.pair_sum;
				break;
			}
			else{
				pq_n.pop();
			}
		}
		ans[i-1] = total_n;
	}
	for(int i = n-3;i > 0;i -= 2){
		while(!pq_n_1.empty()){
			auto cur_pair = pq_n_1.top();
			if(info_table_n_1[cur_pair.start_index].tag == 0 && info_table_n_1[cur_pair.end_index].tag == 0){
				int new_start_index = info_table_n_1[cur_pair.start_index].prev_index;
				int new_end_index = info_table_n_1[cur_pair.end_index].next_index;
				info_table_n_1[cur_pair.start_index].tag = 1;
				info_table_n_1[cur_pair.end_index].tag = 1;
				info_table_n_1[new_start_index].next_index = new_end_index;
				info_table_n_1[new_end_index].prev_index = new_start_index;
				pq_n_1.pop();
				pq_n_1.push(node(new_start_index, new_end_index, num[new_start_index]+num[new_end_index]));
				total_n_1 -= cur_pair.pair_sum;
				break;
			}
			else{
				pq_n_1.pop();
			}
		}
		
		ans[i-1] = total_n_1;
	}
	for(auto it : ans)
		cout << it << ' ';
	cout << endl;
}
int main(){
	 int t, flag;
	 cin >> t >> flag;
	 while(t--){
		int n;
		cin >> n;
		auto temp = vector<long long>(n);
		 
		for(int i = 0;i < n;i++)
		 cin >> temp[i];

		auto num = pre_process(temp);
		helper(num, n);
	 }
	 
}