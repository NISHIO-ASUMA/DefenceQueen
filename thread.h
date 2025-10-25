//=====================================
//
// スレッドクラス処理 [ thread.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードガード
//**********************
#pragma once

//**********************
// インクルードファイル
//**********************
#include <thread>
#include <atomic>
#include <functional>

//**********************
// スレッドクラスを定義
//**********************
class CThread
{
public:

	CThread();
	~CThread();

	// スレッド開始関数
	void Start(std::function<void()> func);

	// スレッド停止関数
	void Stop(void);

	// スレッドが動作中か
	bool IsRunning(void) const { return m_isRunning; }

private:

	// 部分スレッド関数
	void ThreadProc(std::function<void()> func);

	std::thread m_thread; // スレッド変数
	std::atomic<bool> m_isRunning; // スレッド動作中かのフラグ
};