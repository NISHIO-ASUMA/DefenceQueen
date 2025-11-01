//=====================================
//
// �J�������� [ camera.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once 

//**********************
// �O���錾
//**********************
class CInputMouse;

//**********************
// �J�����N���X���`
//**********************
class CCamera
{
public:
	//**********************
	// �J�������[�h�񋓌^
	//**********************
	enum MODE
	{
		MODE_NONE,
		MODE_MOUSE,
		MODE_SHAKE,
		MODE_EVENT,
		MODE_MAX
	};

	//*************************
	// �J�����\���̂��`
	//*************************
	struct Camera
	{
		D3DXMATRIX mtxprojection;	// �v���W�F�N�V�����}�g���b�N�X
		D3DXMATRIX mtxView;			// �r���[�}�g���b�N�X
		D3DXVECTOR3 posV, posR;		// ���_,�����_���W
		D3DXVECTOR3 rot;			// �p�x
		D3DXVECTOR3 vecU;			// �@���x�N�g��
		D3DXVECTOR3 posRDest;		// �ړI���W
		float fDistance;			// �J�����̋���
		int nMode;					// �J�����̃��[�h
	};

	CCamera();
	~CCamera();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	void MouseView(CInputMouse* pMouse);

	void SetMode(int nMode) { m_pCamera.nMode = nMode; }
	void SetRot(D3DXVECTOR3 rot) { m_pCamera.rot = rot; }

	D3DXVECTOR3 GetRot(void) { return m_pCamera.rot; }
	D3DXVECTOR3 GetPos(void) { return m_pCamera.posV; }
	D3DXVECTOR3 GetPosR(void) { return m_pCamera.posR; }
	D3DXMATRIX GetMtxProjection(void) { return m_pCamera.mtxprojection; }
	int GetMode(void) { return m_pCamera.nMode; }

private:

	Camera ClearDefault(void);	// �N���A�p�֐�
	Camera m_pCamera;		// �J�����\���̕ϐ�
};