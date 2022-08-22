#include <iostream>
#include <vector>

using namespace std;
vector<vector<int>> peg = vector<vector<int>>(3, vector<int>({}));
vector<long long> power = vector<long long>({1});
vector<int> memo;

long long helper(int disk, int start, int middle, int end, long long ans){
	int condition = 0;
	
	if(disk == 0)
		return ans;
	
	if(memo[disk] == start)
		condition = 1;
	else if(memo[disk] == end)
		condition = 2;
	
	if(condition == 1){
		ans = (ans + power[disk - 1]) % 998244353;
		ans = helper(disk - 1, start, end, middle, ans);
	}
	else if(condition == 2)
		ans = helper(disk - 1, middle, start, end, ans);
	
	else
		ans = helper(0, start, middle, end, -1);
	
	return ans;
	
}

int main(){
	int n, i, data;
	cin >> n;
	int left_n, middle_n, right_n;
	auto temp = vector<int>(n+1, 0);
	
	for(i = 1;i <= n;i++)
		power.push_back((power[i-1] * 2) % 998244353);
	
	cin >> left_n;
	
	for(i = 0;i < left_n;i++){
		cin >> data;
		peg[0].push_back(data);
	}
	
	cin >> middle_n;
	
	for(i = 0;i < middle_n;i++){
		cin >> data;
		temp[data] = 1;
		peg[1].push_back(data);
	}
	
	cin >> right_n;
	
	for(i = 0;i < right_n;i++){
		cin >> data;
		temp[data] = 2;
		peg[2].push_back(data);
	}
	
	memo = move(temp);
	cout << helper(n, 0, 1, 2, 0);
}