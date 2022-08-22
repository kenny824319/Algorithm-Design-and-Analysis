#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
auto array = vector<pair<int, int>>({});
long long ans = 0;

bool cmp(pair<int, int> a, pair<int, int> b){
	return a.first < b.first;
}

bool cmp1(pair<int,int> p, int v){
	return p.second <= v;
}

pair<int, int> L[200000], R[200000]; 

void merge_query(int l, int m, int r, int middle_line){
	int i ,j;
    int n1 = m - l + 1;
    int n2 = r - m;
	int k = l;
	for (i = 0; i < n1; i++) L[i] = array[l + i];
	
    for (j = 0; j < n2; j++) R[j] = array[m + 1 + j];
	
	i = j = 0;

	while(i < n1 && j < n2){
		if(L[i].second < R[j].second)
			array[k++] = L[i++];
		else
			array[k++] = R[j++];
    }
	
    while (i < n1) array[k++] = L[i++];
 
    while (j < n2) array[k++] = R[j++];
	
	vector<pair<int, int>> left_stack = {};
	vector<pair<int, int>> right_stack = {};
	for(i = l;i <= r;i++){
		int dist_from_middle_line = array[i].first - middle_line;
		if(dist_from_middle_line > 0){//right
			
			int right_top = right_stack.size()-1;
			while(right_top != -1){
				if(right_stack[right_top].first - middle_line >= dist_from_middle_line){
					right_stack.pop_back();
					right_top = right_stack.size()-1;
				}
				else
					break;
			}
			if(right_stack.size() > 0)//binary_search
				ans += left_stack.end() - lower_bound(left_stack.begin(), left_stack.end(), right_stack[right_top].second, cmp1);
			else if(right_stack.size() == 0)
				ans += left_stack.size();
			right_stack.push_back(array[i]);
		}
		else{//left
			dist_from_middle_line = abs(dist_from_middle_line);
			int left_top = left_stack.size()-1;
			while(left_top != -1){
				if(middle_line - left_stack[left_top].first >= dist_from_middle_line){
					left_stack.pop_back();
					left_top = left_stack.size()-1;
				}
				else
					break;
			}
			if(left_stack.size() > 0)//binary_search
				ans += right_stack.end() - lower_bound(right_stack.begin(), right_stack.end(), left_stack[left_top].second, cmp1);
			else if(left_stack.size() == 0)
				ans += right_stack.size();
			left_stack.push_back(array[i]);
		}
	}
	
}

void merge_sort(int l, int r){
	if(l < r){
		int m = l + (r - l) / 2;
		int middle_line = (array[m].first + array[m+1].first) / 2;
		merge_sort(l, m);
		merge_sort(m + 1, r);
		merge_query(l, m, r, middle_line);
	}
}

int main(){
	int n;
	cin >> n;
	for(int i = 0;i < n;i++){
		int x, y;
		cin >> x >> y;
		array.push_back({x, y});
	}
	sort(array.begin(), array.end(), cmp);
	merge_sort(0, n-1);
	cout << ans;
}