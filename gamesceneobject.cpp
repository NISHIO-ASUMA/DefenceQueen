//==================================================
//
// �Q�[���̃I�u�W�F�N�g�Ǘ����� [ gameobject.cpp ]
// Author: Asuma Nishio
//
//==================================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "gamesceneobject.h"
#include "ui.h"
#include "player.h"
#include "meshfield.h"

//**********************
// �ÓI�����o�ϐ�
//**********************
CScore* CGameSceneObject::m_pScore = nullptr; // �X�R�A�N���X

//===========================
// �R���X�g���N�^
//===========================
CGameSceneObject::CGameSceneObject()
{
	// �l�̃N���A
}
//===========================
// �f�X�g���N�^
//===========================
CGameSceneObject::~CGameSceneObject()
{
	// ����
}
//===========================
// ����������
//===========================
HRESULT CGameSceneObject::Init(void)
{
	// �v���C���[����
	CPlayer::Create(VECTOR3_NULL, VECTOR3_NULL, 10, "data/MOTION/Player/Player100motion.txt");

	// �X�R�A�N���X����
	m_pScore = CScore::Create(D3DXVECTOR3(600.0f, 200.0f, 0.0f), 60.0f, 40.0f);

	// ���b�V���t�B�[���h����
	CMeshField::Create(VECTOR3_NULL, 3000.0f,3000.0f,1,1);

	return S_OK;
}
//===========================
// �I������
//===========================
void CGameSceneObject::Uninit(void)
{
	// null������
	m_pScore = nullptr;
}
//===========================
// �X�V����
//===========================
void CGameSceneObject::Update(void)
{
	// ����
}