//=====================================
//
// �V�[������ [ scene.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once 

//******************************
// �V�[���N���X���`
//******************************
class CScene 
{
public:
	//*************************
	// �V�[���̎�ޗ񋓌^
	//*************************
	enum MODE
	{
		MODE_NONE,		// ��������
		MODE_TITLE,		// �^�C�g��
		MODE_TUTORIAL,	// �`���[�g���A��
		MODE_GAME,		// �Q�[��
		MODE_RESULT,	// ���U���g
		MODE_LOSERESULT,// ���s���U���g
		MODE_RANKING,	// �����L���O
		MODE_MAX
	};

	CScene(MODE mode);
	virtual ~CScene();

	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	MODE GetScene(void) const { return m_Scene; }

private:

	MODE m_Scene;	// �V�[���Ǘ��ϐ�
};