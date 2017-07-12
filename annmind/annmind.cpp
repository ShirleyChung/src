#include "annmind.h"
#include <iostream>

extern "C" IModule* GetModule()
{
	return AnnMindSingleton::GetInstance();
}

/* 模組初始化 */
AnnMind::AnnMind()
{
	_name = "ANN";
	_desc = "Artifical Neural Network prac.";
	
	AddFunc("anntrain", &AnnMind::Trainning);
}

AnnMind::~AnnMind()
{
}

/* 輸入訓練資料 */
void AnnMind::Trainning(STRARR& cmd)
{
	cout<<"trainning not implement yet.\n";
}

