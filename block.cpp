//=========================================================
//
// ブロック処理 [ block.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "block.h"
#include "boxcollider.h"
#include "collisionbox.h"
#include "xfilemanager.h"
#include "manager.h"
#include "shadowS.h"

//=========================================================
// コンストラクタ
//=========================================================
CBlock::CBlock(int nPriority) : CObjectX(nPriority), m_pCollider(nullptr)
{
	// 値のクリア
}
//=========================================================
// デストラクタ
//=========================================================
CBlock::~CBlock()
{
	// 無し
}
//=========================================================
// 生成処理
//=========================================================
CBlock* CBlock::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 scale, const char* pModelName)
{
	// インスタンス生成
	CBlock* pBlock = new CBlock;
	if (pBlock == nullptr) return nullptr;

	// オブジェクト設定
	pBlock->SetPos(pos);
	pBlock->SetRot(rot);
	pBlock->SetScale(scale);
	pBlock->SetFilePass(pModelName);

	// 初期化失敗時
	if (FAILED(pBlock->Init())) return nullptr;

	return pBlock;
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CBlock::Init(void)
{
	// 親クラスの初期化処理
	CObjectX::Init();

	// Xファイルオブジェクト取得
	CXfileManager* pXManager = CManager::GetInstance()->GetXManager();
	if (pXManager == nullptr) return E_FAIL;

	// インデックス番号を取得
	int nModelIdx = GetModelIdx();
	D3DXVECTOR3 Size = pXManager->GetInfo(nModelIdx).Size;

	std::string str = pXManager->GetInfo(nModelIdx).FilePath;

	// 葉っぱは当たらない
	if (str == "data/MODEL/STAGEOBJ/Reef.x") m_pCollider = nullptr;
	else
		m_pCollider = CBoxCollider::Create(GetPos(), GetPos(), Size);
	
	// マトリックスシャドウを有効化する
	SetShadow(true);

	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CBlock::Uninit(void)
{
	// nullチェック
	if (m_pCollider)
	{
		delete m_pCollider;
		m_pCollider = nullptr;
	}

	// 親クラスの終了処理
	CObjectX::Uninit();
}
//=========================================================
// 更新処理
//=========================================================
void CBlock::Update(void)
{
	// 現在の座標取得
	D3DXVECTOR3 pos = GetPos();

	// 座標の更新
	if (m_pCollider) m_pCollider->SetPos(pos);
}
//=========================================================
// 描画処理
//=========================================================
void CBlock::Draw(void)
{
	// 親クラスの描画処理
	CObjectX::Draw();
}
//=========================================================
// 当たり判定
//=========================================================
bool CBlock::Collision(CBoxCollider* pOther, D3DXVECTOR3* OutPos)
{
	// 矩形同士の当たり判定を返す
	return CCollisionBox::Collision(m_pCollider, pOther, OutPos);
}