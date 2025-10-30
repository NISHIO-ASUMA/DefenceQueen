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

//**************************
// �O���錾
//**************************
class CResultScore;

//**************************
// �C���N���[�h�t�@�C��
//**************************
#include <memory>

//**************************
// ���U���g�Ǘ��N���X���`
//**************************
class CResultManager
{
public:

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Load(void);

	// �C���X�^���X�擾
	static CResultManager* GetInstance(void)
	{
		// �C���X�^���X��Ԃ�
		static CResultManager pResultManager;
		return &pResultManager;
	}

private:

	CResultManager();
	~CResultManager();

	static constexpr int SCORELISTNUM = 3; // �ő吔

	bool m_isKeyDown; // �L�[���̓t���O
	int m_nGameScore; // �X�R�A���i�[
	int m_nLastTime; // ���Ԃ��i�[

	CResultScore* m_pResultScore[SCORELISTNUM];	// �X�R�A�|�C���^
};