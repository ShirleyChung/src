#include "../classes/console.h"

int main(int argc)
{
	try{
		Console con;
		cin<<"test 123 456\n";
		con.Prompt();
		return 0;
	}
	catch(...)
	{
		return -1;
	}
}
