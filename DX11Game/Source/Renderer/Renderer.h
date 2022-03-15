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
	// ���f��
	CAssimpModel* m_pModel;
	// �A�j��No
	int m_nAnimeNo;	
	// ���f���t�@�C����
	std::string m_filename;
	// �e�N�X�`��
	ID3D11ShaderResourceView* m_pTexture;
	// �A�j���Đ�����
	static double m_dAnimeTime;

	// ���f���v�[��
	static std::map<const std::string, CAssimpModel*, std::less<>> m_ModelPool;
	// �}�e���A���v�[��
	static std::map<const CAssimpModel*, TAssimpMaterial*, std::less<>> m_MaterialPool;
};
