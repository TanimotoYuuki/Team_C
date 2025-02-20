#pragma once
#include "level3D/TklFile.h"

namespace nsK2EngineLow
{
	struct LevelObjectData : public Noncopyable
	{
		/// <summary>
		/// �����œn�����I�u�W�F�N�g���̃I�u�W�F�N�g�����ׂ�
		/// </summary>
		/// <param name="objName">���ׂ閼�O</param>
		/// <returns>���O�������ꍇtrue��Ԃ�</returns>
		const bool EqualObjectName(const wchar_t* objName)
		{
			return wcscmp(objName, name) == 0;
		}

		/// <summary>
		/// ���O���O����v�����ׂ�
		/// </summary>
		/// <param name="n">���ׂ閼�O</param>
		/// <returns>��v���Ă�����true��Ԃ�</returns>
		const bool ForwardMatchName(const wchar_t* n)
		{
			auto len = wcslen(n);
			auto namelen = wcslen(name);
			if (len > namelen) {
				//���O�������B�s��v
				return false;
			}
			return wcsncmp(n, name, len) == 0;
		}

		Vector3 position; //���W
		Quaternion rotation; //��]
		Vector3 scale; //�g�嗦
		const wchar_t* name; //���O
		int number = 0;
	};

	class Level3DRender : public Noncopyable
	{
	public:
		Level3DRender();
		~Level3DRender();

		/// <summary>
		/// ���x����������
		/// </summary>
		/// <param name="filePath">tkl�t�@�C���̃t�@�C���p�X</param>
		/// <param name="hookFunc"></param>
		void Init(const char* filePath, std::function<bool(LevelObjectData& objData)> hookFunc);

	private:
		//tkl�t�@�C���̍s���ϊ�����
		void MatrixTklToLevel();

	private:
		using BonePtr = std::unique_ptr<Bone>;
		std::vector<BonePtr> m_bonelist;
		TklFile m_tklFile;
	};
}

