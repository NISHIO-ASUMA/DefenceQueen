//=============================================
//
// �Q�[�W�֌W�̃N���X���� [ gauge.h ]
// Author: Asuma Nishio
//
//=============================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object2D.h"

//**********************
// �Q�[�W�N���X���`
//**********************
class CGauge :public CObject2D
{
public:

	CGauge(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CGauge();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	/// <summary>
	/// int�^�̃p�����[�^�̃Q�[�W�̒�����ݒ肷��֐�
	/// </summary>
	/// <param name="nMaxHp">�ő厞�̃p�����[�^</param>
	/// <param name="nCurrentHp">�ϓ����錻�݂̃p�����[�^</param>
	/// <param name="fMaxWidth">�\������Q�[�W�̍ő啝</param>
	void SetLengthParamInt(const int nMax,const int nCurrent,const float fMaxWidth);

	/// <summary>
	/// float�^�̃p�����[�^�̃Q�[�W�̒�����ݒ肷��֐�
	/// </summary>
	/// <param name="fMax">����</param>
	/// <param name="fCurrent">���݂̒l</param>
	/// <param name="fMaxWidth">�ő厞�̉���</param>
	void SetLengthParamFloat(const float fMax, const float fCurrent, const float fMaxWidth);

	static CGauge* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
};