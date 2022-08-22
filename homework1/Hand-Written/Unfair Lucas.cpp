#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <climits>

using namespace std;

class sol{
	public:
		int start;
		int end;
		int min;
		sol(int start, int end, int min):start(start), end(end), min(min){}
		sol(){}
	
};


int main(){
	int n;
	cin >> n;
	auto num = vector<int>(n);
	for(int i = 0;i < n;i++)
		cin >> num[i];
	auto left = vector<sol>(n, sol(0, 0, 0));
	auto right = vector<sol>(n, sol(n-1, n-1, 0));
	int cur_min = num[0];
	int ans_min = num[0];
	int total = num[0];
	int min_pos_start = 0;
	int min_pos_end = 0;
	

	for(int i = 1;i < n;i++){
		left[i] = sol(min_pos_start, min_pos_end, ans_min);
		total += num[i];
		if(num[i] < ans_min)
			min_pos_start = i;
		cur_min = min(cur_min + num[i], num[i]);
		if(cur_min < ans_min)
			min_pos_end = i;
		ans_min = min(cur_min, ans_min);
		
	}
	cur_min = ans_min = num[n-1];
	int min_neg_start = n-1;
	int min_neg_end = n-1;
	for(int i = n-2;i >= 0;i--){
		right[i] = sol(min_neg_end, min_neg_start, ans_min);
		if(num[i] < ans_min)
			min_neg_start = i;
		cur_min = min(cur_min + num[i], num[i]);
		if(cur_min < ans_min)
			min_neg_end = i;
		ans_min = min(cur_min, ans_min);
	}
	auto final_res = vector<int>(n);
	ans_min = INT_MAX;
	sol res;
	int cross_skip_index;
	
	cout << '\n';
	
	for(int i = 0;i < n;i++){
		final_res[i] = min(num[i] + left[i].min, num[i] + right[i].min);
		if(final_res[i] < ans_min){
			cross_skip_index = i;
			if(final_res[i] == num[i]+left[i].min)
				res = left[i];
			else
				res = right[i];
		}
		ans_min = min(final_res[i], ans_min);
	}
	cout << "cross head tail skip index of num[i] : " << cross_skip_index << '\n';
	cout << "cross head tail skip from : " << res.start <<" to : "<< res.end << '\n';
	cout << "cross head tail and skip once : " << total - ans_min << '\n' << '\n';
	int cur_max = num[0];
	int ans_max = num[0];
	int cur_max_skip = 0;
	int skip_num_index = 0;
	int start = 0;
	int end = 0;
	for(int i = 1;i < n;i++){
		if(cur_max > cur_max_skip + num[i])
			skip_num_index = i;
		cur_max_skip = max(cur_max, cur_max_skip + num[i]);
		if(num[i] > ans_max)
			start = i;
		cur_max = max(cur_max + num[i], num[i]);
		if(cur_max_skip > ans_max)
			end = i;
		ans_max = max(cur_max_skip, ans_max);
	}
	cout << "skip num index : " << skip_num_index << '\n';
	cout << "skip once and max in the mid from : " << start <<" to : "<< end << "\n";
	cout <<"skip once and max in the mid : " << ans_max << '\n' << '\n';
	
	cout << "skip once max val : " << ((ans_max > 0) ? max(ans_max, total - ans_min) : ans_max) << "\n\n";
	cur_max = num[0];
	ans_max = num[0];
	start = end = 0;
	for(int i = 1;i < n;i++){
		if(num[i] > ans_max)
			start = i;
		cur_max = max(cur_max + num[i], num[i]);
		if(cur_max > ans_max)
			end = i;
		ans_max = max(cur_max, ans_max);
	}
	cout << "didn't skip and max in the mid from : " << start <<" to : "<< end << '\n';
	cout <<"didn't skip and max in the mid : " << ans_max << "\n\n";
	
	
	cur_min = num[0];
	ans_min = num[0];
	start = end = 0;
	for(int i = 1;i < n;i++){
		if(num[i] < ans_min)
			start = i;
		cur_min = min(cur_min + num[i], num[i]);
		if(cur_min < ans_min)
			end = i;
		ans_min = min(cur_min, ans_min);
	}
	cout << "cross head tail skip from : " << start <<" to : "<< end << '\n';
	cout <<"cross head tail max val :" << total - ans_min << '\n' << '\n';
	
	cout << "didn't skip max val : " << ((ans_max > 0) ? max(ans_max, total - ans_min) : ans_max) << "\n\n";
}