//==============================================
//
// ���U���g�V�[���Ǘ����� [ resultmanager.h ]
// Author: Asuma Nishio
// 
//==============================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once 

//******************************
// �C���N���[�h�t�@�C��
//******************************
#include "scenemanagebase.h"

//**************************
// �O���錾
//**************************
class CResultScore;

//**************************
// ���U���g�Ǘ��N���X���`
//**************************
class CResultManager : public CSceneManageBase
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CResultManager();
	~CResultManager();

	// �����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	void Load(void);

private:
	static constexpr int SCORELISTNUM = 3; // �ő吔

	bool m_isKeyDown; // �L�[���̓t���O
	int m_nGameScore; // �X�R�A���i�[
	int m_nLastTime; // ���Ԃ��i�[

	CResultScore* m_pResultScore[SCORELISTNUM];	// �X�R�A�|�C���^
};