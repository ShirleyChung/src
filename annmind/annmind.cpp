#include "annmind.h"
#include <iostream>

extern "C" IModule* GetModule()
{
	return AnnMindSingleton::GetInstance();
}

/* �Ҳժ�l�� */
AnnMind::AnnMind()
{
	_name = "ANN";
	_desc = "Artifical Neural Network prac.";
	
	AddFunc("anntrain", &AnnMind::Trainning);
}

AnnMind::~AnnMind()
{
}

/* ��J�V�m��� */
void AnnMind::Trainning(STRARR& cmd)
{
	cout<<"trainning not implement yet.\n";
}

