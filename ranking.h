//=====================================
//
// �����L���O�V�[������ [ ranking.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once 

//******************************
// �C���N���[�h�t�@�C���錾
//******************************
#include "scene.h"

//******************************
// �O���錾
//******************************
class CRankingManager;

//******************************
// �����L���O�V�[���N���X���`
//******************************
class CRanking : public CScene
{
public:

	CRanking();
	~CRanking();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CRanking* Create(void);

private:
};