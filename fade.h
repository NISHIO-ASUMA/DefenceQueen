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
	// ��ԗ񋓌^
	//**********************
	enum FADE
	{
		FADE_NONE,	// �����Ȃ�
		FADE_IN,	// �t�F�[�h�C��
		FADE_OUT,	// �t�F�[�h�A�E�g
		FADE_MAX
	};

	CFade();
	~CFade();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	/// <summary>
	/// �V�[����ݒ肷��
	/// </summary>
	/// <param name="pNewScene">�t�F�[�h��̃C���X�^���X</param>
	void SetFade(std::unique_ptr<CScene> pNewScene);

	FADE GetFade(void) { return m_fade; }

private:

	static constexpr float AlphaFade = 0.025f; // �t�F�[�h�ŉ��Z����l

	LPDIRECT3DVERTEXBUFFER9 m_pVtx; // ���_�o�b�t�@
	D3DXCOLOR m_col;				// �|���S���J���[
	FADE m_fade;					// �t�F�[�h�̗񋓌^�ϐ�

	std::unique_ptr<CScene> m_pScene; 	// �V�[���N���X�|�C���^
};
