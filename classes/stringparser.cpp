#include "stringparser.h"

/* FindNextEmbrace:
	從緩衝區中找到括號內的字串. 若重覆找到左括號代表文件格式錯誤.
	advCursor = true 若找到符合資料則會將指標前進到右括號後.
*/
size_t StringParser::FindNextEmbrace(const string& lb, const string& rb, string& embrace, bool advCursor)
{
	size_t spos = _cpos;
	for( ; spos < _buf.size(); ++spos )
		if ( 0 == _buf.compare( spos, lb.size(), lb ) ) // found rb
			break;
	
	spos += lb.size();
	size_t epos = spos;
	for( ; spos < _buf.size(); ++spos )
	{
			if ( 0 == _buf.compare( spos, rb.size(), rb ) )  // fonud rb
			{
				embrace = _buf.substr(epos, spos - epos);
				if (advCursor) _cpos = spos + rb.size();
				return spos + rb.size();
			}
			if ( 0 == _buf.compare( spos, lb.size(), lb ) ) // error.
				return string::npos;
	}
		
	return string::npos;
}
