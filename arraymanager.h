//===============================================
//
// ���ԃN���X�S�̂̊Ǘ����� [ arraymanager.h ]
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
#include <list>

//**********************
// �O���錾
//**********************
class CArray;

//***************************************
// ���ԑS�̂��Ǘ�����N���X���`
//***************************************
class CArrayManager
{
public:

	CArrayManager();
	~CArrayManager();

	HRESULT Init(const int nActives);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetUseArray(void) { return m_nActiveAll; }

	/// <summary>
	/// ���Ԃ��o��������֐�
	/// </summary>
	/// <param name="pos">�o�����W</param>
	/// <param name="rot">�o�����̊p�x</param>
	/// <param name="nLife">�̗͒l</param>
	/// <returns></returns>
	void Spawn(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, int nLife,const int nNumSpawn);

	/// <summary>
	/// �z��̗v�f�����擾����
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	int GetAll(void) { return static_cast<int>(m_pArrays.size()); }

	/// <summary>
	/// �z��̗v�f�ԍ�����擾
	/// </summary>
	/// <param name="nIdx">�擾�������ԍ�</param>
	/// <returns></returns>
	CArray* GetArrays(const int nIdx) { return m_pArrays[nIdx]; }

	/// <summary>
	/// �S�̂��擾����
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	std::vector<CArray*>& GetArray(void) { return m_pArrays; }

private:
	std::vector<CArray*>m_pArrays; // ���I�z��
	int m_nActiveAll;		// ���݂̏o����
};