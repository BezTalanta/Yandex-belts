#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <algorithm>

using namespace std;

int main(){
	int q; cin >> q;
	
	unordered_map<string, vector<string> > m, m2;
	for(int i = 0; i < q; ++i){
		string command; cin >> command;
		
		if(command == "NEW_BUS"){
			string bus; cin >> bus;
			int count; cin >> count;
			
			vector<string> stops;
			for(int j = 0; j < count; ++j){
				string stop; cin >> stop;
				stops.push_back(stop);
				m2[stop].push_back(bus);
			}
			m[bus] = stops;
		}
		else if(command == "BUSES_FOR_STOP"){
			string stop; cin >> stop;
			unordered_map<string, vector<string> >::iterator find = m2.find(stop);
			if(find == m2.end())
				cout << "No stop\n";
			else {
				for(const string& items : find->second)
					cout << items << ' ';
				cout << '\n';
			}
		}
		else if(command == "STOPS_FOR_BUS"){
			string bus; cin >> bus;
			unordered_map<string, vector<string> >::iterator find = m.find(bus);
			if(find == m.end()){
				cout << "No bus\n";
				continue;
			}
			
			for(const string& itemStop : find->second){
				unordered_map<string, vector<string> >::iterator find2 = m2.find(itemStop);
				if(find2->second.size() == 1){
					cout << "Stop " << itemStop << ": no interchange\n";
					continue;
				}
				
				cout << "Stop " << itemStop << ": ";
				for(const string& itemBus : find2->second)
					if(itemBus != bus)
						cout << itemBus << ' ';
				cout << '\n';
			}
		}
		else if(command == "ALL_BUSES"){
			if(m.size() == 0){
				cout << "No buses\n";
				continue;
			}
			
			map<string, vector<string> > copy;
			for(const auto& items : m)
				copy[items.first] = items.second;
			
			for(const auto& items : copy){
				cout << "Bus " << items.first << ": ";
				for(const string& itemsStop : items.second)
					cout << itemsStop << ' ';
				cout << '\n';
			}
		}
	}
}
