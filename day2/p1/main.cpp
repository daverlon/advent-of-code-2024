#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

void get_numbers(const string & line, vector<int> & nums) {
  string buf = "";
  for (auto & c : line) {
    if (c == ' ') {
      nums.push_back(stoi(buf));
      buf = "";
    } 
    else {
      buf += c;
    }
  }
  nums.push_back(stoi(buf));
}

bool is_safe(const vector<int> & arr) {

  bool ascending = arr[0] < arr[1];
  for (int i = 0; i < arr.size()-1; i++) {
    
    int curr = arr[i];
    int next = arr[i+1];

    int delta = next - curr;
    
    if (ascending) {
      if (delta < 1) return false;
      if (delta > 3) return false;
    }
    else {
      if (delta < -3) return false;
      if (delta > -1) return false;
    }
  }

  return true;
}

int main(int argc, char* argv[]) {

  if (argc != 2) {
    cout << "Usage " << argv[0] << " <file>" << endl;
    exit(EXIT_FAILURE);
  }

  fstream f(argv[1]);  
  string line;

  int safes = 0;

  while (getline(f, line)) {
    vector<int> a;
    get_numbers(line, a);
    if (is_safe(a)) safes++;
    
    if (1) {
      for (int j = 0; j < a.size(); j++) {
        cout << a[j] << ",";
      }
      cout << (is_safe(a) ? "SAFE" : "UNSAFE");
      cout << endl;
    }
  }
  cout << "Safes: " << safes << endl;
  f.close();

  exit(EXIT_SUCCESS);
}
