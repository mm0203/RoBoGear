// BGM/SE定義 (SoundData.h)

enum eBGM 
{
	TITLE,	// タイトル	
	STAGESELECT, // ステージセレクト
	GAME,	// ゲーム
	EDIT,
	MAX_BGM
};

enum eSE 
{
	SE_CURSORMOVE,	// 選択
	SE_CHOISE,		// 決定
	SE_PLAYER_MOVE,	// プレイヤー移動
	SE_CUBE_MOVE,	// キューブ移動
	SE_CUBE_MOVE_NONE,	// キューブ移動できないとき
	SE_KEY_GIMIC,	// 鍵取得　ギミック破壊
	SE_TRAP,
	SE_PAUSE,		// ポーズ　操作説明
	SE_PAUSE_CLOSE,		// ポーズ　操作説明　閉じた時
	SE_CLEAR,	// ゲーム開始時
	SE_GAMEOVER_BEEP,
	SE_GAMEOVER_SMOKE,
	SE_SELECT_CURSOR,
	SE_EIDT_SAVE,
	SE_EIDT_LOAD,
	SE_EDIT_CREATE,
	SE_EDIT_DELTE,
	SE_EDIT_CREATE_CURSOR,
	SE_EDIT_ARROW,
	MAX_SE
};
