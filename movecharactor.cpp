//==================================================
//
// �����L�����N�^�[�N���X���� [ movecharactor.cpp ]
// Author: Asuma Nishio
//
//==================================================

//************************
// �C���N���[�h�t�@�C��
//************************
#include "movecharactor.h"
#include "model.h"
#include "shadowS.h"
#include "manager.h"

//======================================
// �R���X�g���N�^
//======================================
CMoveCharactor::CMoveCharactor(int nPriority) : CObject(nPriority),
m_pos(VECTOR3_NULL),
m_posOld(VECTOR3_NULL),
m_move(VECTOR3_NULL),
m_rot(VECTOR3_NULL),
m_rotDest(VECTOR3_NULL),
m_scale(INITSCALE),
m_type(TYPE_NONE),
m_pModel{},
m_pMotion{},
m_pShadowS{},
m_fMoveValue(NULL)
{
	// �l�̃N���A
	D3DXMatrixIdentity(&m_mtxworld);
}
//======================================
// �f�X�g���N�^
//======================================
CMoveCharactor::~CMoveCharactor()
{

}
//======================================
// ����������
//======================================
HRESULT CMoveCharactor::Init(void)
{
	// �ϐ��̏�����
	m_pModel.clear();

	// ���f������
	m_pShadowS = CShadowS::Create(m_pos, m_rot);

	return S_OK;
}
//======================================
// �I������
//======================================
void CMoveCharactor::Uninit(void)
{
	// ���I�m�ە��̃��f���̔j��
	for (auto iter = m_pModel.begin(); iter != m_pModel.end(); iter++)
	{
		// null�`�F�b�N
		if ((*iter) != nullptr)
		{
			// �I������
			(*iter)->Uninit();

			// �|�C���^�̔j��
			delete (*iter);

			// null������
			(*iter) = nullptr;
		}
	}

	// �z��̃N���A
	m_pModel.clear();

	// �|�C���^�j��
	m_pMotion.reset();
	
	// ���g�̔j��
	CObject::Release();
}
//======================================
// �X�V����
//======================================
void CMoveCharactor::Update(void)
{
	//// �ʒu�ۑ�
	//m_posOld = m_pos;

	//// ���W���X�V����
	//m_pos += m_move;

	// �ړ��ʂ̌���
	m_move.x += (0.0f - m_move.x) * 0.75f;
	m_move.z += (0.0f - m_move.z) * 0.75f;

	// �p�x�⊮
	if (m_rotDest.y - m_rot.y > D3DX_PI)
	{// ����]
		// �p�x
		m_rot.y = m_rot.y + D3DX_PI * 2.0f;
	}
	else if (m_rot.y - m_rotDest.y > D3DX_PI)
	{// �E��]
		// �p�x
		m_rot.y = m_rot.y - D3DX_PI * 2.0f;
	}

	// ���݂̊p�x
	m_rot.y += (m_rotDest.y - m_rot.y) * 0.25f;

	// �X�e���V���V���h�E�̍X�V
	if (m_pShadowS)
	{
		// �I�u�W�F�N�g�ݒ�
		m_pShadowS->SetPos(m_pos);
		m_pShadowS->SetRot(m_rot);
	}

	// ���[�V�����̍X�V����
	m_pMotion->Update(m_pModel,m_pModel.size());
}
//======================================
// �`�揈��
//======================================
void CMoveCharactor::Draw(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �v�Z�p�̃}�g���b�N�X��錾
	D3DXMATRIX mtxRot, mtxTrans, mtxScal;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxworld);

	// �傫���𔽉f
	D3DXMatrixScaling(&mtxScal, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxScal);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

	// ���f���̕`��
	for (auto& model : m_pModel)
	{
		model->Draw();
	}
}
//======================================
// �ʒu���̍X�V
//======================================
void CMoveCharactor::UpdatePosition(void)
{
	// �ʒu�̍X�V
	m_posOld = m_pos;
	m_pos += m_move;
}
//======================================
// ���[�V�������[�h����
//======================================
void CMoveCharactor::MotionLoad(const char* pScriptName, int nDestMotions)
{
	// �|�C���^����
	m_pMotion = CMotion::Load(pScriptName, m_pModel, nDestMotions);
}