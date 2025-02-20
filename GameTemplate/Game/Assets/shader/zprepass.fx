///////////////////////////////////////
// ZPrepass
///////////////////////////////////////

///////////////////////////////////////
// �\����
///////////////////////////////////////
struct SSkinVSIn
{
    int4 Indices : BLENDINDICES0;
    float4 Weights : BLENDWEIGHT0;
};

//���_�V�F�[�_�[�ւ̓���
struct SVSIn
{
    float4 pos : POSITION;
    SSkinVSIn skinVert;
};

//�s�N�Z���V�F�[�_�[�ւ̓���
struct SPSIn
{
    float4 pos : SV_POSITION;
    float3 depth : TEXCOORD0;
};

///////////////////////////////////////
// �萔�o�b�t�@�B
///////////////////////////////////////
// ���f���p�̒萔�o�b�t�@�[
cbuffer ModelCb : register(b0)
{
    float4x4 mWorld;
    float4x4 mView;
    float4x4 mProj;
};

///////////////////////////////////////
// �֐�
///////////////////////////////////////
StructuredBuffer<float4x4> g_boneMatrix : register(t3); //�{�[���s��B

/// <summary>
//�X�L���s����v�Z����B
/// </summary>
float4x4 CalcSkinMatrix(SSkinVSIn skinVert)
{
    float4x4 skinning = 0;
    float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += g_boneMatrix[skinVert.Indices[i]] * skinVert.Weights[i];
        w += skinVert.Weights[i];
    }

    skinning += g_boneMatrix[skinVert.Indices[3]] * (1.0f - w);

    return skinning;
}

// ���f���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g
SPSIn VSMainCore(SVSIn vsIn, uniform bool hasSkin)
{
    SPSIn psIn;
    float4x4 m;
    if (hasSkin)
    {
        m = CalcSkinMatrix(vsIn.skinVert);
    }
    else
    {
        m = mWorld;
    }

    psIn.pos = mul(m, vsIn.pos); // ���f���̒��_�����[���h���W�n�ɕϊ�
    psIn.pos = mul(mView, psIn.pos); // ���[���h���W�n����J�������W�n�ɕϊ�
    psIn.depth.z = psIn.pos.z;
    psIn.pos = mul(mProj, psIn.pos); // �J�������W�n����X�N���[�����W�n�ɕϊ�
    psIn.depth.x = psIn.pos.z / psIn.pos.w;
    psIn.depth.y = saturate(psIn.pos.w / 1000.0f);

    return psIn;
}

/// <summary>
/// �X�L���Ȃ����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�֐��B
/// </summary>
SPSIn VSMain(SVSIn vsIn)
{
    return VSMainCore(vsIn, false);
}

/// <summary>
/// �X�L�����胁�b�V���̒��_�V�F�[�_�[�̃G���g���[�֐��B
/// </summary>
SPSIn VSSkinMain(SVSIn vsIn)
{
    return VSMainCore(vsIn, true);
}

/// <summary>
/// �s�N�Z���V�F�[�_�[�̃R�A�֐��B
/// </summary>
float4 PSMain(SPSIn psIn) : SV_Target0
{
    return float4(psIn.depth.x, psIn.depth.y, psIn.depth.z, 1.0f);
}