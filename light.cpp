//====================================
//
// ���C�g���� [ light.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "light.h"
#include "manager.h"

//=================================
// �R���X�g���N�^
//=================================
CLight::CLight() : m_aLight{}, m_vecDir{}
{
	// �l�̃N���A
}
//=================================
// �f�X�g���N�^
//=================================
CLight::~CLight()
{
	// ����
}
//=================================
// ���C�g�̏���������
//=================================
HRESULT CLight::Init(void)
{
	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// ���C�g�̃[���N���A����
	ZeroMemory(&m_aLight, sizeof(m_aLight));

	for (auto &light : m_aLight)
	{
		light.Type = D3DLIGHT_DIRECTIONAL;
		light.Diffuse = COLOR_WHITE;
	}

	// ���C�g�̕����ݒ�
	m_vecDir[0] = D3DXVECTOR3(0.25f, -0.84f, -0.23f);
	m_vecDir[1] = D3DXVECTOR3(-0.61f, 0.10f, 0.44f);
	m_vecDir[2] = D3DXVECTOR3(1.0f, -0.52f, 0.21f);

	// ���K������
	for (int nCnt = 0; nCnt < NUMLIGHT; nCnt++)
	{	
		// �x�N�g���̑傫����1�ɂ���
		D3DXVec3Normalize(&m_vecDir[nCnt], &m_vecDir[nCnt]); 

		m_aLight[nCnt].Direction = m_vecDir[nCnt];

		// ���C�g�̐ݒ�
		pDevice->SetLight(nCnt, &m_aLight[nCnt]);

		// ���C�g��L����
		pDevice->LightEnable(nCnt, TRUE);
	}

	return S_OK;
}
//=================================
// ���C�g�̏I������
//=================================
void CLight::Uninit(void)
{
	// ����
}
//=================================
// ���C�g�̍X�V����
//=================================
void CLight::Update(void)
{
	// ����
}