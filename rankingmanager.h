//==========================================
//
// �����L���O�Ǘ����� [ rankingmanager.h ]
// Author: Asuma Nishio
//
//==========================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once 

//******************************
// �C���N���[�h�t�@�C��
//******************************
#include "scenemanagebase.h"

//******************************
// �����L���O�Ǘ��N���X���`
//******************************
class CRankingManager : public CSceneManageBase
{
public:
	CRankingManager();
	~CRankingManager();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

};