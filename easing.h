//=============================================
//
// �C�[�W���O���� [ easing.h ]
// Author: Asuma Nishio
//
//=============================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once 

//*********************************
// �C�[�W���O�̃N���X��`
//*********************************
class CEasing
{
public:
	CEasing();
	~CEasing();

	static float EaseInsine(float t);
	static float EaseOutsine(float t);
	static float EaseInOutSine(float t);

	static float EaseInQuad(float t);	
	static float EaseOutQuad(float t);	
	static float EaseInOutQuad(float t);

	static float EaseInCubic(float t);	
	static float EaseOutCubic(float t);	
	static float EaseInOutCubic(float t);

	static float EaseBounce(float t);

	static float EaseOutQuart(float t);
	static float EaseInOutQuart(float t);

	static float EaseOutQuint(float t);
	static float EaseInOutQuint(float t);

	static float EaseInBack(float t);
	static float EaseOutBack(float t);
	static float EaseInOutBack(float t);

	static float EaseInElastic(float t);
	static float EaseOutElastic(float t);
	static float EaseInOutElastic(float t);

	static float SetEase(int EaseFrame, int MaxEaseFrame);

private:

};
