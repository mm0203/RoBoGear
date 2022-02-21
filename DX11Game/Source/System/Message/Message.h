//=============================================================================
// Message.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <main.h>
#include <Renderer/Polygon/CPolygon.h>

//=============================================================================
// 
//�@�}�N����`
// 
//=============================================================================
namespace
{
	const int MessageMax = 20;		// �\���ł���ő啶����
	const int MessageNum = 15;		// �����ł��镶����
	const int DefaultMag = 5;		// �f�t�H���g�̕����T�C�Y
	const float FontSizeX = 4.0f;   // ���t���[����
	const float FontSizeY = 7.0f;   // �c�t���[����

	const int FontFrameX = 7;		// �t�H���g�t���[��X
	const int FontFrameY = 4;		// �t�H���g�t���[��X

	// UV�𕪊�
	constexpr float FontFrameSizeX = 1.0f / FontFrameX;
	constexpr float FontFrameSizeY = 1.0f / FontFrameY;
}

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class MessageManager;
class Message : public CPolygon
{
	// �t�����h�N���X�@�}�l�[�W���[
	friend class MessageManager;
public:
	Message();
	~Message() = default;

	// �����o�֐�
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	// �����o�ϐ�
	XMFLOAT2 m_MessagePos;
	char m_Message[MessageMax];
	int m_Mag;	//�����{��
};

// ���b�Z�[�W�}�l�[�W���[
class MessageManager
{
public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	static void CreateMessage
	(const char* message, XMFLOAT2 pos, int Mag = DefaultMag, XMFLOAT3 Color = { 1.0f,1.0f,1.0f });
	static void DeleteObject(Message*);
	static std::vector<Message*> GetActiveList() { return m_ActiveList; }

private:
	static void AddObject(Message);
	static void CreateObject(int num = MessageNum);
	static void UpdateObject();

private:
	static std::vector<Message*> m_UnusedList;
	static std::vector<Message*> m_ActiveList;
	static std::vector<Message*> m_DeleteList;
	static ID3D11ShaderResourceView* m_pFont;
};

