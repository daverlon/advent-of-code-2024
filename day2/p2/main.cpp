#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

ostream & operator<< (ostream & os, vector<int> v) {
  for (auto & i : v) {
    os << i << ",";
  }
  return os;
}

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

bool check(int curr, int next, bool ascending) {
  int delta = next - curr;

  if (ascending) {
    if (delta < 1) return false;
    if (delta > 3) return false;
  }
  else {
    if (delta < -3) return false;
    if (delta > -1) return false;
  }

  return true;
}

bool is_safe(const vector<int> & arr) {

  bool ascending = arr[0] < arr[1];
  for (int i = 0; i < arr.size()-1; i++) {
    int curr = arr[i];
    int next = arr[i+1];
    if (!check(curr, next, ascending)) {
      return false;
    }
  }

  return true;
}

bool is_safe2(const vector<int> & arr) {
  if (is_safe(arr)) return true;
  for (int ignore = 0; ignore < arr.size(); ignore++) {
    vector<int> v;
    for (int i = 0; i < arr.size(); i++) {
      if (i != ignore) v.push_back(arr[i]);
    }
    if (is_safe(v)) return true;
  }
  return false;
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
    if (is_safe2(a)) safes++;
  }
  cout << "Safes: " << safes << endl;
  f.close();

  exit(EXIT_SUCCESS);
}
