//=============================================================================
// Polygon.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include <main.h>
#include <Renderer/Assimp/AssimpModel.h>

//=============================================================================
// 
// プロトタイプ宣言
// 
//=============================================================================
HRESULT InitPolygon();
void UninitPolygon();
void UpdatePolygon();
void DrawPolygon(ID3D11DeviceContext* pDeviceContext);
void SetPolygonTexture(ID3D11ShaderResourceView* pTexture);
void SetPolygonPos(float fX, float fY);
void SetPolygonSize(float fScaleX, float fScaleY);
void SetPolygonAngle(float fAngle);
void SetPolygonUV(float fU, float fV);
void SetPolygonFrameSize(float fWidth, float fHeight);
void SetPolygonColor(float fRed, float fGreen, float fBlue);
void SetPolygonAlpha(float fAlpha);

