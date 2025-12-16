#pragma once


//********************************
// アウトラインクラス
//********************************
class COutLine
{
public:

	~COutLine();

	HRESULT Init(const char * pShaderFile);
	void Uninit(void);
	void Begin(void);
	void BeginPass(const int nPass = 0);
	void EndPass(void);
	void End(void);
	void SetParameter(const float fOutLineWidth, const D3DXVECTOR4& color, const D3DXMATRIX& mtxworld);

	static COutLine* GetInstance(void)
	{
		static COutLine pInstance;
		return &pInstance;
	};

	LPD3DXEFFECT GetOutLineEffect(void) { return m_pOutLine; }

private:

	COutLine(); // コンストラクタ

	LPD3DXEFFECT m_pOutLine = nullptr;	// エフェクトポインタ
};