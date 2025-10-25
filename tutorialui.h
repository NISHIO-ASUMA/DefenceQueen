//=============================================
//
// �`���[�g���A��UI���� [ tutorialui.h ]
// Author: Asuma Nishio
//
//=============================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once 

//******************************
// �C���N���[�h�t�@�C���錾
//******************************
#include "object2D.h"

//******************************
// �`���[�g���A��ui�N���X���`
//******************************
class CTutorialUi : public CObject2D
{
public:
	//***************************
	// �I�u�W�F�N�g�̏��
	//***************************
	enum STATE
	{
		STATE_AWAIT,
		STATE_MOVE,
		STATE_STOP,
		STATE_EXIT,
		STATE_MAX
	};

	CTutorialUi(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CTutorialUi();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetState(int nState) { m_nState = nState; }

	// �Q�b�^�[
	bool IsFinished() const;

	static CTutorialUi* Create(D3DXVECTOR3 pos, float fWidth, float fHeight,const char * pFileName,int nState);

private:
	int m_nState;		// UI�̏��
	float m_fAlpha;		// �����x
};