//=============================================================================
//
// �e�V�[�����ƂɎg��Manager�N���X���ꊇ�Ǘ����鏈�� [ scenemanagement.h ]
// Author: Asuma Nishio
//
//=============================================================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once

//*************************************
// �}�l�[�W���[���Ǘ�����N���X���`
//*************************************
class CSceneManagement
{
public:

	CSceneManagement();
	~CSceneManagement();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

};