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
// �����L���O�Ǘ��N���X���`
//******************************
class CRankingManager
{
public:
	
	~CRankingManager();

	HRESULT Init(void);
	void Update(void);
	void Uninit(void);
	void Draw(void);

	// �C���X�^���X�擾
	static CRankingManager* GetInstance(void);

private:

	CRankingManager();

};