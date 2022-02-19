//=============================================================================
// Shader.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

// �x����\��
//#pragma warning(disable : 4996)

#include <d3d11.h>
#include <map>
#include <string>
#include <Renderer/Texture/Texture.h>

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================

// �V�F�[�_��{�N���X
class Shader
{
protected:
	enum Kind
	{
		VertexShader,
		PixelShader
	};
protected:
	Shader(Kind kind);
public:
	virtual ~Shader();
public:
	// �V�F�[�_�[�t�@�C��(*.cso)��ǂݍ��ޏ���
	HRESULT Load(const char* pFileName);
	// �����񂩂�V�F�[�_���R���p�C��
	HRESULT Compile(const char* pCode);

	// �V�F�[�_�[��`��Ɏg�p
	virtual void Bind(void) = 0;

protected:
	// �V�F�[�_�[�t�@�C����ǂݍ��񂾌�A�V�F�[�_�[�̎�ޕʂɏ������s��
	virtual HRESULT MakeShader(void* pData, UINT size) = 0;

private:
	Kind m_kind;
};

// ���_�V�F�[�_
class VertexShader : public Shader
{
private:
	using ILKey = std::pair<std::string, ID3D11InputLayout*>;
	using ILList = std::map<std::string, ID3D11InputLayout*>;
public:
	static void ReleaseInputLayout();

	VertexShader();
	~VertexShader();
	void Bind(void);
protected:
	HRESULT MakeShader(void* pData, UINT size);

private:
	static ILList m_ilList;
	ID3D11VertexShader* m_pVS;
	ID3D11InputLayout* m_pInputLayout;
};

// �s�N�Z���V�F�[�_
class PixelShader : public Shader
{
public:
	PixelShader();
	~PixelShader();
	void Bind(void);
protected:
	HRESULT MakeShader(void* pData, UINT size);
private:
	ID3D11PixelShader* m_pPS;
};


// �萔�o�b�t�@
class ConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();

	HRESULT Create(UINT size);
	void Write(const void* pData);
	void BindVS(UINT slot);
	void BindPS(UINT slot);

	ID3D11Buffer& GetBuffer() { return *m_pBuffer; }
private:
	ID3D11Buffer* m_pBuffer;
};

//=============================================================================
// 
// �e�N�X�`���Z�b�g
// 
//=============================================================================
void SetTextureVS(Texture* pTex, UINT slot = 0);
void SetTexturePS(Texture* pTex, UINT slot = 0);
