#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

bool digits(string s)
{
    if (s.empty() || s.size() > 3) return false;
	for (auto &c : s)
	{
		if (!isdigit(c))
			return false;
	}
	return true;
}

int parse2(string sub)
{
	size_t fb = sub.find("(");
	size_t lb = sub.find(")");
	size_t c = sub.find(',');
	if (fb == string::npos 
		|| lb == string::npos 
		|| c == string::npos)
	{
		cout << "failed" << endl;
		return 0;
	}

	string a = sub.substr(fb + 1, c - (fb + 1));
	string b = sub.substr(c + 1, lb - (c + 1));

    if (!digits(a) || !digits(b)) return 0;


	return stoi(a) * stoi(b);
}

int parse(string line, bool * enable) {
    int total = 0;
    size_t pos = line.find("mul");
    while (pos != string::npos) {
        size_t fb = line.find("(", pos);
        size_t comma = line.find(",", fb);
        size_t lb = line.find(")", comma);

        if (fb != string::npos 
        	&& comma != string::npos 
        	&& lb != string::npos 
        	&& pos + 3 == fb)
        {
            string sub = line.substr(pos, lb - pos + 1);
            int mul = parse2(sub) * int(*enable);
            total += mul;
        }

        size_t p  = line.find("mul", pos + 1);
        size_t p1 = line.find("do()", pos + 1);
        size_t p2 = line.find("don't()", pos + 1);
        if (p1 < p || p2 < p) {
        	*enable = p1 < p2;
        }
        pos = p;
    }
    return total;
}

int main(int argc, char *argv[])
{

	if (argc != 2)
	{
		cout << "Usage: " << argv[0] << " <file>" << endl;
		exit(EXIT_FAILURE);
	}

	ifstream f(argv[1]);

	int total = 0;
	bool enabled = true;
	string line;
	while (getline(f, line))
	{
		total += parse(line, &enabled);
	}

	cout << "Total: " << total << endl;

	f.close();
	exit(EXIT_SUCCESS);
}
