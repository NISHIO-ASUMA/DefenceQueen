//=================================================
//
// �e�탍�[�h�����N���X [ load.h ]
// Author: Asuma Nishio
//
//=================================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include <vector>

//*************************
// ���[�h�����N���X���`
//*************************
class CLoad
{
public:
	CLoad();
	~CLoad();

	void LoadInt(const char * loadfilename);
	void LoadIntToArray(const char* loadfilename);
	void SaveInt(const char* savefilename, const int OutputData);
	void SaveIntToArray(const char* savefilename, const std::vector<int>& ArrayData);

	static CLoad* Create(void);

private:
};

