//�萔�o�b�t�@�̎󂯎���

#define MAX_BONE_MATRIX	64

cbuffer Matrix : register(b0)
{
	matrix	g_mtxWVP;			// ���[���h�~�r���[�~�ˉe�s��
	matrix	g_mtxLitWVP;		// ���C�g�̃��[���h�~�r���[�~�ˉe�s��
	matrix	g_mtxWorld;			// ���[���h�s��
	matrix	g_mtxTexture;		// �e�N�X�`���s��
	float4	g_vCameraPos;
};

cbuffer global_bones : register(b2)
{
	matrix g_BoneWorld[MAX_BONE_MATRIX];
};

struct VS_IN
{
	float3 pos : POSITION0;
	float3 normal : NORMAL0;
	float2 uv : TEXCOORD0;
	uint4	Bone	: BONE_INDEX;	// �{�[���̃C���f�b�N�X
	float4	Weight	: BONE_WEIGHT;	// �{�[���̏d��
};
// �s�N�Z���V�F�[�_�ɓn���f�[�^
struct VS_OUT
{
	float4 pos : SV_POSITION;
	float4	LitPos		: WORLD_POSITION;
	float2 uv : TEXCOORD0;
	float3 normal : TEXCOORD1;
	float3	PosForPS	: TEXCOORD2;
};
struct SKIN
{
	float4 Pos;
	float3 Norm;
};

// ���_���X�L�j���O (�{�[���ɂ��ړ�)
SKIN SkinVert(VS_IN input)
{
	SKIN output;
	float4 Pos = float4(input.pos, 1.0f);
	float3 Norm = input.normal;
	if (input.Weight.x == 0.0f)
	{
		// �{�[������
		output.Pos = Pos;
		output.Norm = Norm;
	}
	else {
		// �{�[��0
		uint uBone = input.Bone.x;
		float fWeight = input.Weight.x;
		matrix m = g_BoneWorld[uBone];
		output.Pos = fWeight * mul(Pos, m);
		output.Norm = fWeight * mul(Norm, (float3x3)m);
		// �{�[��1
		uBone = input.Bone.y;
		fWeight = input.Weight.y;
		m = g_BoneWorld[uBone];
		output.Pos += fWeight * mul(Pos, m);
		output.Norm += fWeight * mul(Norm, (float3x3)m);
		// �{�[��2
		uBone = input.Bone.z;
		fWeight = input.Weight.z;
		m = g_BoneWorld[uBone];
		output.Pos += fWeight * mul(Pos, m);
		output.Norm += fWeight * mul(Norm, (float3x3)m);
		// �{�[��3
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
	// �J�����Ƃ̋����𒲂ׂ邽�߂ɁA���O�Ƀ��[���h���W���v�Z
	float4 worldPos = mul(vSkinned.Pos, g_mtxWorld);

	// �J�����Ƃ̋���
	float distance = length(worldPos.xyz - g_vCameraPos.xyz);

	// �֊s���Ƃ��ĕ\�����邽�߁A�@�������Ƀ��f����傫������B
	// �g�k�ł͌��_���痣���قǁA�\���������
	// �J�����Ƃ̋����ɉ����Ė@�������ւ̈ړ��ʂ�ς���ƃJ����������Ă����̑傫���ŗ֊s�����\�������
	float margin = distance / 1000.0f;
	vout.pos.xyz += normalize(vin.normal) * margin;

	vout.pos = mul(vout.pos, g_mtxWVP);
	vout.LitPos = mul(vSkinned.Pos, g_mtxLitWVP);
	vout.uv = mul(float4(vin.uv, 0.0f, 1.0f), g_mtxTexture).xy;
	vout.normal = mul(vSkinned.Norm, (float3x3)g_mtxWorld);
	vout.PosForPS = mul(vSkinned.Pos, g_mtxWorld).xyz;

	return vout;
}