//====================================
//
// ���C���Q�[������ [ game.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once

//****************************
// �C���N���[�h�t�@�C���錾
//****************************
#include "scene.h"
#include "pausemanager.h"
#include <memory>

//****************************
// �O���錾
//****************************
class CGameManager;
class CGameSceneObject;
class CGameState;

//****************************
// �Q�[���V�[���N���X���`
//****************************
class CGame : public CScene
{
public:
	//***********************
	// �Q�[����ԗ񋓌^
	//***********************
	enum GAMESTATE
	{
		GAMESTATE_NONE,
		GAMESTATE_NORMAL,
		GAMESTATE_END,
		GAMESTATE_LOSEEND,
		GAMESTATE_MAX
	};

	CGame();
	~CGame();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	CGameManager* GetGameManager(void) { return m_pGameManager.get(); }
	CGameSceneObject* GetGameObject(void) { return m_pGameObject.get(); }
	CGameState* GetState(void) { return m_pState; }

	static CPauseManager* GetPause(void) { return m_pPausemanager; }

private:
	static CPauseManager* m_pPausemanager;			// �|�[�Y�}�l�[�W���[�N���X�|�C���^
	CGameState * m_pState;							// �Q�[���i�s�Ǘ��N���X�̃|�C���^
	std::unique_ptr<CGameManager>m_pGameManager;	// �Q�[���}�l�[�W���[�N���X�̃|�C���^
	std::unique_ptr<CGameSceneObject>m_pGameObject;	// �Q�[�����̃I�u�W�F�N�g�N���X�̃|�C���^

};