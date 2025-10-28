//=================================================
//
// �e�탍�[�h�����N���X [ load.cpp ]
// Author: Asuma Nishio
//
//=================================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "load.h"
#include <fstream>
#include <iostream>
#include <algorithm>

//=============================
// �R���X�g���N�^
//=============================
CLoad::CLoad()
{
	// �l�̃N���A
}
//=============================
// �f�X�g���N�^
//=============================
CLoad::~CLoad()
{
	// ����
}
//=====================================
// ��̃o�C�i�����l�f�[�^�������o��
//=====================================
void CLoad::SaveInt(const char* savefilename, const int OutputData)
{
	// �����o���t�@�C�����J��
	std::ofstream Openfile(savefilename, std::ios::binary);
	if (!Openfile)
	{
		// ��O����
		MessageBox(GetActiveWindow(), "�����o�����s", "�t�@�C����������܂���( SaveInt )", MB_OK);
		return;
	}

	// ���l�������o��
	Openfile.write(reinterpret_cast<const char*>(&OutputData), sizeof(int));

	// �t�@�C�������
	Openfile.close();
}
//=================================
// �z��̃o�C�i���f�[�^�������o��
//=================================
void CLoad::SaveIntToArray(const char* savefilename, const std::vector<int>& ArrayData)
{
	// �����o���t�@�C�����J��
	std::ofstream Openfile(savefilename, std::ios::binary);
	if (!Openfile)
	{
		// ��O����
		MessageBox(GetActiveWindow(), "�����o�����s", "�t�@�C����������܂���( SaveIntToArray )", MB_OK);
		return;
	}

	// �\�[�g�p�Ɉꎞ�ۑ�
	std::vector<int> SortData = ArrayData;

	// �~���Ƀ\�[�g
	std::sort(SortData.begin(), SortData.end(), std::greater<int>());

	// �v�f���������o��
	int nNumData = static_cast<int>(ArrayData.size());
	Openfile.write((const char*)(&nNumData), sizeof(int));

	// �z��f�[�^���o�C�i���`���ŏ����o��
	Openfile.write((const char*)(ArrayData.data()), sizeof(int) * nNumData);
	
	// �t�@�C�������
	Openfile.close();
}