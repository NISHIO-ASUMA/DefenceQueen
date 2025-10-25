//==========================================
//
// �����L���O�X�R�A���� [ rankingscore.h ]
// Author: Asuma Nishio
//
//==========================================

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

//******************************
// �����L���O�X�R�A�N���X��`
//******************************
class CRankingScore : public CObject
{
public:
	CRankingScore(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CRankingScore();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Load(void);

	void SetTexture(void);

	static CRankingScore* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
	static void SetRankInScoreIdx(int nIdxScore) { m_nNewRankingScore = nIdxScore; }

private:
	static constexpr int RANKSCOREDIGIT = 6; // �\������
	static constexpr int RANKING_MAX = 5;	// �����L���O��

	static int m_nNewRankingScore;	// ���ʂɓ����Ă��邩�ǂ���

	int m_nIdxTex;					// �e�N�X�`���C���f�b�N�X
	int m_aRankScore[RANKING_MAX];	// �X�R�A�z��
	CNumber* m_apNumber[RANKING_MAX][RANKSCOREDIGIT]; // �e�X�R�A�ƌ���

	D3DXVECTOR3 m_pos;		// ���W
	float m_fWidth;			// ����
	float m_fHeight;		// ����
};