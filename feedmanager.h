//===============================================
//
// �����̉a���Ǘ����鏈�� [ feedmanager.h ]
// Author: Asuma Nishio
//
//===============================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include <vector>

//**********************
// �O���錾
//**********************
class CFeed;

//***************************
// �a���Ǘ�����N���X���`
//***************************
class CFeedManager
{
public:

	CFeedManager();
	~CFeedManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

};