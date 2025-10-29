//=============================================================================
//
// �V�[���x�[�X�N���X [ scenemanagebase.h ]
// Author: Asuma Nishio
//
//=============================================================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once

//************************
// �Ǘ��x�[�X�N���X���`
//************************
class CSceneManageBase
{
public:

	CSceneManageBase() {};
	virtual ~CSceneManageBase() {}
	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};

