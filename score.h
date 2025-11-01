//====================================
//
// �X�R�A���� [ score.h ]
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
#include "number.h"
#include "object.h"
#include <memory>

//**********************
// �O���錾
//**********************
class CLoad;

//*******************************************
// �X�R�A�N���X���`
//*******************************************
class CScore : public CObject
{
public:

	CScore(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CScore();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	D3DXVECTOR3 GetPos(void) { return m_pos; }

	void AddScore(int nValue);
	void DeleteScore(void);
	void SaveScore(void);
	void SetScore(int nDestScore) { m_nScore = nDestScore; }

	static CScore* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

	int GetScore(void) { return m_nScore; }

private: 

	static constexpr int NUM_SCORE = 8; // ����
	static constexpr int NUM_DIGIT = 10; // �\�����镪�������̒l

	CNumber *m_apNumber[NUM_SCORE];	// �������̃i���o�[�̃|�C���^
	D3DXCOLOR m_col;				// �J���[
	D3DXVECTOR3 m_pos;				// ���W
	D3DXVECTOR3 m_rot;				// �p�x
	
	float m_fWidth;					// ����
	float m_fHeight;				// ����
	int m_nScore;			// �X�R�A�ێ��p

	std::unique_ptr< CLoad>m_pLoad; // ���j�[�N�|�C���^
};
