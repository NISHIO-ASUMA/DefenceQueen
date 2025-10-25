//=====================================
//
// ���[�V�������� [ motion.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once 

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "model.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

//*****************************
// ���[�V�����N���X���`
//*****************************
class CMotion
{
public:
	//***************************
	// �L�[�\���̐錾
	//***************************
	struct KEY
	{
		float fPosX;	// �ʒuX
		float fPosY;	// �ʒuY
		float fPosZ;	// �ʒuZ
		float fRotX;	// �p�xX
		float fRotY;	// �p�xY
		float fRotZ;	// �p�xZ
	};

	//***************************
	// �L�[���̍\���̐錾
	//***************************
	struct KEY_INFO
	{
		int nFrame;				// �t���[����
		std::vector<KEY> aKey;  // ���I�ȃL�[��
	};

	//***************************
	// ���[�V�������̍\���̐錾
	//***************************
	struct INFO
	{
		bool bLoop;						// ���[�v���邩���Ȃ���
		int nNumKey;					// �L�[�̑���
		std::vector<KEY_INFO> aKeyInfo; // ���[�V�����̓��I�L�[�t���[��
	};

	CMotion();
	~CMotion();

	void Update(std::vector<CModel*> m_pModel, const int nMaxPart);
	void UpdateCurrentMotion(CModel** ppModel, int nModelCount);
	void UpdateBlend(CModel** ppModel, int nModelCount);
	void Debug(void);
	bool CheckFrame(int nStartMotion, int nEndMotion, int nMotionType);

	void SetMotion(int motiontype);
	void SetMotionNum(int nMotion) { m_nNumMotion = nMotion; }

	int SetModels(std::istringstream& iss);
	void SetModelFile(std::istringstream& iss, std::vector<CModel*>& pModel, int nCnt);
	void SetParts(std::ifstream& file, std::vector<CModel*>& pModel);
	void SetPartsMotion(std::ifstream& file, CMotion* pMotion, int nCntMotion);
	void SetKey(std::ifstream& file, CMotion* pMotion, int nCntMotion, int nCntKey);
	void SetKeyDate(std::istringstream& ss, const std::string& param, CMotion* pMotion, int nCntMotion, int nCntKey, int& posKeyIndex, int& rotKeyIndex);
	void SetMotion(int nMotionType, bool isBlend, int nBlendFrame, bool isBoss);
	void SetResetFrame(int nFrame) { m_nCounterMotion = nFrame;}

	int GetMotionType(void) { return m_motiontype; }
	bool GetFinishMotion(void) { return m_isFinishMotion; }

	// ���j�[�N�|�C���^
	static std::unique_ptr<CMotion>Load(const char* pFilename, std::vector<CModel*>& pModel,int nDestMotions);

private: 
	std::vector<INFO> m_aMotionInfo; // ���[�V�������𓮓I�m��

	int m_nNumMotion;		// ���[�V�����̑���
	int m_nNumKey;			// �L�[�̑���
	int m_nKey;				// ���݂̃L�[No
	int m_nCounterMotion;	// ���[�V�����̃J�E���^�[
	int m_nNextKey;			// ���̃L�[
	int m_motiontype;		// ���[�V�����^�C�v
	int m_type;

	bool m_isBlendMotion;	// �u�����h�����邩�ǂ���
	bool m_isFinishMotion;	// ���[�V�������I��������ǂ���
	bool m_isFirstMotion;	// ���[�V�������n�܂����t���O
	bool m_isLoopMotion;	// ���[�v���邩�ǂ���

	int m_motiontypeBlend;	// �u�����h�̎��
	int m_nFrameBlend;		// �u�����h�̃t���[����
	int m_nCounterBlend;	// �u�����h�J�E���^�[
	int m_nKeyBlend;		// �u�����h���[�V�����̌��݂̃L�[
	int m_nNextKeyBlend;	// �u�����h���[�V�����̎��̃L�[

	int m_nNumModels;
	int m_nNumAllFrame;		// �L�[���Ƃ̃t���[����
	int m_nAllFrameCount;	// �S�̃t���[����

	static constexpr int NEUTRAL = 0; // �j���[�g�����ԍ�
};