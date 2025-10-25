//=====================================
//
// �^�C������ [ time.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once 

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object.h"

//**********************
// �O���錾
//**********************
class CNumber;

//**********************************
// �^�C���N���X���`
//**********************************
class CTime : public CObject
{
public:
	CTime(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CTime();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Save(void);

	int GetAllTime(void) { return m_nAllTime; }
	int GetcurrentTime(void) { return m_nSecond; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }

	static CTime* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
	void Second(void);
	void Minute(void);

	static constexpr int DIGIT_TIME = 2;	// ����
	static constexpr int NUMTIME = 150;	// �ő�^�C�}�[
	static constexpr int CARVETIME = 60;	// �J�E���g���
	static constexpr int DIVIDE = 10;	// �������̒l
	static constexpr int REDTIMEZONE = 10; // �Ԃ��_�ł����鎞��
	static inline constexpr float VALUE_WIDTH = 150.0f;

	int m_nAllTime;		// �S�̂̎���
	int m_nSecond;		// ���݂̎��� ( �b )
	int m_nMinute;		// ���ݎ��� (�� )
	int m_nDecTime;		// ���������ԗ�
	int m_nCount;		// ���ԃJ�E���^�[
	float m_fHeight, m_fWidth;	// ����,����

	CNumber* m_pNumberMinute[DIGIT_TIME];	// ��
	CNumber* m_pNumberSecond[DIGIT_TIME];	// �b

	D3DXVECTOR3 m_pos;		// ���W
};
