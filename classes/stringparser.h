#ifndef _string_parser_base_for_tokenize_a_long_string_into_tokens_by_delimeter_2017_05
#define _string_parser_base_for_tokenize_a_long_string_into_tokens_by_delimeter_2017_05

#include <string>

using namespace std;

class StringParser
{
protected:

	string& _buf;
	string _tmpbuf;
	
	size_t _cpos;

public:
	StringParser(string& buf):_buf(buf), _cpos(0){}
	StringParser():_buf(_tmpbuf), _cpos(0){}
		
	size_t FindNextEmbrace(const string& lb, const string& rb, string& embrace, bool advCursor = false);

	virtual ~StringParser(){}
};

#endif
