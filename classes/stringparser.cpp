#include "stringparser.h"

/* FindNextEmbrace:
	從緩衝區中找到括號內的字串. 若重覆找到左括號代表文件格式錯誤.
	advCursor = true 若找到符合資料則會將指標前進到右括號後.
*/
size_t StringParser::FindNextEmbrace(const string& lb, const string& rb, string& embrace, bool advCursor)
{
	size_t cpos = _cpos;
	for( ; cpos < _buf.size(); ++cpos )
		if ( 0 == _buf.compare( cpos, lb.size(), lb ) ) // found rb
			break;
	
	cpos += lb.size();
	size_t spos = cpos; // save start pos to retrieve the embrace content
	for( ; cpos < _buf.size(); ++cpos )
	{
			if ( 0 == _buf.compare( cpos, rb.size(), rb ) )  // fonud rb
			{
				embrace = _buf.substr(spos, cpos - spos);
				if (advCursor) _cpos = cpos + rb.size();
				return cpos + rb.size();
			}
			if ( 0 == _buf.compare( cpos, lb.size(), lb ) ) // error.
				return string::npos;
	}
		
	return string::npos;
}
