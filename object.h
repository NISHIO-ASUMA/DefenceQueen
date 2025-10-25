//====================================
//
// �I�u�W�F�N�g���� [ object.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once 

//***************************
// �I�u�W�F�N�g�N���X���`
//***************************
class CObject
{
public:
	//*************************
	// �I�u�W�F�N�g�̎�ޒ�`
	//*************************
	enum TYPE
	{
		TYPE_NONE,
		TYPE_PLAYER,
		TYPE_MESH,
		TYPE_BULLET,
		TYPE_BOSS,
		TYPE_ENEMY,
		TYPE_BLOCK,
		TYPE_COLLBLOCK,
		TYPE_PAUSE,
		TYPE_BARRIER,
		TYPE_ITEM,
		TYPE_RUBBLE,
		TYPE_PILER,
		TYPE_POINT,
		TYPE_MAX
	};

	//*************************
	// �`��ԍ���`
	//*************************
	enum PRIORITY
	{
		NONE,		// �������
		MESH,		// ���b�V��
		BASENUMBER, // ��ԍ�
		MODELOBJECT,// ���f��
		BULLET,		// �e
		SHADOW,		// �e
		IMPACT,		// �Ռ��g
		CHARACTOR,	// �v���C���[
		BILLBOARD,	// �r���{�[�h
		EFFECT,		// �G�t�F�N�g
		UI,			// 2DUI
		PAUSE,		// �|�[�Y
		PRIORITY_MAX // �ő吔
	};

	CObject(int nPriority = NONE);
	virtual ~CObject();

	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);
	static CObject* GetTop(int nPriority) { return m_pTop[nPriority]; }
	static int GetNumAll(void) { return m_nNumAll; }

	void SetObjType(TYPE type) { m_Type = type; }

	TYPE GetObjType(void) { return m_Type; }
	CObject* GetNext(void) { return m_pNext; }

protected:
	void Release(void); // ���

private:
	static int m_nNumAll;	// �����Ǘ�
	int m_nID;				// �������g��ID
	TYPE m_Type;			// �I�u�W�F�N�g�̎�ޕϐ�
	int m_nPriority;		// �D�揇�ʔԍ�

	static CObject* m_pTop[PRIORITY_MAX];	// �擪�I�u�W�F�N�g
	static CObject* m_pCur[PRIORITY_MAX];	// �Ō���I�u�W�F�N�g

	CObject* m_pNext;		// ���̃I�u�W�F�N�g�̃|�C���^
	CObject* m_pPrev;		// �O�̃I�u�W�F�N�g�̃|�C���^

	bool m_isDeath;			// ���S�t���O
};