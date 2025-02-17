#pragma once

namespace nsK2EngineLow{
	/// <summary>
	/// �X�v���C�g�����_�[
	/// </summary>
	class SpriteRender
	{
	public:
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="filePath">�t�@�C���p�X</param>
		/// <param name="w">�摜�̉���</param>
		/// <param name="h">�摜�̏c��</param>
		void Init(const char* filePath, const float w, const float h);

		/// <summary>
		/// ���W��ݒ�@z��0.0f��
		/// </summary>
		/// <param name="pos">���W</param>
		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x,y,z });
		}
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
		}

		/// <summary>
		/// ���W���擾
		/// </summary>
		/// <returns>���W</returns>
		const Vector3& GetPositon() const
		{
			return m_position;
		}

		/// <summary>
		/// �傫����ݒ�@z��1.0f��
		/// </summary>
		/// <param name="scale"></param>
		void SetScale(float x, float y, float z)
		{
			SetScale({ x,y,z });
		}
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}

		/// <summary>
		/// �傫�����擾
		/// </summary>
		/// <returns>�傫��</returns>
		const Vector3& GetScale() const
		{
			return m_scale;
		}

		/// <summary>
		/// ��]��ݒ�
		/// </summary>
		/// <param name="rot">��]</param>
		void SetRotation(const Quaternion& rot)
		{
			m_rotation = rot;
		}

		/// <summary>
		/// ��]���擾
		/// </summary>
		/// <returns></returns>
		const Quaternion& GetRotation()
		{
			return m_rotation;
		}

		/// <summary>
		/// �s�|�b�g��ݒ�
		/// </summary>
		/// <param name="pivot">�s�|�b�g</param>
		void SetPivot(float x, float y)
		{
			SetPivot({ x,y });
		}
		void SetPivot(const Vector2& pivot)
		{
			m_povot = pivot;
		}

		/// <summary>
		/// ��Z�J���[��ݒ�
		/// </summary>
		/// <param name="mulColor">��Z�J���[</param>
		void SetMulColor(float r, float g, float b, float a)
		{
			SetMulColor({ r,g,b,a });
		}
		void SetMulColor(const Vector4& mulColor)
		{
			m_sprite.SetMulColor(mulColor);
		}

		/// <summary>
		/// ��Z�J���[���擾
		/// </summary>
		/// <returns>��Z�J���[</returns>
		const Vector4& GetMulColor() const
		{
			return m_sprite.GetMulColor();
		}

		/// <summary>
		/// �X�V����
		/// </summary>
		void Update()
		{
			m_sprite.Update(m_position,
				m_rotation,
				m_scale,
				m_povot);
		}

		/// <summary>
		/// �`�揈��
		/// </summary>
		/// <param name="rc">�����_�[�R���e�L�X�g</param>
		void Draw(RenderContext& rc);

	private:
		Sprite		m_sprite; //�X�v���C�g
		Vector3		m_position = Vector3::Zero; //���W
		Quaternion		m_rotation = Quaternion::Identity; //��]
		Vector3		m_scale = Vector3::One; //�傫��
		Vector2		m_povot = Sprite::DEFAULT_PIVOT; //�s�|�b�g
	};
}

