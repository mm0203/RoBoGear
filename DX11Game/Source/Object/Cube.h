//=============================================================================
// CCube.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <Manager/Object.h>

#define MODEL_CUBE "data/MODEL/Object/Magnet/Magnet1.fbx"

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class CCube : public Object
{
public:
	CCube();
	~CCube() = default;

	void Init()	  override;
	void Update() override;

private:
	//// �ʓd���̃e�N�X�`��
	//std::string m_energyOnTexture;
	//// ��ʓd���̃e�N�X�`��
	//std::string m_energyOffTexture;
};