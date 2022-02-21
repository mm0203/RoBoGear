//=============================================================================
// CInstructions.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================

#include "Instructions.h"
#include <System/Input/input.h>
#include <System/Sound/Sound.h>

//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
CInstructions::CInstructions()
{
	// インスタンス生成
	m_InstructionsBackGround = std::make_shared<CInstructionsBackGround>();
	m_InstructionsCursor = std::make_shared<CInstructionsCursor>();
	m_InstructionsScreen = std::make_shared<CInstructionsScreen>();

	// リスト追加
	m_pInstructionsTextures.emplace_back(m_InstructionsBackGround);
	m_pInstructionsTextures.emplace_back(m_InstructionsCursor);
	m_pInstructionsTextures.emplace_back(m_InstructionsScreen);
}

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void CInstructions::Init()
{
	// 初期化
	for (auto& it : m_pInstructionsTextures)
		it->Init();
}

//=============================================================================
// 
// 終了処理
// 
//=============================================================================
void CInstructions::Uninit()
{	
	// 終了
	for (auto& it : m_pInstructionsTextures)
		it->Uninit();
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void CInstructions::Update(GameState state)
{
	// 操作説明以外ならスキップ
	if (state != GameState::eInstructions)	return;

	// 更新
	for (auto& it : m_pInstructionsTextures)
		it->Update();

	// 作業用変数
	static float fPosX = 0.0f;	 // 位置
	static float fMove = 0.0f;	 // 移動量
	static int nCurrentPage = 0; // 現在のページ
	float movment = 110.0f; // 移動量

	// ページ移動
	fPosX += fMove;
	fMove += (0.0f - fMove) * 0.1f;

	// ページ切り替え
	if (GetKeyTrigger(VK_A) && nCurrentPage > eInstructions_Page1)
	{
		CSound::Play(SE_SELECT_CURSOR);

		nCurrentPage--;
		fMove += movment;
	}
	if (GetKeyTrigger(VK_D) && nCurrentPage < eInstructions_Page3)
	{
		CSound::Play(SE_SELECT_CURSOR);

		nCurrentPage++;
		fMove -= movment;
	}

	// カーソル移動 非表示
	m_InstructionsCursor->MoveCursor(nCurrentPage);

	// ページ移動
	m_InstructionsScreen->PageMove(fPosX);
}

//=============================================================================
// 
// 描画処理
// 
//=============================================================================
void CInstructions::Draw(GameState state)
{
	// 操作説明以外ならスキップ
	if (state != GameState::eInstructions)	return;

	// 描画
	for (auto& it : m_pInstructionsTextures)
		it->Draw();

}
