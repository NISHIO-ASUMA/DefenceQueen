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
	virtual ~CSceneManagement();

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

private:

};