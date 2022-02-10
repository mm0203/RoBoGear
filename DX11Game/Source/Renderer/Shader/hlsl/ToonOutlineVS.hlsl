#define MAX_BONE_MATRIX	64

cbuffer Matrix : register(b0)
{
	matrix	g_mtxWVP;			// ワールド×ビュー×射影行列
	matrix	g_mtxLitWVP;		// ライトのワールド×ビュー×射影行列
	matrix	g_mtxWorld;			// ワールド行列
	matrix	g_mtxTexture;		// テクスチャ行列
	float4	g_vCameraPos;
};

cbuffer global_bones : register(b2)
{
	matrix g_BoneWorld[MAX_BONE_MATRIX];
};

struct VS_IN
{
	float3 pos		: POSITION0;
	float3 normal	: NORMAL0;
	float2 uv		: TEXCOORD0;
	uint4	Bone	: BONE_INDEX;	// ボーンのインデックス
	float4	Weight	: BONE_WEIGHT;	// ボーンの重み
};
// ピクセルシェーダに渡すデータ
struct VS_OUT
{
	float4 pos		: SV_POSITION;
	float4 LitPos	: WORLD_POSITION;
	float2 uv		: TEXCOORD0;
	float3 normal	: TEXCOORD1;
	float3 PosForPS : TEXCOORD2;
};
struct SKIN
{
	float4 Pos;
	float3 Norm;
};

// 頂点をスキニング (ボーンにより移動)
SKIN SkinVert(VS_IN input)
{
	SKIN output;
	float4 Pos = float4(input.pos, 1.0f);
	float3 Norm = input.normal;
	if (input.Weight.x == 0.0f)
	{
		// ボーン無し
		output.Pos = Pos;
		output.Norm = Norm;
	}
	else {
		// ボーン0
		uint uBone = input.Bone.x;
		float fWeight = input.Weight.x;
		matrix m = g_BoneWorld[uBone];
		output.Pos = fWeight * mul(Pos, m);
		output.Norm = fWeight * mul(Norm, (float3x3)m);
		// ボーン1
		uBone = input.Bone.y;
		fWeight = input.Weight.y;
		m = g_BoneWorld[uBone];
		output.Pos += fWeight * mul(Pos, m);
		output.Norm += fWeight * mul(Norm, (float3x3)m);
		// ボーン2
		uBone = input.Bone.z;
		fWeight = input.Weight.z;
		m = g_BoneWorld[uBone];
		output.Pos += fWeight * mul(Pos, m);
		output.Norm += fWeight * mul(Norm, (float3x3)m);
		// ボーン3
		uBone = input.Bone.w;
		fWeight = input.Weight.w;
		m = g_BoneWorld[uBone];
		output.Pos += fWeight * mul(Pos, m);
		output.Norm += fWeight * mul(Norm, (float3x3)m);
	}
	return output;
}

VS_OUT main(VS_IN vin)
{
	VS_OUT vout;
	SKIN vSkinned = SkinVert(vin);

	vout.pos = float4(vSkinned.Pos);
	// カメラとの距離を調べるために、事前にワールド座標を計算
	float4 worldPos = mul(vSkinned.Pos, g_mtxWorld);

	// カメラとの距離
	float distance = length(worldPos.xyz - g_vCameraPos.xyz);

	// 輪郭線として表示するため、法線方向にモデルを大きくする。
	// 拡縮では原点から離れるほど、表示がずれる
	// カメラとの距離に応じて法線方向への移動量を変えるとカメラが離れても一定の大きさで輪郭線が表示される
	float margin = distance / 1000.0f;
	vout.pos.xyz += normalize(vin.normal) * margin;

	vout.pos = mul(vout.pos, g_mtxWVP);
	vout.LitPos = mul(vSkinned.Pos, g_mtxLitWVP);
	vout.uv = mul(float4(vin.uv, 0.0f, 1.0f), g_mtxTexture).xy;
	vout.normal = mul(vSkinned.Norm, (float3x3)g_mtxWorld);
	vout.PosForPS = mul(vSkinned.Pos, g_mtxWorld).xyz;

	return vout;
}