//====================================
//
// X�t�@�C������ [ objectX.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "objectX.h"
#include "manager.h"
#include "xfilemanager.h"
#include "texture.h"

//=============================
// �R���X�g���N�^
//=============================
CObjectX::CObjectX(int nPriority) : CObject(nPriority),
m_mtxWorld{},
m_pos(VECTOR3_NULL),
m_rot(VECTOR3_NULL),
m_Scale(INITSCALE),
m_isShadow(false),
m_nIdxModel(-1)
{
	// �l�̃N���A
}
//=============================
// �f�X�g���N�^
//=============================
CObjectX::~CObjectX()
{
	// ����
}
//=============================
// ����������
//=============================
HRESULT CObjectX::Init(void)
{
	// ���ʂ�Ԃ�
	return S_OK;
}
//=============================
// �I������
//=============================
void CObjectX::Uninit(void)
{
	// �I�u�W�F�N�g���g�̔j��
	CObject::Release();
}
//=============================
// �X�V����
//=============================
void CObjectX::Update(void)
{
	// ����
}
//=============================
// �`�揈��
//=============================
void CObjectX::Draw(void)
{
	if (m_nIdxModel == -1)
		return;

	// �t�@�C���}�l�[�W���[�擾
	CXfileManager* pXMgr = CManager::GetInstance()->GetXManager();
	if (!pXMgr) return;

	// �z����
	auto& fileData = pXMgr->GetList();
	if (m_nIdxModel >= static_cast<int>(fileData.size())) return;

	// �z��
	auto& model = fileData[m_nIdxModel];
	if (!model.pMesh) return;

	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �v�Z�p�̃}�g���b�N�X��錾
	D3DXMATRIX mtxScale,mtxRot, mtxTrans;

	// ���݂̃}�e���A����ۑ�
	D3DMATERIAL9 matDef;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �g�嗦�𔽉f
	D3DXMatrixScaling(&mtxScale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	
	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�g���b�N�X�̎擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A�����擾�ł�����
	if (model.pBuffMat)
	{
		// �}�e���A���f�[�^�̃|�C���^
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)model.pBuffMat->GetBufferPointer();

		// �e�N�X�`���擾
		CTexture* pTex = CManager::GetInstance()->GetTexture();

		for (int nCnt = 0; nCnt < model.dwNumMat; nCnt++)
		{
			// �}�e���A���̃Z�b�g
			pDevice->SetMaterial(&pMat[nCnt].MatD3D);

			// �e�N�X�`���擾
			int texIdx = model.pTexture[nCnt];

			// �e�N�X�`���Z�b�g
			pDevice->SetTexture(0, (texIdx >= 0) ? pTex->GetAddress(texIdx) : nullptr);

			// ���f���̕`��
			model.pMesh->DrawSubset(nCnt);
		}
	}

	// �}�e���A����߂�
	pDevice->SetMaterial(&matDef);

	// �}�g���b�N�X�V���h�E�`��
	if (m_isShadow)
	{
		DrawShadow();
	}
}
//=============================
// �}�g���b�N�X�V���h�E�`��
//=============================
void CObjectX::DrawShadow(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	if (!pDevice) return;

	// X�t�@�C���}�l�[�W���[�擾
	CXfileManager* pXMgr = CManager::GetInstance()->GetXManager();
	if (!pXMgr) return;

	// �z����̎擾
	auto& fileData = pXMgr->GetList();
	if (m_nIdxModel < NULL || m_nIdxModel >= static_cast<int>(fileData.size())) return;

	// ���f���v�f���擾
	auto& model = fileData[m_nIdxModel];
	if (!model.pMesh) return;

	// ���C�g����
	D3DXVECTOR4 lightDir(-0.37f, -0.7f, 0.1f, 0.0f);

	// ���ʓ��e���W��ݒ�
	D3DXPLANE plane;
	D3DXVECTOR3 point = VECTOR3_NULL;
	D3DXVECTOR3 normal = D3DXVECTOR3(0.0f,-1.5f,0.0f);
	D3DXPlaneFromPointNormal(&plane, &point, &normal);

	// �e�}�g���b�N�X����
	D3DXMATRIX mtxShadow;
	D3DXMatrixShadow(&mtxShadow, &lightDir, &plane);

	// �e�����f���̈ʒu�ɍ��킹��
	D3DXMATRIX mtxWorldShadow;
	D3DXMatrixMultiply(&mtxWorldShadow, &m_mtxWorld, &mtxShadow);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorldShadow);

	// �������ɐݒ�
	D3DMATERIAL9 shadowMat = {};
	shadowMat.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.25f);
	shadowMat.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.25f);

	// �}�e���A���Z�b�g
	pDevice->SetMaterial(&shadowMat);

	// ���b�V���`��
	for (int nCnt = 0; nCnt < model.dwNumMat; nCnt++)
	{
		model.pMesh->DrawSubset(nCnt);
	}

	// �}�e���A����߂�
	pDevice->SetMaterial(&shadowMat);
}
//=============================
// �V�K���f���o�^
//=============================
void CObjectX::SetFilePass(const char* pFilePass)
{
	// �}�l�[�W���[�擾
	CXfileManager* pXMgr = CManager::GetInstance()->GetXManager();

	if (pXMgr != nullptr)
	{
		// �p�X�A��
		std::string ModelName = "data/MODEL/";
		ModelName += pFilePass;

		// ���f����o�^
		m_nIdxModel = pXMgr->Register(ModelName.c_str());
	}
}
//=============================
// ��������
//=============================
CObjectX* CObjectX::Create(int nIdx,D3DXVECTOR3 pos)
{
	// �C���X�^���X����
	CObjectX* pObjX = new CObjectX;
	if (pObjX == nullptr) return nullptr;

	pObjX->m_pos = pos;
	pObjX->m_nIdxModel = nIdx;

	// ����������
	if (FAILED(pObjX->Init()))
	{
		// �j��
		delete pObjX;

		// nullptr���
		pObjX = nullptr;

		// nullptr��Ԃ�
		return nullptr;
	}

	// �|�C���^��Ԃ�
	return pObjX;
}