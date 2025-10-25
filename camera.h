//=====================================
//
// カメラ処理 [ camera.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードガード
//**********************
#pragma once 

//**********************
// 前方宣言
//**********************
class CInputMouse;

//**********************
// カメラクラスを定義
//**********************
class CCamera
{
public:
	//**********************
	// カメラモード列挙型
	//**********************
	enum MODE
	{
		MODE_NONE,
		MODE_MOUSE,
		MODE_SHAKE,
		MODE_EVENT,
		MODE_MAX
	};

	CCamera();
	~CCamera();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	void MouseView(CInputMouse* pMouse);
	void AnimCamera(void);
	void UpdateAnimCamera(void);
	void UpdateShake(void);
	void Load(int nIdx);
	void Save(void);

	// セッター
	void StartEventCamera(const D3DXVECTOR3& targetV, const D3DXVECTOR3& targetR, int endFrame);
	void SetCameraMode(int nMode) { m_pCamera.nMode = nMode; }
	void SetLoadPass(int nIdxPass) { m_nFileIdx = nIdxPass; }
	void SetAnim(bool isFlags) { m_isAnimTime = isFlags; }
	void SetRot(D3DXVECTOR3 rot) { m_pCamera.rot = rot; }

	// ゲッター
	D3DXVECTOR3 GetRot(void) { return m_pCamera.rot; }
	D3DXVECTOR3 GetPos(void) { return m_pCamera.posV; }
	D3DXVECTOR3 GetPosR(void) { return m_pCamera.posR; }
	D3DXMATRIX GetMtxProjection(void) { return m_pCamera.mtxprojection; }
	int GetMode(void) { return m_pCamera.nMode; }
	bool GetShake(void) { return m_isShake; }
	bool GetAnim(void) { return m_isAnimTime; }

private:

	// 定数宣言
	static constexpr int NUMKEY = 10;
	static constexpr int ANIMFILENUM = 1;

	//*************************
	// イベントフレーム構造体
	//*************************
	struct EventData
	{
		bool isActive;		// イベント実行中か
		int	 frame;			// 経過フレーム
		int	 endFrame;		// 終了フレーム
		D3DXVECTOR3 startPosV;		// 開始視点
		D3DXVECTOR3 startPosR;		// 開始注視点
		D3DXVECTOR3 targetPosV;		// 目標視点
		D3DXVECTOR3 targetPosR;		// 目標注視点
	};

	//********************************
	// カメラアニメーションキー構造体
	//********************************
	struct AnimDataKey
	{
		float fPosVX;	// 視点X
		float fPosVY;	// 視点Y
		float fPosVZ;	// 視点Z

		float fPosRX;	// 注視点X
		float fPosRY;	// 注視点Y
		float fPosRZ;	// 注視点Z

		float fRotX;	// 向きX
		float fRotY;	// 向きY
		float fRotZ;	// 向きZ
		int nAnimFrame; // アニメーションのフレーム
		float fDistance;// カメラの距離
	};

	//**********************************
	// カメラアニメーションデータ構造体
	//**********************************
	struct AnimData
	{
		AnimDataKey KeyInfo[NUMKEY];	// 構造体
		int nNumKey; // キーの最大数
		bool isLoop;	// ループするかどうか
	};

	//*************************
	// カメラ構造体を定義
	//*************************
	struct Camera
	{
		D3DXMATRIX mtxprojection;	// プロジェクションマトリックス
		D3DXMATRIX mtxView;			// ビューマトリックス
		D3DXVECTOR3 posV, posR;		// 視点,注視点座標
		D3DXVECTOR3 rot;			// 角度
		D3DXVECTOR3 vecU;			// 法線ベクトル
		D3DXVECTOR3 posRDest;		// 目的座標
		float fDistance;			// カメラの距離
		int nMode;					// カメラのモード
		int nUseKey;				// アニメーション使用時に読み取るキー数
		int nCntAnim;				// カウント
		AnimData m_AnimData;	// アニメーションデータ
	};

	EventData m_event;		// イベント用データ
	Camera m_pCamera;		// カメラ構造体変数

	int m_nShakeTime;		// 振動時間
	int m_nAnimNowKey;		// 現在キーNo
	int m_nFileIdx;			// ファイルインデックス
	int m_nAnimShakeFlame;	// アニメーション振動フレーム

	bool m_isShake;			// 振動するかどうか
	bool m_isAnimTime;		// アニメーション中かどうか
	bool m_isLoad;			// 読み込んだかどうか
	bool m_isCreate;		// 生成されたか
};