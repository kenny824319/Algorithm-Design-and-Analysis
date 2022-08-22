#include "ada-hw4-p3.h"
#include <bits/stdc++.h>
//discussion with b08902149 徐晨祐 & b08501098 柯晨緯
// feel free to use global variables
std::vector<int> contest;
std::vector<int> pos2id;
std::vector<bool> conceal(3004, false);
std::vector<int> del_pair(3004);

std::vector<int> init(int N){
	int l = 0, r = 1;
	for(int i = 0;i < N;i++) pos2id.push_back(i);
    while(r < N){
		if(compare(l, r)){
			l = r;
			r++;
		}
		else{//inversion
			contest.push_back(l);
			contest.push_back(r);
			conceal[l] = conceal[r] = true;
			del_pair[l] = r;
			del_pair[r] = l;
			r++;
			while(l >= 0 && conceal[l]) l--;
			if(l == -1){
				l = r;
				r++;
			}
		}
	}
    return contest;
}

std::vector<int> insert(int p, int id) {
    pos2id.insert(pos2id.begin() + p, id);
	int N = pos2id.size();
	int l = p-1;
	while(l >= 0 && conceal[pos2id[l]]) l--;
	if(l != -1 && !compare(pos2id[l], pos2id[p])){
		contest.push_back(pos2id[l]);
		contest.push_back(pos2id[p]);
		conceal[pos2id[l]] = conceal[pos2id[p]] = true;
		del_pair[pos2id[l]] = pos2id[p];
		del_pair[pos2id[p]] = pos2id[l];
	}
	else{
		int r = p+1;
		while(r < N && conceal[pos2id[r]]) r++;
		if(r != N && !compare(pos2id[p], pos2id[r])){
			contest.push_back(pos2id[p]);
			contest.push_back(pos2id[r]);
			conceal[pos2id[p]] = conceal[pos2id[r]] = true;
			del_pair[pos2id[p]] = pos2id[r];
			del_pair[pos2id[r]] = pos2id[p];
		}
	}
	
    return contest;
}

std::vector<int> remove(int p) {
	if(conceal[pos2id[p]]){
		int contest_remove_pos;
		conceal[del_pair[pos2id[p]]] = false;
		for(int i = 0;i < contest.size();i++)
			if(contest[i] == pos2id[p]){
				contest_remove_pos = i;
				break;
			}
		contest.erase(contest.begin() + contest_remove_pos);
		for(int i = 0;i < contest.size();i++)
			if(contest[i] == del_pair[pos2id[p]]){
				contest_remove_pos = i;
				break;
			}
		contest.erase(contest.begin() + contest_remove_pos);
		int N = pos2id.size();
		int dummy_insert_pos;
		for(int i = 0;i < N;i++)
			if(pos2id[i] == del_pair[pos2id[p]]){
				dummy_insert_pos = i;
				break;
			}
		
		int l = dummy_insert_pos-1;
		while(l >= 0 && conceal[pos2id[l]]) l--;
		if(l != -1 && !compare(pos2id[l], pos2id[dummy_insert_pos])){
			contest.push_back(pos2id[l]);
			contest.push_back(pos2id[dummy_insert_pos]);
			conceal[pos2id[l]] = conceal[pos2id[dummy_insert_pos]] = true;
			del_pair[pos2id[l]] = pos2id[dummy_insert_pos];
			del_pair[pos2id[dummy_insert_pos]] = pos2id[l];
		}
		else{
			int r = dummy_insert_pos+1;
			while(r < N && conceal[pos2id[r]]) r++;
			if(r != N && !compare(pos2id[dummy_insert_pos], pos2id[r])){
				contest.push_back(pos2id[dummy_insert_pos]);
				contest.push_back(pos2id[r]);
				conceal[pos2id[dummy_insert_pos]] = conceal[pos2id[r]] = true;
				del_pair[pos2id[dummy_insert_pos]] = pos2id[r];
				del_pair[pos2id[r]] = pos2id[dummy_insert_pos];
			}
		}
	}
	pos2id.erase(pos2id.begin() + p);
    return contest;
}
