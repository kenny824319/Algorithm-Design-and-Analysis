#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;


class sol{
	public:
		long long sum;
		deque<int> ans_array;
};

sol helper(vector<long long> &num){
	sol res;
	int n = num.size();
	auto dp = vector<vector<long long>>(2, vector<long long>(n, -10000000000));
	auto record = vector<int>(n, -1);
	
	int positive_end = -1;
	int negative_end = -1;
	if(num[0] > 0){
		positive_end++;
		dp[0][0] = num[0];
	}
	else if(num[0] < 0){
		negative_end++;
		dp[1][0] = num[0];
	}
	else{
		positive_end++;
		negative_end++;
		dp[0][0] = 0;
		dp[1][0] = 0;
	}
	long long ans = max(dp[0][0], dp[1][0]);
	for(int i = 1;i < n;i++){
		if(num[i] > 0){
			dp[0][i] = max({dp[1][i-1] + num[i], num[i], dp[0][i-1]});
			dp[1][i] = dp[1][i-1];
			if(dp[0][i] == dp[1][i-1] + num[i]){
				record[i] = negative_end;
				positive_end = i;
			}
			else if(dp[0][i] == num[i])
				positive_end = i;
				
		}
		else if(num[i] < 0){
			dp[1][i] = max({dp[0][i-1] + num[i], num[i], dp[1][i-1]});
			dp[0][i] = dp[0][i-1];
			if(dp[1][i] == dp[0][i-1] + num[i]){
				record[i] = positive_end;
				negative_end = i;
			}
			else if(dp[1][i] == num[i])
				negative_end = i;
		}
		else{
			dp[0][i] = max({dp[0][i-1], dp[1][i-1], num[i]});
			dp[1][i] = dp[0][i];
			
			if(dp[0][i] == dp[0][i-1])
				record[i] = positive_end;
			
			else if(dp[1][i] == dp[1][i-1])
				record[i] = negative_end;
			
			positive_end = i;
			negative_end = i;
		}
		ans = max(dp[0][i], dp[1][i]);
	}
	int backtrack;
	if(ans == dp[0][n-1]){
		backtrack = positive_end;
		while(backtrack != -1){
			res.ans_array.push_front(backtrack + 1);
			backtrack = record[backtrack];
		}
	}
	else{
		backtrack = negative_end;
		while(backtrack != -1){
			res.ans_array.push_front(backtrack + 1);
			backtrack = record[backtrack];
		}
		
	}
	res.sum = ans;
	
	return res;
	
}

int main(){
	int test_n, flag;
	cin >> test_n >> flag;
	
	for(int i = 0;i < test_n;i++){
		int n;
		cin >> n;
		auto num = vector<long long>(n, 0);
		for(int j = 0;j < n;j++)
			cin >> num[j];
		sol ans = helper(num);
		if(!flag)
			cout << ans.sum << '\n';
		else{
			cout << ans.sum << '\n';
			cout << ans.ans_array.size();
			for(auto it : ans.ans_array)
				cout << ' ' << it;
			cout << '\n';
		}
	}
}