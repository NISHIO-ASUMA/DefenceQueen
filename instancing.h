//=========================================================
// 
// インスタンシングシェーダークラス [ instancing.h ]
// Author : Asuma Nishio
// 
//=========================================================

//*********************************************************
// インクルードガード
//*********************************************************
#pragma once

//*********************************************************
// インスタンシング適用クラスを定義
//*********************************************************
class CInstancing
{
public:

	~CInstancing();

	HRESULT Init(const char* pShaderFile);
	void Uninit(void);
	void Begin(void);
	void BeginPass(const int nPass = 0);
	void EndPass(void);
	void End(void);

	void SetInstancingParam(const float& col);

	/// <summary>
	/// DirectDeviceを取得する
	/// </summary>
	/// <param name="pDevice">レンダラーのD3Dデバイス</param>
	inline void SetDeviceToInstancing(const LPDIRECT3DDEVICE9 pDevice)
	{
		m_pInstanceDevice = pDevice;
	}

	static CInstancing* GetInstance(void)
	{
		static CInstancing pInstance;
		return &pInstance;
	};

private:

	CInstancing();

	LPD3DXEFFECT m_pInstancing = nullptr;	// エフェクトポインタ
	LPDIRECT3DDEVICE9 m_pInstanceDevice;	// デバイスポインタ
};