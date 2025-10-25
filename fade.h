//=====================================
//
// �t�F�[�h���� [ fade.h ]
// Author: Asuma Nishio
// 
//=====================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include <memory>

//**********************
// �O���錾
//**********************
class CScene;

//**********************
// �t�F�[�h�N���X���`
//**********************
class CFade
{
public:

	//**********************
	// �t�F�[�h��ԗ񋓌^
	//**********************
	enum FADE
	{
		FADE_NONE,	// �����Ȃ�
		FADE_IN,	// �t�F�[�h�C��
		FADE_OUT,	// �t�F�[�h�A�E�g
		FADE_MAX
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CFade();
	~CFade();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ���j�[�N�|�C���^�œn��
	void SetFade(std::unique_ptr<CScene> pNewScene);

	// �Q�b�^�[
	FADE GetFade(void) { return m_fade; }

private:

	static constexpr float AlphaFade = 0.025f; // �t�F�[�h�ŉ��Z����l

	LPDIRECT3DVERTEXBUFFER9 m_pVtx; // ���_�o�b�t�@
	D3DXCOLOR m_col;				// �|���S���J���[
	FADE m_fade;					// �t�F�[�h�̗񋓌^�ϐ�

	// ���L��������
	std::unique_ptr<CScene> m_pScene;
};
