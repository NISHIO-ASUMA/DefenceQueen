//=======================================================
//
// �^�C�g���ŏo������I�u�W�F�N�g���� [ titleobject.h ]
// Author: Asuma Nishio
//
//=======================================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once

//****************************************
// �^�C�g���I�u�W�F�N�g�Ǘ��N���X���`
//****************************************
class CTitleObject
{
public:

	CTitleObject();
	~CTitleObject();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

};