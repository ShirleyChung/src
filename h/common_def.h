#ifndef _common_def_for_std_collectons_abbrev_2017_03_s
#define _common_def_for_std_collectons_abbrev_2017_03_s

#include <map>
#include <list>
#include <vector>

using namespace std;

typedef const vector<string> STRARR;

typedef void (*cmd_handler)(STRARR&);

typedef list<cmd_handler> CMDCBLIST;

typedef map<string,string> STRMAP;

#endif