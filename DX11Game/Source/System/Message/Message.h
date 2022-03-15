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
// �O���錾
class MessageManager;

class CMessage : public CPolygon
{
	friend class CMessageManager; // �t�����h�N���X
public:
	CMessage();
	~CMessage() = default;

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
class CMessageManager
{
public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	// ���b�Z�[�W����
	static void CreateMessage(const char* message, XMFLOAT2 pos, int Mag = DefaultMag, XMFLOAT3 Color = { 1.0f,1.0f,1.0f });
	// �I�u�W�F�N�g�폜
	static void DeleteObject(CMessage*);
	// ���b�Z�[�W���X�g�擾
	static std::vector<CMessage*> GetActiveList() { return m_ActiveList; }

private:
	// ���b�Z�[�W�ǉ�
	static void AddObject(CMessage);
	// ���b�Z�[�W����
	static void CreateObject(int num = MessageNum);
	// ���b�Z�[�W�X�V
	static void UpdateObject();

private:
	static std::vector<CMessage*> m_UnusedList;	// ���g�p���X�g
	static std::vector<CMessage*> m_ActiveList;	// �g�p���X�g
	static std::vector<CMessage*> m_DeleteList; // �폜���X�g
	static ID3D11ShaderResourceView* m_pFont;	// �g���t�H���g
};

