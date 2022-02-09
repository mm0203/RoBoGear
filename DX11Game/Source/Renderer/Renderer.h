//=============================================================================
// CRenderer.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <Renderer/Assimp/AssimpModel.h>

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class CRenderer
{
public:
	CRenderer();
	~CRenderer() = default;

	// getter
	int GetAnimeNo() { return m_nAnimeNo; }
	static double GetAnimeTime() { return m_dAnimeTime; }

	// setter
	void SetAnimeNo(int AnimeNo) { m_nAnimeNo = AnimeNo; }
	static void SetAnimeTime(double AnimTime) { m_dAnimeTime = AnimTime; }

	// �e�N�X�`���Z�b�g
	void SetTexture(const char* filename);
	void SetTexture(const wchar_t* filename);
	// �}�e���A���擾
	TAssimpMaterial* GetMaterial();
	 // �A�j���Đ����Ԏ擾
	static void AnimePlayTime();
	// �A�j���`��
	void DrawAnime();
	// �A�j���ύX(�A�j��No, �Đ����x)
	void AnimeChange(int AnimeNo, double AnimeSpeed = 1.0f); 
	// ���f���ǂݍ���
	bool LoadModel(const char* FileName);
	// ���f���J��
	void ReleaseModel();
	// ���f���ꊇ�J��
	void ReleaseModelAll();
	// �`��
	void Draw(XMFLOAT3 pos, XMFLOAT3 scale, XMFLOAT3 rot);

private:
	CAssimpModel* m_pModel;	// ���f��
	int m_nAnimeNo;	// �A�j��No
	std::string m_filename;	// ���f���t�@�C����
	ID3D11ShaderResourceView* m_pTexture; // �e�N�X�`��
	
	static double m_dAnimeTime;	// �A�j���Đ�����

	// ���f���v�[��
	static std::map<const std::string, CAssimpModel*, std::less<>> m_ModelPool;
	// �}�e���A���v�[��
	static std::map<const CAssimpModel*, TAssimpMaterial*, std::less<>> m_MaterialPool;
};
