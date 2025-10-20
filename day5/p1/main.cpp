#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <set>

using namespace std;

vector<int> getvalues(string s) {

	vector<int> out;
	size_t pos = 0;
	string token;
	while (true) {
		pos = s.find(",");
		token = s.substr(0, pos);
		out.push_back(stoi(token));
		s.erase(0, pos + 1);
		if (pos == string::npos) break;
	}
	return out;
}

bool isvalid(const vector<int> & data, 
	const map<int,set<int>> & dict) {

	map<int, int> ids;

	size_t len = data.size();

	for (int i = 0; i < len; i++) {
		ids[data[i]] = i;
	}

	for (const auto & pair : dict) {
		int id1 = ids[pair.first];
		for (const auto & x : pair.second) {
			auto it = find(data.begin(), data.end(), x);
			if (it == data.end()) continue;
			if (ids[x] < id1) {
				// cout << "[";
				// for (auto & pp : data) {
				// 	cout << pp << ",";
				// }
				// cout << "] " << pair.first << " is after " << x << endl;
				return false;
			}
		}
	}

	return true;
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout << "Usage: " << argv[0] << " <file>" << endl;
		exit(EXIT_FAILURE);
	}
	ifstream f(argv[1]);

	map<int,set<int>> data;

	bool search = false;
	int ret = 0;

	string line;
	while (getline(f, line)) {
		if (line == "") { 
			cout << "BLANK!~\n"; 
			search = true;  
			continue;
		}

		if (!search) {
			int a, b;
			sscanf(line.c_str(), "%d|%d", &a, &b);
			data[a].insert(b);
			cout << line << ": " << a << ", " << b << endl;
		} 
		else {
			vector<int> vals = getvalues(line);
			if (isvalid(vals, data)) {
				int middle = vals.size() / 2;
				ret += vals[middle];

				for (auto & i : vals) {
					cout << i << ",";
				}
				cout << endl;
				// cout << " is valid!" << endl;
			}
			else {
				// cout << endl;
			}
		}
	}
	cout << "Total: " << ret << endl;

	f.close();
	exit(EXIT_SUCCESS);
}