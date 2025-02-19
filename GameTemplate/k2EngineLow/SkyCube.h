#pragma once

namespace nsK2EngineLow
{
	enum EnSkyCubeType {
		enSkyCubeType_Day, //����
		enSkyCubeType_Night, //���
		enSkyCubeType_Snow, //��R
		enSkyCubeType_Snow_2, //��R_2
		enSkyCubeType_Wild, //�r��
		enSkyCubeType_Wild_2, //�r��
		enSkyCubeType_Wild_Night, //�r��(���)
		enSkyCubeType_Grass, //�Ő�
		enSkyCubeType_Euro, //���B
		enSkyCubeType_DayToon, //����(�g�D�[����)
		enSkyCubeType_DayToon_2, //����(�g�D�[����)2
		enSkyCubeType_DayToon_3, //����(�g�D�[����)3
		enSkyCubeType_DayToon_4, //����(�g�D�[����)4
		enSkyCubeType_NightToon, //���(�g�D�[����)
		enSkyCubeType_NightToon_2, //���(�g�D�[����)2
		enSkyCubeType_SunriseToon, //������(�g�D�[����)
		enSkyCubeType_SpaceToon, //��C��(�g�D�[����)
		enSkyCubeType_Num,
	};

	/// <summary>
	/// �X�J�C�L���[�u
	/// </summary>
	class SkyCube : public IGameObject
	{
	public:
		SkyCube();
		~SkyCube();
		bool Start()override final;
		void Update()override final;
		void Render(RenderContext& rc)override final;

	public:
		/// <summary>
		/// ���W��ݒ�
		/// </summary>
		/// <param name="pos">���W</param>
		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x,y,z });
		}
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
			m_isDirty = true;
		}

		/// <summary>
		/// �傫����ݒ�
		/// </summary>
		/// <param name="scale">�傫��</param>
		void SetScale(const float scale)
		{
			m_scale = g_vec3One;
			m_scale.Scale(scale);
			m_isDirty = true;
		}
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
			m_isDirty = true;
		}

		/// <summary>
		/// �X�J�C�L���[�u�̃^�C�v��ݒ�
		/// </summary>
		/// <param name="type">�X�J�C�L���[�u�̃^�C�v</param>
		void SetType(EnSkyCubeType type)
		{
			m_type = type;
		}

		/// <summary>
		/// ���邳��ݒ�
		/// </summary>
		/// <param name="lum">���邳</param>
		void SetLuminance(const float lum)
		{
			m_luminance = lum;
		}

		/// <summary>
		/// �X�J�C�L���[�u�̃e�N�X�`�����擾
		/// </summary>
		/// <returns>�e�N�X�`��</returns>
		const wchar_t* GetTextureFilePath()
		{
			return m_textureFilePaths[m_type];
		}

	private:
		ModelRender m_modelRender;

		Texture m_texture[enSkyCubeType_Num];
		const wchar_t* m_textureFilePaths[enSkyCubeType_Num];
		Vector3 m_position = g_vec3Zero;
		Vector3 m_scale = g_vec3One * 50.0f;
		float m_luminance = 1.0f;
		bool m_isDirty = false;
		EnSkyCubeType m_type = enSkyCubeType_Day;
		Quaternion m_rotation = { 0.0f,0.0f,0.0f,1.0f };
	};
}

