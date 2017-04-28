#include "chcreater.h"
#include "tool.h"

extern "C" IModule* GetModule()
{
	return Singleton<CharaterCreater>::GetInstance();
}

CharaterCreater::CharaterCreater()
:_working_dir("characters")
{
	_name = "charatercreater";
	CheckDirExist(_working_dir);
	
	AddFunc("newchar", &CharaterCreater::NewCharacter);
	AddFunc("mfchar", &CharaterCreater::ModifyCharacter);
	AddFunc("delchar", &CharaterCreater::DeleteCharacter);

}

CharaterCreater::~CharaterCreater()
{

}

void CharaterCreater::NewCharacter(STRARR& cmd)
{
	cout<<"not impl.\n";
}


void CharaterCreater::ModifyCharacter(STRARR& cmd)
{
	cout<<"not impl.\n";
}

void CharaterCreater::DeleteCharacter(STRARR& cmd)
{
	cout<<"not impl.\n";
}

bool CharaterCreater::CreateFile(const string& fn)
{
	return false;
}
