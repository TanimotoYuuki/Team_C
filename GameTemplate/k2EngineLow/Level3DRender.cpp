#include "k2EngineLowPreCompile.h"
#include "Level3DRender.h"

#include "level3D/TklFile.h"

namespace Level3DConst
{
	const int MAX_FONT_COUNT = 256;
}

namespace nsK2EngineLow
{
	Level3DRender::~Level3DRender()
	{
	}

	void Level3DRender::Init(
		const char* filePath,
		std::function<bool(LevelObjectData& objData)> hookFunc
	)
	{
		//tkl�t�@�C�������[�h����
		m_tklFile.Load(filePath);

		MatrixTklToLevel();

		for (int i = 1; i < m_bonelist.size(); i++) {
			auto bone = m_bonelist[i].get();
			if (bone->GetParentBoneNo() == 0) {

				//�s�񂩂�|�W�V�������쐬����
				LevelObjectData levelObjData;
				bone->CalcWorldTRS(levelObjData.position, levelObjData.rotation, levelObjData.scale);

				//Zup��Yup�̕ύX
				//���W
				float fix = levelObjData.position.y;
				levelObjData.position.y = levelObjData.position.z;
				levelObjData.position.z = -fix;
				//��]
				fix = levelObjData.rotation.y;
				levelObjData.rotation.y = levelObjData.rotation.z;
				levelObjData.rotation.z = -fix;
				//�傫��
				std::swap(levelObjData.scale.y, levelObjData.scale.z);
				//Zup��Yup�̕ύX�@�I���

				levelObjData.name = m_bonelist[i]->GetName();
				std::wstring name = levelObjData.name;
				//@�����邩�ǂ����A��������
				int pos = static_cast<int>(name.find('@'));
				//@�����݂��Ă���΁A@��̐������擾����
				if (pos != std::wstring::npos)
				{
					std::wstring number = name.substr(static_cast<size_t>(pos) + 1);
					//wchar�^��int�^�ɕϊ����Ă���
					levelObjData.number = std::stoi(number.c_str());
				}

				//Hook���o�^�ς݂Ȃ�΃}�b�v�`�b�v�͍쐬�s�v
					//false �̂܂܂Ȃ�쐬����B
				bool isHooked = false;
				//hookFunc�ɂȂɂ������Ă��Ȃ���Sobject�ɂ͉����Ȃ��B
				if (hookFunc != nullptr) {
					isHooked = hookFunc(levelObjData);
				}
			}
		}
	}

	void Level3DRender::MatrixTklToLevel()
	{
		m_tklFile.QuaryObject([&](TklFile::SObject& tklObj) {
			//�R�s�[�B
			//�o�C���h�|�[�Y�B
			Matrix bindPoseMatrix;
			memcpy(bindPoseMatrix.m[0], &tklObj.bindPose[0], sizeof(tklObj.bindPose[0]));
			memcpy(bindPoseMatrix.m[1], &tklObj.bindPose[1], sizeof(tklObj.bindPose[1]));
			memcpy(bindPoseMatrix.m[2], &tklObj.bindPose[2], sizeof(tklObj.bindPose[2]));
			memcpy(bindPoseMatrix.m[3], &tklObj.bindPose[3], sizeof(tklObj.bindPose[3]));
			bindPoseMatrix.m[0][3] = 0.0f;
			bindPoseMatrix.m[1][3] = 0.0f;
			bindPoseMatrix.m[2][3] = 0.0f;
			bindPoseMatrix.m[3][3] = 1.0f;

			/// <summary>
			/// �o�C���h�|�[�Y�̋t�s��
			/// ��3��Vector3�ϊ��̍ۂɕs�v�Ȃ̂ŏ������B
			/// </summary>
			Matrix invBindPoseMatirx;
			memcpy(invBindPoseMatirx.m[0], &tklObj.invBindPose[0], sizeof(tklObj.invBindPose[0]));
			memcpy(invBindPoseMatirx.m[1], &tklObj.invBindPose[1], sizeof(tklObj.invBindPose[1]));
			memcpy(invBindPoseMatirx.m[2], &tklObj.invBindPose[2], sizeof(tklObj.invBindPose[2]));
			memcpy(invBindPoseMatirx.m[3], &tklObj.invBindPose[3], sizeof(tklObj.invBindPose[3]));
			invBindPoseMatirx.m[0][3] = 0.0f;
			invBindPoseMatirx.m[1][3] = 0.0f;
			invBindPoseMatirx.m[2][3] = 0.0f;
			invBindPoseMatirx.m[3][3] = 1.0f;

			wchar_t boneName[Level3DConst::MAX_FONT_COUNT];

			/// <summary>
			/// tkl�̃I�u�W�F�N�g���̌^�����C�h�����ɕϊ��B
			/// char -> wchar_t
			/// �ϊ�����char�^�̕�����B
			/// �ϊ����ʂ�wchar_t�^������B
			/// �T�C�Y
			/// </summary>
			mbstowcs(boneName, tklObj.name.get(), Level3DConst::MAX_FONT_COUNT);
			BonePtr bone = std::make_unique<Bone>(
				boneName,
				bindPoseMatrix,
				invBindPoseMatirx,
				tklObj.parentNo,
				tklObj.no
			);
			//�{�[����ςށB
			m_bonelist.push_back(std::move(bone));
			//�R�s�[�I���B
			});
	}
}