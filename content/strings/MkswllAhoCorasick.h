/**
 * Author: Maxwell He
 * Date: 
 * License: 
 * Source: 
 * Description: 
 */
#pragma once

int trie[MAXN][30], tot = 0;
int fail[MAXN];
bool vis[MAXN];
vector<int> rec[MAXN];

void build_trie(string s, int id){
	int len = (int) s.size();
	int cur = 0;
	for(int i = 0; i < len; ++i){
		if(!trie[cur][s[i] - 'a']){
			trie[cur][s[i] - 'a'] = ++tot;
		}
		cur = trie[cur][s[i] - 'a'];
	}
	rec[cur].pb(id); // marks the end of a template string
}

void get_fail(){
	queue <int> q;
	for(int i = 0; i < 26; ++i){
		if(trie[0][i]){
			// fail[trie[0][i]] = 0;
			q.push(trie[0][i]);
		}
	}
	while(!q.empty()){
		int cur = q.front();
		q.pop();
		for(int i = 0; i < 26; ++i){
			if(trie[cur][i]){
				fail[trie[cur][i]] = trie[fail[cur]][i];
				q.push(trie[cur][i]);
			}
			else{
				trie[cur][i] = trie[fail[cur]][i];
			}
		}
	}
}

void get_ans(string s){
	// build trie and call get_fail() first
	int len = (int) s.size();
	int cur = 0;
    for(int i = 0; i < len; ++i){
    	cur = trie[cur][s[i] - 'a'];
    	int temp = cur;
    	while(temp && !vis[temp]){
    		// code here
    		
    		vis[temp] = 1;
    		temp = fail[temp];
    	}
    }
}
