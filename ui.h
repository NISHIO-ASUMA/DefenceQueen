//====================================
//
// UI���� [ ui.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once 

//****************************
// �C���N���[�h�t�@�C���錾
//****************************
#include "object2D.h"

//****************************
// UI�N���X���`
//****************************
class CUi : public CObject2D
{
public:

	CUi(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CUi();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CUi* Create(D3DXVECTOR3 pos, int nFlashFrame,float fWidth, float fHeight,const char * Filename,bool isUse);

private:

	int m_nFlashFrame;		// �_�ŊԊu
	bool m_isFlash;			// �_�ł��邩�ǂ���
};