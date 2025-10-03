#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void get_numbers(const string & line, array<int, 2> & out) {
  array<string, 2> s;
  int n = 0;
  for (auto & c : line) {
    if (c != ' ') {
      s[n].push_back(c);
    }
    else {
      if (n == 0) n = 1;
    }
  } 
  out[0] = stoi(s[0]);
  out[1] = stoi(s[1]);
}

int calculate_similarity(vector<int> & arr1, vector<int> & arr2) {
  int sim = 0;
  int l1 = arr1.size();
  int l2 = arr2.size();

  for (int i = 0; i < l1; i++) {
    int apps = 0;
    int n1 = arr1[i];
    for (int j = 0; j < l2; j++) {
      if (arr2[j] == n1)
        apps++;
    }
    sim += n1 * apps;
  }

  return sim;
}

int main(int argc, char* argv[]) {

  if (argc != 2) {
    cout << "Usage: " << argv[0] << " <file>" << endl; 
    exit(EXIT_FAILURE);
  }

  cout << "Using input file: " << argv[1] << endl;

  fstream f(argv[1]);
  cout << argv[1] << endl;

  vector<int> arr1;
  vector<int> arr2;
  string line;
  while (getline(f, line)) {
    array<int, 2> Ns;
    get_numbers(line, Ns);
    arr1.push_back(Ns[0]);
    arr2.push_back(Ns[1]);
  }
  sort(arr1.begin(), arr1.end(), greater<int>());
  sort(arr2.begin(), arr2.end(), greater<int>());

  cout << "Similarity: " << calculate_similarity(arr1, arr2) << endl;

  f.close();

  exit(EXIT_SUCCESS);
}
