#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>

using namespace std;

int main(){
	int q; cin >> q;
	
	map<string, set<string> > dictionary;
	for(int i = 0; i < q; ++i){
		string com; cin >> com;
		if(com == "ADD"){
			string word1, word2; cin >> word1 >> word2;
			
			dictionary[word1].insert(word2);
			dictionary[word2].insert(word1);
		}
		else if(com == "COUNT"){
			string in; cin >> in;
			cout << dictionary[in].size() << '\n';
		}
		else if(com == "CHECK"){
			string word1, word2; cin >> word1 >> word2;
			if(dictionary[word1].count(word2))
				cout << "YES\n";
			else
				cout << "NO\n";
		}
	}
}