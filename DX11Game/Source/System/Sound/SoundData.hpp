// BGM/SE定義 (SoundData.hpp)

LPCWSTR g_pszFileBGM[MAX_BGM] = 
{
	L"Title.mp3",			// タイトル
	L"StageSelect.mp3",		// ステージセレクト
	L"Game.mp3",			// ゲーム
	L"EditMode.mp3",		// ゲーム
};

LPCWSTR g_pszFileSE[MAX_SE] = 
{							
	L"CursorMove.mp3",		// 選択
	L"ChoiseDecide.mp3",	// 決定
	L"PlayerMove.mp3",		// プレイヤー移動
	L"CubeMove.mp3",		// キューブ移動
	L"CubeMoveNone.mp3",	// キューブ移動できないとき
	L"GimicDelete.mp3",		// 鍵取得　ギミック破壊
	L"Trap.mp3",			// ダメージ床踏んだ時
	L"Pause.mp3",			// ポーズ　操作説明
	L"PauseClose.mp3",		// ポーズ　操作説明　閉じた時
	L"Clear.mp3",			// クリア時
	L"GameOverBeep.mp3",	// ゲームオーバー音(ビープ)
	L"GameOverSmoke.mp3",	// ゲームオーバー音(スモーク)
	L"SelectCursor.mp3",	// カーソル音
	L"EditSave.mp3",		// エディットモードセーブ
	L"EditLoad.mp3",		// エディットモードロード
	L"CreateObject.mp3",	// エディットモードオブジェクト生成
	L"ObjectDelete.mp3",	// エディットモードオブジェクト削除
	L"EditCursor.mp3",		// エディットモードカーソル音
	L"EditArrow.mp3",		// エディットモードオブジェクト移動
	L"TimeLeap.mp3",		// 巻き戻し
	
};
