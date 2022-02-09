//=============================================================================
// Message.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include <main.h>
#include <Renderer/Polygon/CPolygon.h>

//=============================================================================
// 
//　マクロ定義
// 
//=============================================================================
#define DEFAULT_MAG		(5)
#define FONTSIZE_X		(4.0f)
#define FONTSIZE_Y		(7.0f)

#define FONTFRAME_X		(7)
#define FONTFRAME_Y		(4)

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class MessageManager;
class Message : public CPolygon
{
	// フレンドクラス　マネージャー
	friend class MessageManager;
public:
	Message();
	~Message() = default;

	// メンバ関数
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	// メンバ変数
	XMFLOAT2 m_MessagePos;
	char m_Message[20];
	int m_Mag;	//文字倍率
};

// メッセージマネージャー
class MessageManager
{
public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	static void CreateMessage
	(const char* message, XMFLOAT2 pos, int Mag = DEFAULT_MAG, XMFLOAT3 Color = { 1.0f,1.0f,1.0f });
	static void DeleteObject(Message*);
	static std::vector<Message*> GetActiveList() { return m_ActiveList; }

private:
	static void AddObject(Message);
	static void CreateObject(int num = 15);
	static void UpdateObject();

private:
	static std::vector<Message*> m_UnusedList;
	static std::vector<Message*> m_ActiveList;
	static std::vector<Message*> m_DeleteList;
	static ID3D11ShaderResourceView* m_pFont;
};

