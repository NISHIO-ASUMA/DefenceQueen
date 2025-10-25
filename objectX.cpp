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
CObjectX::CObjectX(int nPriority) : CObject(nPriority)
{
	// �l�̃N���A
	m_mtxWorld = {};
	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_nIdxModel = -1; 
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
	if (m_nIdxModel >= fileData.size()) return;

	// �z��
	auto& model = fileData[m_nIdxModel];
	if (!model.pMesh) return;

	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �v�Z�p�̃}�g���b�N�X��錾
	D3DXMATRIX mtxRot, mtxTrans;

	// ���݂̃}�e���A����ۑ�
	D3DMATERIAL9 matDef;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

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
		// �|�C���^
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
