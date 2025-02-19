#pragma once

namespace nsK2EngineLow
{
	/// <summary>
	/// �X�L�����f�������_�[
	/// </summary>
	class ModelRender
	{
	public:
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="filePath">�t�@�C���p�X</param>
		/// <param name="animationClips">�A�j���[�V�����N���b�v</param>
		/// <param name="numAnimationClips">�A�j���[�V�����N���b�v�̐�</param>
		/// <param name="enModelUpAxis">���f���̏����</param>
		void Init(const char* filePath,
			AnimationClip* animationClips = nullptr,
			int numAnimationClips = 0,
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ);
		
		/// <summary>
		/// �X�J�C�L���[�u��������
		/// </summary>
		void InitSkyCube(ModelInitData& initData);

		/// <summary>
		/// �X�V���� 
		/// </summary>
		void Update();

		/// <summary>
		/// �`�揈��
		/// </summary>
		/// <param name="rc">�����_�[�R���e�L�X�g</param>
		void Draw(RenderContext& rc);

		/// <summary>
		/// �A�j���[�V�����Đ�
		/// </summary>
		/// <param name="animNo"></param>
		/// <param name="interpolateTime"></param>
		void PlayAnimation(int animNo, float interpolateTime = 0.0f)
		{
			m_animation.Play(animNo, interpolateTime);
		}

		/// <summary>
		/// �A�j���[�V�����̍Đ����H 
		/// </summary>
		bool IsPlayingAnimation() const
		{
			return m_animation.IsPlaying();
		}

		/// <summary>
		/// ���f�����擾
		/// </summary>
		/// <returns></returns>
		Model& GetModel()
		{
			return m_model;
		}

		/// <summary>
		/// ���W�A��]�A�g���S�čX�V
		/// </summary>
		/// <param name="pos">���W</param>
		/// <param name="rotation">��]</param>
		/// <param name="scale">�g��</param>
		void SetTRS(const Vector3& pos, const Quaternion& rotation, const Vector3& scale)
		{
			SetPosition(pos);
			SetRotation(rotation);
			SetScale(scale);
		}

		/// <summary>
		/// ���W��ݒ�
		/// </summary>
		/// <param name="pos">���W</param>
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
		}

		/// <summary>
		/// ��]��ݒ�
		/// </summary>
		/// <param name="rotation"><��]/param>
		void SetRotation(const Quaternion& rotation)
		{
			m_rotation = rotation;
		}

		/// <summary>
		/// �傫����ݒ�
		/// </summary>
		/// <param name="scale"></param>
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}
	private:
		/// <summary>
		/// ���f���̏�����
		/// </summary>
		/// <param name="filePath">�t�@�C���p�X</param>
		/// <param name="enModelUpAxis">���f���̏����</param>
		void InitModel(const char* filePath, EnModelUpAxis enModelUpAxis);
		/// <summary>
		/// �X�P���g���̏�����
		/// </summary>
		/// <param name="filePath"></param>
		void InitSkeleton(const char* filePath);
		/// <summary>
		/// �A�j���[�V�����̏�����
		/// </summary>
		/// <param name="animationClips"></param>
		/// <param name="numAnimationClips"></param>
		/// <param name="enModelUpAxis"></param>
		void InitAnimation(AnimationClip* animationClips,
			int numAnimationClips,
			EnModelUpAxis enModelUpAxis
		);

	private:
		AnimationClip* m_animationClips = nullptr; //�A�j���[�V�����N���b�v
		int		m_numAnimationClips = 0; //�A�j���[�V�����̐�
		Vector3		m_position = Vector3::Zero; //���W
		Quaternion		m_rotation = Quaternion::Identity; //��]
		Vector3		m_scale = Vector3::One; //�g�嗦
		EnModelUpAxis		m_enFbxUpAxis = enModelUpAxisZ; //FBX�̏����
		Animation		m_animation; //�A�j���[�V����
		Model		m_model; //�X�L�����f��
		bool		m_isUpdateAnimation = true; // �A�j���[�V�������X�V����H
		Skeleton		m_skeleton; //��
	};
}

