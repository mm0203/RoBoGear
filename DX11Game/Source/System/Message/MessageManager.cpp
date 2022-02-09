//=============================================================================
// MeSsageManager.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#include "Message.h"
#include <System/Debug/debugproc.h>
#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// 
// �ÓI�����o
// 
//=============================================================================
std::vector<Message*> MessageManager::m_ActiveList;
std::vector<Message*> MessageManager::m_UnusedList;
std::vector<Message*> MessageManager::m_DeleteList;
ID3D11ShaderResourceView* MessageManager::m_pFont = nullptr;

//=============================================================================
// 
// ����������
// 
//=============================================================================
void MessageManager::Init()
{
	// �t�H���g�ǂݍ���
	CreateTextureFromFile(GetDevice(), L"data/texture/EngFont.png", &m_pFont);

	// �I�u�W�F�N�g�쐬
	MessageManager::CreateObject();
}
//=============================================================================
// 
// �I������
// 
//=============================================================================
void MessageManager::Uninit()
{
	// �e���X�g�̃I�u�W�F�N�g�j��
	int num = (int)m_ActiveList.size();
	for (int i = 0; i < num; i++)
	{
		Message* p;
		p = *(m_ActiveList.begin());
		p->Uninit();
		m_ActiveList.erase(m_ActiveList.begin());
		delete p;
	}
	num = (int)m_UnusedList.size();
	for (int i = 0; i < num; i++)
	{
		Message* p;
		p = *(m_UnusedList.begin());
		p->Uninit();
		m_UnusedList.erase(m_UnusedList.begin());
		delete p;
	}

	SAFE_RELEASE(m_pFont);
}

//=============================================================================
// 
// �X�V����
// 
//=============================================================================
void MessageManager::Update()
{
	// �I�u�W�F�N�g�X�V
	for (auto it : m_ActiveList)
		it->Update();
	// ���X�g�X�V
	MessageManager::UpdateObject();
}

//=============================================================================
// 
// �`�揈��
// 
//=============================================================================
void MessageManager::Draw()
{
	// �I�u�W�F�N�g�`��
	for (auto it : m_ActiveList)
		it->Draw();
}

//=============================================================================
// 
// ���b�Z�[�W��������
// 
//=============================================================================
void MessageManager::CreateMessage(const char* message, XMFLOAT2 pos, int Mag, XMFLOAT3 Color)
{
	Message obj;
	strcpy(obj.m_Message, message);
	obj.m_MessagePos = pos;
	obj.SetFrameSize(1.0f / FONTFRAME_X, 1.0f / FONTFRAME_Y);
	obj.SetSize(FONTSIZE_X * Mag, FONTSIZE_Y * Mag);
	obj.SetColor(Color);
	obj.m_Mag = Mag;
	obj.SetTex(m_pFont);
	MessageManager::AddObject(obj);
}

//=============================================================================
// 
// �폜����
// 
//=============================================================================
void MessageManager::DeleteObject(Message* pObj)
{
	// DeleteList�ɓo�^
	m_DeleteList.push_back(pObj);
}

//=============================================================================
// 
// �I�u�W�F�N�g�ǉ�
// 
//=============================================================================
void MessageManager::AddObject(Message obj)
{
	// �o�^�p�I�u�W�F�N�g
	Message* pObj;
	// ���g�p�I�u�W�F�N�g��������΃G���[
	if (m_UnusedList.empty())
	{
		MessageBoxA(GetMainWnd(), "���b�Z�[�W�I�u�W�F�N�g������Ȃ�", "ObjectNothing", MB_OK);
		return;
	}
	// ���g�p���X�g����I�u�W�F�N�g�����o��
	pObj = *m_UnusedList.begin();

	// ���g�p���X�g�X�V
	m_UnusedList.erase(m_UnusedList.begin());

	// �I�u�W�F�N�g�̒��g���R�s�[
	*pObj = obj;

	// �A�N�e�B�u���X�g�ɓo�^
	m_ActiveList.push_back(pObj);
}

//=============================================================================
// 
// �I�u�W�F�N�g�X�V
// 
//=============================================================================
void MessageManager::UpdateObject()
{
	// ��̏ꍇ�X�L�b�v
	if (m_DeleteList.empty()) return;

	for (auto it : m_DeleteList)
	{
		int num = 0;
		// �A�N�e�B�u���X�g���猟��
		for (auto ite : m_ActiveList)
		{
			if (it == ite)
			{
				// �|�C���^���Q�b�g
				Message* pObj = ite;

				// �A�N�e�B�u���X�g����폜
				m_ActiveList.erase(m_ActiveList.begin() + num);

				// ���g�p���X�g�ɒǉ�
				m_UnusedList.push_back(pObj);

				break;
			}
			num++;
		}
	}
	// �폜���X�g�N���A
	m_DeleteList.clear();
}

//=============================================================================
// 
// �I�u�W�F�N�g����
// 
//=============================================================================
void MessageManager::CreateObject(int num)
{
	// �I�u�W�F�N�g�쐬
	for (int i = 0; i < num; i++)
	{
		Message* pObj = new Message;
		// ���g�p���X�g�ɓo�^
		m_UnusedList.push_back(pObj);
	}
}
