//====================================
//
// �p�����[�^���� [ parameter.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once 

//******************************
// �p�����[�^�[�N���X���`
//******************************
class CParameter
{
public:
	CParameter();
	~CParameter();

	void SetHp(int nHp) { m_nHp = nHp; }
	void SetMaxHp(int nMaxHp) { m_nMaxHp = nMaxHp; }
	void AddHp(int nValue) { m_nHp += nValue; }

	int GetHp()const { return m_nHp; }
	int GetMaxHp() const { return m_nMaxHp; }

private:
	int m_nHp; // �̗�
	int m_nMaxHp; // �ő�̗�
};