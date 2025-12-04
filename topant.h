//=========================================================
//
// 各スポナーの仲間に指示を出すアリのクラス [ topant.h ]
// Author: Asuma Nishio
// NOTE : これは一体に関する処理
//=========================================================

//*********************************************************
// インクルードガード
//*********************************************************
#pragma once

//*********************************************************
// インクルードファイル
//*********************************************************
#include "movecharactor.h"

//*********************************************************
// 前方宣言
//*********************************************************
class CInputKeyboard;
class CJoyPad;

//*********************************************************
// 各スポナーのトップのアリのクラスを定義
//*********************************************************
class CTopAnt : public CMoveCharactor
{
public:

	//********************
	// 命令の種類
	//********************
	enum ORDER
	{
		MOVE,
		STOP,
		RETURN,
		ORDER_MAX
	};

	CTopAnt(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CTopAnt();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Moving(void);
	void MovePad(void);

	static CTopAnt* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);

private:

};