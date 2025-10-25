//=========================================
//
// �v���C���[�̗͏��� [ playerlifegage.h ]
// Author: Asuma Nishio
//
//=========================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once 

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "gage.h"

//**********************
// �O���錾
//**********************
class CPlayer;
class CObject;

//*************************
// �̗̓Q�[�W�N���X���`
//*************************
class CPlayerLifeGage : public CGage
{
public:
	//**********************
	// �Q�[�W�̎�ޒ�`
	//**********************
	enum GAGE
	{
		GAGE_FRAME,
		GAGE_BAR,
		GAGE_MAX
	};

	CPlayerLifeGage(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CPlayerLifeGage();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetGage(int type) { m_gage = type; }
	void SetShake(bool isFlags) { m_isShake = isFlags; }
	int GetGage(void) const { return m_gage; }
	
	static CPlayerLifeGage* Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int gagetype,const char * pTexName);

private:
	int m_nLifeLength;		// �o�[�̒�����l
	int m_nMaxLifeLength;	// �ŏ��̗̑͒l
	int m_gage;				// �񋓕ϐ�
	int m_nMaxLife;			// �ő厞�̗̑�
	int m_nShakeTimer;		// �U������
	float m_fShakeAmplitude;// �U����
	float m_fShakeOffset;	// �I�t�Z�b�g

	bool m_isShake;			// �U�����邩�ǂ���

	CPlayer* m_pPlayer;		// �v���C���[�N���X�|�C���^
	D3DXVECTOR3 m_basePos;	// ����W
};