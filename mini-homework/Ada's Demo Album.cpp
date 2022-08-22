#include <climits>
#include <iostream>
#include <vector>

using namespace std;
class item{
	public:
		int left, right;
		long long sum;
		item(int i, int j, long long Sum): left(i), right(j), sum(Sum) {}
};

item cross_array(vector<long long> &num, int i, int k, int j, int x, int y, int z){
	long long left_sum = LONG_LONG_MIN;
	long long sum = 0;
	int max_left;
	for(int p = k;p >= i;p--){
		sum = sum + x * num[p];
		if(sum > left_sum){
			left_sum = sum;
			max_left = p;
		}
		sum = sum - x * num[p] + y * num[p];
	}
	long long right_sum = LONG_LONG_MIN;
	sum = 0;
	int max_right;
	for(int q = k+1;q <= j;q++){
		sum = sum + z * num[q];
		if(sum > right_sum){
			right_sum = sum;
			max_right = q;
		}
		sum = sum - z * num[q] + y * num[q];
	}
	
	return item(max_left, max_right, left_sum + right_sum);
}


item helper(vector<long long> &num, int i, int j, int x, int y, int z){
	if(i == j)
		return item(i, j, LONG_LONG_MIN);
	else{
		int k = (i + j) / 2;
		auto left_item = helper(num, i, k, x, y, z);
		auto right_item = helper(num, k+1, j, x, y, z);
		auto cross_item = cross_array(num, i, k, j, x, y, z);
		if(left_item.sum >= right_item.sum && left_item.sum >= cross_item.sum)
			return left_item;
		else if(right_item.sum >= left_item.sum && right_item.sum >= cross_item.sum)
			return right_item;
		else
			return cross_item;
	}
		
}

int main(){
	long long n, x, y, z, i;
	cin >> n >> x >> y >> z;
	
	auto num = vector<long long>({});
	for(i = 0;i < n;i++){
		long long data;
		cin >> data;
		num.push_back(data);
	}
	auto res_item = helper(num, 0, n-1, x, y, z);
	long long res = res_item.sum;
	cout << res;
}