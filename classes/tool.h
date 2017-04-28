#ifndef tool_sets_such_as_strings_tokenize_etc_2017_
#define tool_sets_such_as_strings_tokenize_etc_2017_

#include <string>
#include <vector>

using namespace std;

vector<string> Tokenize(const string&);
vector<string> Tokenize(const string&, const string& sep);
string Tokencombine(const vector<string>&);
string Tokencombine(const vector<string>&, const string& sep);

string& rtrim(string& s, const string& sep);

bool CheckDirExist(const string& fn);
bool CheckFileExist(const string& fn);

#endif
