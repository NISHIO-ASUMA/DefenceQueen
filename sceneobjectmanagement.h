//===========================================================================================
//
// �e�V�[�����Ƃŏo������ObjectManager�N���X���ꊇ�Ǘ����鏈�� [ sceneobjectmanagement.h ]
// Author: Asuma Nishio
//
//===========================================================================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once

//*************************************************
// �I�u�W�F�N�g�}�l�[�W���[���Ǘ�����N���X���`
//*************************************************
class CSceneObjectManagement
{
public:

	CSceneObjectManagement();
	~CSceneObjectManagement();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

};