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
// �O���錾
//******************************
class CResultScore;

//******************************
// �����L���O�Ǘ��N���X���`
//******************************
class CRankingManager
{
public:
	CRankingManager();
	~CRankingManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:

};