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
		//tklファイルをロードする
		m_tklFile.Load(filePath);

		MatrixTklToLevel();

		for (int i = 1; i < m_bonelist.size(); i++) {
			auto bone = m_bonelist[i].get();
			if (bone->GetParentBoneNo() == 0) {

				//行列からポジションを作成する
				LevelObjectData levelObjData;
				bone->CalcWorldTRS(levelObjData.position, levelObjData.rotation, levelObjData.scale);

				//ZupとYupの変更
				//座標
				float fix = levelObjData.position.y;
				levelObjData.position.y = levelObjData.position.z;
				levelObjData.position.z = -fix;
				//回転
				fix = levelObjData.rotation.y;
				levelObjData.rotation.y = levelObjData.rotation.z;
				levelObjData.rotation.z = -fix;
				//大きさ
				std::swap(levelObjData.scale.y, levelObjData.scale.z);
				//ZupとYupの変更　終わり

				levelObjData.name = m_bonelist[i]->GetName();
				std::wstring name = levelObjData.name;
				//@があるかどうか、検索する
				int pos = static_cast<int>(name.find('@'));
				//@が存在していれば、@後の数字を取得する
				if (pos != std::wstring::npos)
				{
					std::wstring number = name.substr(static_cast<size_t>(pos) + 1);
					//wchar型をint型に変換している
					levelObjData.number = std::stoi(number.c_str());
				}

				//Hookが登録済みならばマップチップは作成不要
					//false のままなら作成する。
				bool isHooked = false;
				//hookFuncになにも入っていない＝Sobjectには何もない。
				if (hookFunc != nullptr) {
					isHooked = hookFunc(levelObjData);
				}
			}
		}
	}

	void Level3DRender::MatrixTklToLevel()
	{
		m_tklFile.QuaryObject([&](TklFile::SObject& tklObj) {
			//コピー。
			//バインドポーズ。
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
			/// バインドポーズの逆行列
			/// 列3はVector3変換の際に不要なので初期化。
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
			/// tklのオブジェクト名の型をワイド文字に変換。
			/// char -> wchar_t
			/// 変換するchar型の文字列。
			/// 変換結果のwchar_t型文字列。
			/// サイズ
			/// </summary>
			mbstowcs(boneName, tklObj.name.get(), Level3DConst::MAX_FONT_COUNT);
			BonePtr bone = std::make_unique<Bone>(
				boneName,
				bindPoseMatrix,
				invBindPoseMatirx,
				tklObj.parentNo,
				tklObj.no
			);
			//ボーンを積む。
			m_bonelist.push_back(std::move(bone));
			//コピー終わり。
			});
	}
}