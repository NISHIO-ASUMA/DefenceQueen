//=========================================================
//
// 草のビルボード処理 [ grass.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "grass.h"
#include "manager.h"
#include "texture.h"
#include <string>

//=========================================================
// コンストラクタ
//=========================================================
CGrass::CGrass(int nPriority) : CObject(nPriority),
m_col(COLOR_WHITE),
m_pos(VECTOR3_NULL),
m_rot(VECTOR3_NULL),
m_PushAngle(VECTOR3_NULL),
m_fHeight(NULL),
m_fWidth(NULL),
m_nIdxTexture(-1),
m_pVtxBuff(nullptr),
m_fRadius(NULL)
{
	D3DXMatrixIdentity(&m_mtxWorld);
}
//=========================================================
// デストラクタ
//=========================================================
CGrass::~CGrass()
{

}
//=========================================================
// 生成処理
//=========================================================
CGrass* CGrass::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth,const float fHeight)
{
	// インスタンス生成
	CGrass* pGrass = new CGrass;
	if (pGrass == nullptr) return nullptr;

	// オブジェクト設定
	pGrass->SetPos(pos);
	pGrass->SetRot(rot);
	pGrass->SetTexture("grass000.png");
	pGrass->SetSize(fWidth, fHeight);
	
	// 初期化失敗時
	if (FAILED(pGrass->Init())) return nullptr;

	return pGrass;
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CGrass::Init(void)
{
	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * BASEVERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// 頂点情報のポインタ
	VERTEX_3D* pVtx = nullptr;

	// 頂点バッファをロックし,頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_fWidth, m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_fWidth, 0.0f, 0.0f);

	// 各頂点の法線の設定
	pVtx[0].nor =
	pVtx[1].nor =
	pVtx[2].nor =
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// 法線情報

	// 頂点カラーの設定
	pVtx[0].col =
	pVtx[1].col =
	pVtx[2].col =
	pVtx[3].col = m_col;

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// アンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CGrass::Uninit(void)
{
	// バッファの解放
	if (m_pVtxBuff)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	// 自身の破棄
	CObject::Release();
}
//=========================================================
// 更新処理
//=========================================================
void CGrass::Update(void)
{
}
//=========================================================
// 描画処理
//=========================================================
void CGrass::Draw(void)
{
	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// カリングをオフ
	pDevice->SetRenderState(D3DRS_CULLMODE, TRUE);

	// ライトをオフ
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//// αテストの設定
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// 計算用のマトリックスを宣言
	D3DXMATRIX mtxRot, mtxTrans;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャ割り当て
	if (m_nIdxTexture == -1) pDevice->SetTexture(0, nullptr);
	else
	{
		// テクスチャクラス取得
		CTexture* pTexture = CManager::GetInstance()->GetTexture();
		if (pTexture == nullptr) return;

		// テクスチャセット
		pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));
	}

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// 設定を元に戻す
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}
//=========================================================
// 当たり判定の処理
//=========================================================
bool CGrass::Collision(D3DXVECTOR3* pPos)
{
	return false;
}
//=========================================================
// テクスチャ処理
//=========================================================
void CGrass::SetTexture(const char* pTexName)
{
	// テクスチャクラスポインタ取得
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	if (pTexture == nullptr) return;

	// パスを省略
	std::string TexPath = "data/TEXTURE/";
	TexPath += pTexName;

	// 実際に登録
	m_nIdxTexture = pTexture->Register(TexPath.c_str());
}