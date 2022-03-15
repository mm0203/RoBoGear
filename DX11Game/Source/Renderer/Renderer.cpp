//=============================================================================
// CRenderer.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#include "Renderer.h"
#include <Renderer/Texture/Texture.h>
#include <Renderer/Graphics/Graphics.h>
#include <System/Input/input.h>
#include <Manager/GameManager.h>
#include <time.h>

//=============================================================================
// 
// �ÓI�����o
// 
//=============================================================================
double CRenderer::m_dAnimeTime;
std::map<const std::string, CAssimpModel*, std::less<>> CRenderer::m_ModelPool;
std::map<const CAssimpModel*, TAssimpMaterial*, std::less<>> CRenderer::m_MaterialPool;

//=============================================================================
// 
// �R���X�g���N�^
// 
//=============================================================================
CRenderer::CRenderer()
{
	m_pModel = nullptr;
	m_nAnimeNo = 0;
	m_filename = "\0";
	m_pTexture = nullptr;
	m_dAnimeTime = 0.0f;
}

//=============================================================================
// 
// �e�N�X�`���Z�b�g
// 
//=============================================================================
void CRenderer::SetTexture(const char* filename)
{
	m_pTexture = CTexture::GetTexture(GetDevice(), filename);
}

//=============================================================================
// 
// �e�N�X�`���Z�b�g
// 
//=============================================================================
void CRenderer::SetTexture(const wchar_t* filename)
{
	m_pTexture = CTexture::GetTexture(GetDevice(), filename);
}

//=============================================================================
// 
// �}�e���A���擾
// 
//=============================================================================
TAssimpMaterial* CRenderer::GetMaterial()
{
	// ���f�����Ȃ�������
	if (!m_pModel) return nullptr;

	if (m_pModel->GetMaterial()) return m_pModel->GetMaterial();

	// �}�e���A������
	const auto& itr = m_MaterialPool.find(m_pModel);

	// �}�e���A�����v�[���ɂ�������
	if (m_MaterialPool.end() != itr)
		return itr->second;

	// �V�K�쐬
	auto pMat = new TAssimpMaterial();

	// ���f���Ɋi�[
	m_pModel->SetMaterial(pMat);

	// �v�[���Ɋi�[
	m_MaterialPool.emplace(m_pModel, pMat);

	return pMat;
}

//=============================================================================
// 
// ���f���ǂݍ���
// 
//=============================================================================
bool CRenderer::LoadModel(const char* FileName)
{
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDC = GetDeviceContext();

	// �v�[�����猟��
	const auto& itr = m_ModelPool.find(FileName);

	// ���Ƀv�[���ɂ�������
	if (m_ModelPool.end() != itr)
	{
		m_pModel = itr->second;
		m_filename = FileName;
		//m_pTexture = GetMaterial()->pTexture;
		return true;
	}

	// �v�[���ɂȂ���ΐ���
	const auto& am = new CAssimpModel();

	// ���f���̃��[�h
	bool b = am->Load(pDevice, pDC, FileName);

	// �v�[���ɓo�^
	m_ModelPool.emplace(FileName, am);

	// �i�[
	m_pModel = am;
	m_filename = FileName;
	//m_pTexture = GetMaterial()->pTexture;

	// �J�����ƃ��C�g���Z�b�g
	m_pModel->SetLight(&CSingleton<CLight>::GetInstance());
	m_pModel->SetCamera(&CSingleton<CCamera>::GetInstance());

	return b;
}

//=============================================================================
// 
// ���f�����
// 
//=============================================================================
void CRenderer::ReleaseModel()
{
	const auto& itr = m_ModelPool.find(m_filename);

	// �v�[���ɂ�������
	if (m_ModelPool.end() != itr)
	{
		//itr->second->Release();
		m_pModel->Release();	 // ���f���������[�X
		m_ModelPool.erase(itr);	 // �v�f���폜
		delete m_pModel;
	}

	// ���f���������
	if (m_pModel)
	{
		m_pModel = nullptr;
		m_filename = "\0";
	}
}

//=============================================================================
// 
// ���f���S�J��
// 
//=============================================================================
void CRenderer::ReleaseModelAll()
{
	// �C���X�^���X�̐����擾
	int ModelCount = (int)m_ModelPool.size();

	// ���X�g���̃C���X�^���X���폜
	for (int i = 0; i < ModelCount; i++)
	{
		const auto& it = m_ModelPool.begin();
		//it->first = "\0";
		it->second->Release();	// ���f���������[�X
		delete it->second;		// �v�f�̒��g���폜
		it->second = nullptr;
		m_ModelPool.erase(it);  // �v�f���폜
	}
	// ���f���������
	if (m_pModel)
	{
		m_pModel = nullptr;
		m_filename = "\0";
	}
}

//=============================================================================
// 
// ���f���`��
// 
//=============================================================================
void CRenderer::Draw(XMFLOAT3 pos, XMFLOAT3 scale, XMFLOAT3 rot)
{
	ID3D11DeviceContext* pDC = GetDeviceContext();
	static XMFLOAT4X4	g_mtxWorld;
	XMMATRIX mtxWorld, mtxRot, mtxTranslate, mtxScale;

	mtxWorld = XMMatrixIdentity();

	// �T�C�Y
	mtxScale = XMMatrixScaling(scale.x, scale.y, scale.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxScale);
	// ��]
	mtxRot = XMMatrixRotationRollPitchYaw(XMConvertToRadians(rot.x), XMConvertToRadians(rot.y), XMConvertToRadians(rot.z));
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);
	// �ړ�
	mtxTranslate = XMMatrixTranslation(pos.x, pos.y, pos.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);
	XMStoreFloat4x4(&g_mtxWorld, mtxWorld);

	// �s�����x�؂�ւ�
	//m_pModel->DrawShadow(pDC, g_mtxWorld, eOpacityOnly, true);

	// ���f���\��
	m_pModel->Draw(pDC, g_mtxWorld, false, eNoAffect);

	// �f�o�b�O���[�h��X��������A�E�g���C����\��
	bool outline = false;
	if (CGameManager::GetDebug() && GetKeyPress(VK_X)) outline ^= 1;

	// �A�E�g���C���\��
	if(!outline)
	m_pModel->Draw(pDC, g_mtxWorld, true, eNoAffect);

	// �A�j���[�V����
	DrawAnime();
}


//=============================================================================
// 
// �A�j���Đ�����
// 
//=============================================================================
void CRenderer::AnimePlayTime()
{
	// ���Ԃ��擾
	static double LastAnimTime = clock() / double(CLOCKS_PER_SEC);
	double m_dCurrent = clock() / double(CLOCKS_PER_SEC);

	// �ŏI�̍X�V���ꂽ���Ԃƌ��݂̎��Ԃ̍������擾
	double dSlice = m_dCurrent - LastAnimTime;
	LastAnimTime = m_dCurrent;

	// ���������Z���Ď��Ԃ𑝂₵�Ă���
	m_dAnimeTime += dSlice;
}

//=============================================================================
// 
// �A�j���؂�ւ�
// 
//=============================================================================
void CRenderer::AnimeChange(int AnimeNo, double AnimeSpeed)
{
	// �A�j���̏I������
	double AnimeEndTime = m_pModel->GetAnimDuration(m_nAnimeNo);

	// ���Ԃɉ����ăA�j���؂�ւ�
	if (m_dAnimeTime >= AnimeEndTime / AnimeSpeed)
		m_nAnimeNo = AnimeNo;
}

//=============================================================================
// 
// �A�j���`��
// 
//=============================================================================
void CRenderer::DrawAnime()
{
	// �w�肵���A�j���[�V����No
	m_pModel->SetAnimIndex(m_nAnimeNo);
	// �A�j���[�V�����Đ�����
	m_pModel->SetAnimTime(m_dAnimeTime);	
}