#pragma once

#include "IRenderer.h"

namespace nsK2EngineLow{
	/// <summary>
	/// �t�H���g�����_�[
	/// </summary>
	class FontRender : public IRenderer
	{
	public:
		static const int MAX_TEXT_SIZE = 256;
		/// <summary>
		/// �\�����镶����ݒ�
		/// </summary>
		/// <param name="text">�\�����镶��</param>
		void SetText(const wchar_t* text)
		{
			swprintf_s(m_text, text);
		}

		/// <summary>
		/// �\�����镶�����擾
		/// </summary>
		/// <returns>�\�����镶��</returns>
		const wchar_t* GetText() const
		{
			return m_text;
		}

		/// <summary>
		/// ���W��ݒ�@z��0.0f��
		/// </summary>
		/// <param name="position">���W</param>
		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x,y,z });
		}
		void SetPosition(const Vector3& position)
		{
			m_position = position;
		}

		/// <summary>
		/// ���W���擾
		/// </summary>
		/// <returns>���W</returns>
		const Vector3& GetPosition() const
		{
			return m_position;
		}

		/// <summary>
		/// �傫����ݒ�
		/// </summary>
		/// <param name="scale">�傫��</param>
		void SetScale(const float scale)
		{
			m_scale = scale;
		}

		/// <summary>
		/// �傫�����擾
		/// </summary>
		/// <returns>�傫��</returns>
		const float GetScale() const
		{
			return m_scale;
		}

		/// <summary>
		/// �F��ݒ�
		/// </summary>
		/// <param name="color">�F</param>
		void SetColor(float r, float g, float b, float a)
		{
			SetColor({ r,g,b,a });
		}
		void SetColor(const Vector4& color)
		{
			m_color = color;
		}

		/// <summary>
		/// ��]��ݒ�
		/// </summary>
		/// <param name="rotation">��]</param>
		void SetRotation(const float rotation)
		{
			m_rotation = rotation;
		}

		/// <summary>
		/// ��]���擾
		/// </summary>
		/// <returns>��]</returns>
		const float GetRotation() const
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
			m_pivot = pivot;
		}

		/// <summary>
		/// �s�|�b�g���擾
		/// </summary>
		/// <returns>�s�|�b�g</returns>
		const Vector2& GetPivot() const
		{
			return m_pivot;
		}
		
		/// <summary>
		/// �`�揈���B
		/// </summary>
		/// <param name="rc">�����_�[�R���e�L�X�g</param>
		void Draw(RenderContext& rc);


		/// <summary>
		/// �e�̃p�����[�^��ݒ�B
		/// </summary>
		/// <param name="isDrawShadow">�e��`�悷�邩�ǂ����B</param>
		/// <param name="shadowOffset">�s�N�Z���̃I�t�Z�b�g�ʁB</param>
		/// <param name="shadowColor">�e�̐F�B</param>
		void SetShadowParam(bool isDrawShadow, float shadowOffset, const Vector4& shadowColor)
		{
			m_font.SetShadowParam(isDrawShadow, shadowOffset, shadowColor);
		}

	private:
		/// <summary>
		/// 2D�`��p�X����Ă΂�鏈���B
		/// </summary>
		/// <param name="rc"></param>
		void OnRender2D(RenderContext& rc) override
		{
			m_font.Begin(rc);
			m_font.Draw(m_text, Vector2(m_position.x, m_position.y), m_color, m_rotation, m_scale, m_pivot);
			m_font.End(rc);
		}

		Vector3		m_position = Vector3::Zero; //���W
		float		m_scale = 1.0f; //�����̑傫��
		Vector4		m_color = g_vec4White; //�����̐F�@�f�t�H���g�Ŕ�
		float		m_rotation = 0.0f; //��]
		Vector2		m_pivot = Sprite::DEFAULT_PIVOT; //�s�|�b�g
		wchar_t		m_text[MAX_TEXT_SIZE]; //����
		Font		m_font; //�t�H���g
	};
}
