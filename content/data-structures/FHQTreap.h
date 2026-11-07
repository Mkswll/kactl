/**
 * Author: Maxwell He
 * Date: 
 * License: 
 * Source: 
 * Description: 
 */
#pragma once

template <typename T>
struct FHQTreap {
	int n, rt;
	
	struct Node {
		int lc = 0, rc = 0;
		T key;
		int pri, siz = 0; 
	};
	
	vector<Node> t;
	
	FHQTreap(): n(0), rt(0) {
		t.emplace_back();
	}
	
	FHQTreap(int up): n(0), rt(0) {
		t.reserve(up);
		t.emplace_back();
	}
	
	int new_node(T x){
		++n;
		t.emplace_back();
		t[n].siz = 1;
		t[n].lc = t[n].rc = 0;
		t[n].key = x;
		t[n].pri = rng();
		return n;
	}
	
	void push_up(int cur){
		t[cur].siz = t[t[cur].lc].siz + t[t[cur].rc].siz + 1;
	}
	
	void split(int cur, T x, int& ltree, int& rtree){ // x is target
		if(!cur){
			ltree = rtree = 0;
			return;
		}
		if(t[cur].key <= x){
			ltree = cur;
			split(t[cur].rc, x, t[cur].rc, rtree);
		}
		else{
			rtree = cur;
			split(t[cur].lc, x, ltree, t[cur].lc);
		}
		push_up(cur);
	}
	
	void split_by_size(int cur, int siz, int& ltree, int& rtree){
		if(!cur){
			ltree = rtree = 0;
			return;
		}
		if(t[t[cur].lc].siz + 1 <= siz){
			ltree = cur;
			split_by_size(t[cur].rc, siz - t[t[cur].lc].siz - 1, t[cur].rc, rtree);
		}
		else{
			rtree = cur;
			split_by_size(t[cur].lc, siz, ltree, t[cur].lc);
		}
		push_up(cur);
	}
	
	int merge(int ltree, int rtree){
		if(!ltree) return rtree;
		if(!rtree) return ltree;
		if(t[ltree].pri > t[rtree].pri){
			t[ltree].rc = merge(t[ltree].rc, rtree);
			push_up(ltree);
			return ltree;
		}
		else{
			t[rtree].lc = merge(ltree, t[rtree].lc);
			push_up(rtree);
			return rtree;
		}
	}
};