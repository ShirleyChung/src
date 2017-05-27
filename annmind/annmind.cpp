#include "annmind.h"
#include <iostream>

extern "C" IModule* GetModule()
{
	return AnnMindSingleton::GetInstance();
}

AnnMind::AnnMind()
{
	_name = "ANN";
	_desc = "Artifical Neural Network prac.";
	
	AddFunc("anntrain", &AnnMind::Trainning);
}

AnnMind::~AnnMind()
{
}

void AnnMind::Trainning(STRARR& cmd)
{
	cout<<"trainning not implement yet.\n";
}

