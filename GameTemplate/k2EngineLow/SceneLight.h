#pragma once
namespace nsK2EngineLow
{
	/// <summary>
	/// �f�B���N�V�������C�g�\����
	/// </summary>
	struct DirectionLight
	{
		Vector3 direction; //���C�g�̕���
		float pad0;
		Vector4 color; //���C�g�̃J���[
	};

	/// <summary>
	/// ���C�g�\����
	/// </summary>
	struct Light
	{
		DirectionLight directionLight; //�f�B���N�V�������C�g�̔z��
		Vector3 eyePos; //�J�����̈ʒu
		float pad1;
		Vector3 ambientLight; //����
	};

	class SceneLight : public Noncopyable
	{
	public:
		/// <summary>
		/// ������
		/// </summary>
		void Init();

		/// <summary>
		/// �V�[�����C�g���擾
		/// </summary>
		/// <returns></returns>
		Light& GetLight()
		{
			return m_light;
		}

		/// <summary>
		/// �f�B���N�V�������C�g��ݒ肷��
		/// </summary>
		/// <param name="lightNo">���C�g�ԍ�</param>
		/// <param name="direction">���C�g�̕���</param>
		/// <param name="color">���C�g�̐F</param>
		void SetDirectionLight(const int lightNo, const Vector3 direction, const Vector4 color)
		{
			m_light.directionLight.direction = direction;
			m_light.directionLight.color = color;
		}

		/// <summary>
		/// ������ݒ肷��
		/// </summary>
		/// <param name="ambient">����</param>
		void SetAmbient(const Vector3 ambient)
		{
			m_light.ambientLight = ambient;
		}
	private:
		Light m_light;
	};
}

