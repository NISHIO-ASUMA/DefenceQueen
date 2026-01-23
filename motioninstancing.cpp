//=========================================================
//
// インスタンシング用モーション処理 [ motioninstancing.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル宣言
//*********************************************************
#include "motioninstancing.h"
#include "template.h"
#include "debugproc.h"
#include "motionmanager.h"
#include "manager.h"
#include "instancemodel.h"

//=========================================================
// コンストラクタ
//=========================================================
CMotionInstancing::CMotionInstancing()
{
	// 値のクリア
	m_nCounterMotion = NULL;
	m_nKey = NULL;
	m_nNumKey = NULL;
	m_motiontype = NULL;
	m_nNextKey = NULL;
	m_nNumModels = NULL;
	m_nAllFrameCount = NULL;
	m_nNumAllFrame = NULL;

	m_motiontypeBlend = NULL;
	m_nFrameBlend = NULL;
	m_nCounterBlend = NULL;
	m_nKeyBlend = NULL;
	m_nNextKeyBlend = NULL;

	m_isLoopMotion = false;
	m_isBlendMotion = false;
	m_isFinishMotion = false;
	m_isFirstMotion = false;
	m_isDirty = false;

	m_nMotionIdx = -1;
	m_ResultData = {};
}
//=========================================================
// デストラクタ
//=========================================================
CMotionInstancing::~CMotionInstancing()
{
	// 無し
}
//=========================================================
// モーション読み込み関数
//=========================================================
std::unique_ptr<CMotionInstancing> CMotionInstancing::Load(const char* pFilename, std::vector<CInstanceModel*>& pModel, int nDestMotions, const bool isShadow)
{
	// モーションのユニークポインタ生成
	auto pMotionInst = std::make_unique<CMotionInstancing>();

	// 登録処理
	pMotionInst->RegisterPath(pFilename, pModel, nDestMotions, isShadow);

	// 生成されたポインタを返す
	return pMotionInst;
}
//=========================================================
// モーションインデックス登録関数
//=========================================================
void CMotionInstancing::RegisterPath(const char* pMotionName, std::vector<CInstanceModel*>& pModel, int nDestMotions, const bool isShadow)
{
	// モーションマネージャーを取得する
	auto MotionManager = CManager::GetInstance()->GetInstMotionM();
	if (MotionManager == nullptr) return;

	// インデックスに登録し,その情報を取得する
	m_nMotionIdx = MotionManager->Register(pMotionName, pModel, nDestMotions, isShadow);
}
//============================================================
// モーションセット
//============================================================
void CMotionInstancing::SetMotion(int motiontype)
{
	// ここはmotiontypeに渡された番号を取得する
	if (m_motiontype == motiontype)
	{
		// 同じだったら
		return;
	}

	// 代入
	m_motiontype = motiontype;
	m_nKey = 0;
	m_nCounterMotion = 0;
	m_nAllFrameCount = 0;
	m_isFinishMotion = false;

	m_isDirty = true; // 切り替えフラグを有効化
}
//=================================================================
// モーションセット情報
//=================================================================
void CMotionInstancing::SetMotion(int nMotionType, bool isBlend, int nBlendFrame)
{
	// ここはmotiontypeに渡された番号を取得する
	if (m_motiontype == nMotionType)
	{
		// 同じだったら
		return;
	}

	m_isDirty = true; // 切り替えフラグを有効化

	// ブレンドが有効化
	if (isBlend == true)
	{
		// 最初のモーションブレンドが終わってたら
		if (!m_isFirstMotion)
		{
			m_isFirstMotion = true;
			m_nKeyBlend = 0;				// 0から始める
			m_nCounterBlend = 0;			// 0から始める
		}

		m_isBlendMotion = isBlend;			// ブレンドがあるかどうか
		m_nFrameBlend = nBlendFrame;		// ブレンドのフレームを代入
		m_motiontypeBlend = nMotionType;	// ブレンドするモーションのタイプを代入
	}
	// モーションブレンドがない
	else
	{
		// ここはmotiontypeに渡された番号を取得する
		if (m_motiontype == nMotionType)
		{
			// 同じだったら
			return;
		}

		// 代入
		m_motiontype = nMotionType;
		m_nKey = 0;
		m_nCounterMotion = 0;
		m_nAllFrameCount = 0;
		m_isFinishMotion = false;
	}
}
#if 1
//=========================================================
// モーション全体更新処理
//=========================================================
void CMotionInstancing::Update(std::vector<CInstanceModel*> pModel)
{
	const auto& manager = CManager::GetInstance()->GetInstMotionM();
	const auto& info = manager->GetFileDataIdx(m_nMotionIdx);

#if 1
	// モーションフレーム計算処理
	MathMotionFrame(info,manager);

	// モデルに適用する
	ApplyCache(pModel,info);
#endif
}
//=================================================================
// フレーム計算
//=================================================================
void CMotionInstancing::MathMotionFrame(const CInstanceMotionManager::MOTIONFILE& info, CInstanceMotionManager* pManager)
{
	// モーションキャッシュ情報を取得
	const auto& motioncache = info.cache[m_motiontype];

	// モーションカウンターを加算
	m_nAllFrameCount++;

	// 最大カウントに達したらリセット
	if (m_nAllFrameCount >= motioncache.totalFrame)
		m_nAllFrameCount = 0;
}
//=========================================================
// 結果の適用
//=========================================================
void CMotionInstancing::ApplyCache(std::vector<CInstanceModel*>& pModel, const CInstanceMotionManager::MOTIONFILE& info)
{
	// モーションの種類のフレーム取得
	const auto& frame = info.cache[m_motiontype].Frames[m_nAllFrameCount];

	// モデルに適用
	for (int nModelCount = 0; nModelCount < info.nNumModel; ++nModelCount)
	{
		pModel[nModelCount]->SetPos(frame.pos[nModelCount]);
		pModel[nModelCount]->SetRot(frame.rot[nModelCount]);
	}
}

//=========================================================
// 座標補完計算関数
//=========================================================
inline D3DXVECTOR3 CMotionInstancing::LerpPosVec3(const CInstanceMotionManager::KEY& nowKey, const CInstanceMotionManager::KEY& nextKey, float fDis)
{
	// 計算用変数
	D3DXVECTOR3 outpos = VECTOR3_NULL;

	// 座標を計算する
	outpos.x = nowKey.fPosX + (nextKey.fPosX - nowKey.fPosX) * fDis;
	outpos.y = nowKey.fPosY + (nextKey.fPosY - nowKey.fPosY) * fDis;
	outpos.z = nowKey.fPosZ + (nextKey.fPosZ - nowKey.fPosZ) * fDis;

	// 計算された座標を返す
	return outpos;
}
//=========================================================
// 回転補完計算関数
//=========================================================
inline D3DXVECTOR3 CMotionInstancing::LerpRotVec3(const CInstanceMotionManager::KEY& nowKey, const CInstanceMotionManager::KEY& nextKey, float fDis)
{
	// 計算用変数
	D3DXVECTOR3 outrot;

	// 角度を正規化する
	float NorX = NormalAngle(nextKey.fRotX - nowKey.fRotX);
	float NorY = NormalAngle(nextKey.fRotY - nowKey.fRotY);
	float NorZ = NormalAngle(nextKey.fRotZ - nowKey.fRotZ);

	// 最終角度を計算する
	outrot.x = nowKey.fRotX + NorX * fDis;
	outrot.y = nowKey.fRotY + NorY * fDis;
	outrot.z = nowKey.fRotZ + NorZ * fDis;

	// 計算された角度を返す
	return outrot;
}
#endif
//=================================================================
// デバッグフォント関数
//=================================================================
void CMotionInstancing::Debug(void)
{
#ifdef _DEBUG
	CDebugproc::Print("[現在フレームカウント] %d /  [ 最大モーションフレーム ] %d", m_nAllFrameCount, m_nNumAllFrame);
	CDebugproc::Draw(800, 320);

	CDebugproc::Print("[ブレンドフレーム] %d / [ブレンドカウント] %d", m_nFrameBlend, m_nCounterBlend);
	CDebugproc::Draw(800, 340);
#endif // _DEBUG

}
//=================================================================
// モーションフレーム判定
//=================================================================
bool CMotionInstancing::CheckFrame(int nStartMotion, int nEndMotion, int nMotionType)
{
	// StartとEndの範囲内なら
	if (m_nAllFrameCount >= nStartMotion && m_nAllFrameCount <= nEndMotion && m_motiontype == nMotionType)
		return true;

	// それ以外の時
	return false;
}

//=================================================================
// 現在のモーションの更新関数
//=================================================================
void CMotionInstancing::UpdateCurrentMotion(CInstanceMotionManager* pMption, CInstanceModel** ppModel, int nModelCount, const CInstanceMotionManager::MOTIONFILE& info)
{
	// 現在のモーション情報取得
	const CInstanceMotionManager::INFO& motionInfo = info.m_aMotionInfo[m_motiontype];

	// 現在と次のキー情報取得
	const CInstanceMotionManager::KEY_INFO& keyInfoNow = motionInfo.aKeyInfo[m_nKey];
	const CInstanceMotionManager::KEY_INFO& keyInfoNext = motionInfo.aKeyInfo[m_nNextKey];

	// キーごとの情報
	const CInstanceMotionManager::KEY& NowKey = keyInfoNow.aKey[nModelCount];
	const CInstanceMotionManager::KEY& NextKey = keyInfoNext.aKey[nModelCount];

	// 補間係数を計算
	float fDis = static_cast<float>(m_nCounterMotion) / keyInfoNow.nFrame;

	// 補完座標と角度を計算する
	m_cache.frame.pos[nModelCount] = LerpPosVec3(NowKey, NextKey, fDis);
	m_cache.frame.rot[nModelCount] = LerpRotVec3(NowKey, NextKey, fDis);
}

//=================================================================
// ブレンドモーションの更新関数
//=================================================================
void CMotionInstancing::UpdateBlend(CInstanceMotionManager* pMption, CInstanceModel** ppModel, int nModelCount, const CInstanceMotionManager::MOTIONFILE& info)
{
#if 0
	const CInstanceMotionManager::INFO& motionInfo = info.m_aMotionInfo[m_motiontype];
	const CInstanceMotionManager::INFO& BlendInfo = info.m_aMotionInfo[m_motiontypeBlend];

	// ブレンド係数を計算
	float fBlendFrame = static_cast<float>(m_nCounterBlend) / static_cast<float>(m_nFrameBlend);
	float fRateMotion = static_cast<float>(m_nCounterMotion) / static_cast<float>(motionInfo.aKeyInfo[m_nKey].nFrame);

	// 現在のキーと次のキーを取得
	const CInstanceMotionManager::KEY& nowKey = motionInfo.aKeyInfo[m_nKey].aKey[nModelCount];
	const CInstanceMotionManager::KEY& nextKey = motionInfo.aKeyInfo[m_nNextKey].aKey[nModelCount];

	const CInstanceMotionManager::KEY& nowKeyBlend = BlendInfo.aKeyInfo[m_nKeyBlend].aKey[nModelCount];
	const CInstanceMotionManager::KEY& nextKeyBlend = BlendInfo.aKeyInfo[m_nNextKeyBlend].aKey[nModelCount];

	//==========================
	// 現在モーションの補間計算
	//==========================
	D3DXVECTOR3 DiffRot = VECTOR3_NULL; // 角度
	D3DXVECTOR3	CurrentRot = VECTOR3_NULL; // 現在角度

	// 計算関数に投げる
	D3DXVECTOR3 currentPos = LerpPosVec3(nowKey, nextKey, fRateMotion);
	D3DXVECTOR3 currentRot = LerpRotVec3(nowKey, nextKey, fRateMotion);

	// 角度を計算する
	DiffRot.x = nextKey.fRotX - nowKey.fRotX;
	DiffRot.y = nextKey.fRotY - nowKey.fRotY;
	DiffRot.z = nextKey.fRotZ - nowKey.fRotZ;

	// 現在角度に適用
	CurrentRot.x = nowKey.fRotX + DiffRot.x * fRateMotion;
	CurrentRot.y = nowKey.fRotY + DiffRot.y * fRateMotion;
	CurrentRot.z = nowKey.fRotZ + DiffRot.z * fRateMotion;

	// 座標を計算
	D3DXVECTOR3 DiffPos = VECTOR3_NULL; // 座標
	D3DXVECTOR3	CurrentPos = VECTOR3_NULL; // 現在座標

	// 座標計算
	DiffPos.x = nextKey.fPosX - nowKey.fPosX;
	DiffPos.y = nextKey.fPosY - nowKey.fPosY;
	DiffPos.z = nextKey.fPosZ - nowKey.fPosZ;

	// 現在座標に適用
	CurrentPos.x = nowKey.fPosX + DiffPos.x * fRateMotion;
	CurrentPos.y = nowKey.fPosY + DiffPos.y * fRateMotion;
	CurrentPos.z = nowKey.fPosZ + DiffPos.z * fRateMotion;

	//==========================================================
	// ブレンドモーションの補間計算
	//==========================================================
	D3DXVECTOR3 DiffBlendRot = VECTOR3_NULL; // 角度
	D3DXVECTOR3	BlendRot = VECTOR3_NULL;	 // ブレンド角度

	D3DXVECTOR3 blendPos = LerpPosVec3(nowKeyBlend, nextKeyBlend, fBlendRate);
	D3DXVECTOR3 blendRot = LerpRotVec3(nowKeyBlend, nextKeyBlend, fBlendRate);

	// ブレンド角度を計算
	DiffBlendRot.x = nextKeyBlend.fRotX - nowKeyBlend.fRotX;
	DiffBlendRot.y = nextKeyBlend.fRotY - nowKeyBlend.fRotY;
	DiffBlendRot.z = nextKeyBlend.fRotZ - nowKeyBlend.fRotZ;

	// ブレンドの角度を適用
	BlendRot.x = nowKeyBlend.fRotX + DiffBlendRot.x * fBlendFrame;
	BlendRot.y = nowKeyBlend.fRotY + DiffBlendRot.y * fBlendFrame;
	BlendRot.z = nowKeyBlend.fRotZ + DiffBlendRot.z * fBlendFrame;

	D3DXVECTOR3 DiffBlendPos = VECTOR3_NULL; // 座標
	D3DXVECTOR3	BlendPos = VECTOR3_NULL;	 // ブレンド座標

	// ブレンド座標を計算
	DiffBlendPos.x = nextKeyBlend.fPosX - nowKeyBlend.fPosX;
	DiffBlendPos.y = nextKeyBlend.fPosY - nowKeyBlend.fPosY;
	DiffBlendPos.z = nextKeyBlend.fPosZ - nowKeyBlend.fPosZ;

	// ブレンドの座標を適用
	BlendPos.x = nowKeyBlend.fPosX + DiffBlendPos.x * fBlendFrame;
	BlendPos.y = nowKeyBlend.fPosY + DiffBlendPos.y * fBlendFrame;
	BlendPos.z = nowKeyBlend.fPosZ + DiffBlendPos.z * fBlendFrame;

	//==========================================================
	// モデルの座標,角度に適用
	//==========================================================

	// 最終角度,座標
	D3DXVECTOR3 LastRot = VECTOR3_NULL;
	D3DXVECTOR3 LastPos = VECTOR3_NULL;

	// 角度計算
	LastRot.x = CurrentRot.x + (BlendRot.x - CurrentRot.x) * fBlendFrame;
	LastRot.y = CurrentRot.y + (BlendRot.y - CurrentRot.y) * fBlendFrame;
	LastRot.z = CurrentRot.z + (BlendRot.z - CurrentRot.z) * fBlendFrame;

	// 座標計算
	LastPos.x = CurrentPos.x + (BlendPos.x - CurrentPos.x) * fBlendFrame;
	LastPos.y = CurrentPos.y + (BlendPos.y - CurrentPos.y) * fBlendFrame;
	LastPos.z = CurrentPos.z + (BlendPos.z - CurrentPos.z) * fBlendFrame;

	// 正規化
	LastRot.x = NormalAngle(LastRot.x);
	LastRot.y = NormalAngle(LastRot.y);
	LastRot.z = NormalAngle(LastRot.z);

	//==========================================================
	// モデルにセット
	//==========================================================
	m_ResultData.pos[nModelCount] = LastPos;
	m_ResultData.rot[nModelCount] = LastRot;
	// 現在モーション情報
	const auto& motionInfo = info.m_aMotionInfo[m_motiontype];
	const auto& blendInfo = info.m_aMotionInfo[m_motiontypeBlend];

	// 補間率
	float fBlendRate = static_cast<float>(m_nCounterBlend) / static_cast<float>(m_nFrameBlend);
	float fMotionRate = (static_cast<float>(m_nCounterMotion) / static_cast<float>(motionInfo.aKeyInfo[m_nKey].nFrame));

	//==========================
	// 現在モーション補間
	//==========================
	const auto& nowKey = motionInfo.aKeyInfo[m_nKey].aKey[nModelCount];
	const auto& nextKey = motionInfo.aKeyInfo[m_nNextKey].aKey[nModelCount];

	// 現在角度を計算
	D3DXVECTOR3 currentPos = LerpPosVec3(nowKey, nextKey, fMotionRate);
	D3DXVECTOR3 currentRot = LerpRotVec3(nowKey, nextKey, fMotionRate);

	//==========================
	// ブレンド先モーション補間
	//==========================
	const auto& nowKeyBlend = blendInfo.aKeyInfo[m_nKeyBlend].aKey[nModelCount];
	const auto& nextKeyBlend = blendInfo.aKeyInfo[m_nNextKeyBlend].aKey[nModelCount];

	// ブレンド計算
	D3DXVECTOR3 blendPos = LerpPosVec3(nowKeyBlend, nextKeyBlend, fBlendRate);
	D3DXVECTOR3 blendRot = LerpRotVec3(nowKeyBlend, nextKeyBlend, fBlendRate);

	//==========================
	// 最終入力値を設定
	//==========================
	m_cache.frame.pos[nModelCount] = currentPos + (blendPos - currentPos) * fBlendRate;
	m_cache.frame.rot[nModelCount] = currentRot + (blendRot - currentRot) * fBlendRate;


#endif
}