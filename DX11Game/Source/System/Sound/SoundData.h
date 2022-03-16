// BGM/SE定義 (SoundData.h)

enum eBGM 
{
	TITLE,			// タイトル
	STAGESELECT,	// ステージセレクト
	GAME,			// ゲーム
	EDIT,			// ゲーム
	MAX_BGM
};

enum eSE 
{
	SE_CURSORMOVE,			// 選択
	SE_CHOISE,				// 決定
	SE_PLAYER_MOVE,			// プレイヤー移動
	SE_CUBE_MOVE,			// キューブ移動
	SE_CUBE_MOVE_NONE,		// キューブ移動できないとき
	SE_KEY_GIMIC,			// 鍵取得　ギミック破壊
	SE_TRAP,				// ダメージ床踏んだ時
	SE_PAUSE,				// ポーズ　操作説明
	SE_PAUSE_CLOSE,			// ポーズ　操作説明　閉じた時
	SE_CLEAR,				// クリア時
	SE_GAMEOVER_BEEP,		// ゲームオーバー音(ビープ)
	SE_GAMEOVER_SMOKE,		// ゲームオーバー音(スモーク)
	SE_SELECT_CURSOR,		// カーソル音
	SE_EIDT_SAVE,			// エディットモードセーブ
	SE_EIDT_LOAD,			// エディットモードロード
	SE_EDIT_CREATE,			// エディットモードオブジェクト生成
	SE_EDIT_DELTE,			// エディットモードオブジェクト削除
	SE_EDIT_CREATE_CURSOR,	// エディットモードカーソル音
	SE_EDIT_ARROW,			// エディットモードオブジェクト移動
	SE_TIMELEAP,			// 巻き戻し
	MAX_SE
};
