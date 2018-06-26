#include"ObjectManager.h"


ObjectManager::ObjectManager(String _type) :
	type(_type) {
	//頭は空
	names.emplace_back(L"");
	//ファイル読み込み
	Array<FilePath> files = FileSystem::DirectoryContents(L"./Data/" + type);
	for (const auto& file : files) {
		if (file.includes(L".png") == true) {
			TextureAsset::Register(FileSystem::BaseName(file), file);
			names.emplace_back(FileSystem::BaseName(file));
		}
	}
	TextureAsset::PreloadAll();

	use = names.begin();

	//csv読み込み
	const CSVReader csv(L"sample.csv");
	if (!csv)
	{
		return;
	}
	for (int i = 0; i < csv.rows; i++) {
		if (csv.get<String>(i, 0) == type) {
			for (int j = 0; j < names.size(); j++) {
				if (csv.get<String>(i, 1) == names[j]) {
					objs.emplace_back(std::make_shared<Object>(csv.get<String>(i, 1), csv.get<Vec2>(i, 2), csv.get<double>(i, 3), csv.get<Vec2>(i, 4), csv.get<int>(i, 5)));
					break;
				}
			}
		}
	}
}

void ObjectManager::update() {
	//ホイールでの画像切り替え
	if (Mouse::Wheel() > 0 && !Input::MouseM.pressed) {
		++use;
		if (use == names.end()) {
			use = names.begin();
		}
	}
	if (Mouse::Wheel() < 0 && !Input::MouseM.pressed) {
		if (use == names.begin()) {
			use = names.end();
		}
		--use;
	}

	//追加
	if (*use != L"" && Operator::get().getTergetSize() == 0) {
		if (Input::MouseL.clicked) {
			objs.emplace_back(std::make_shared<Object>(*use, Mouse::Pos()));
		}
	}

	//選択
	if (Input::MouseR.clicked) {
		if (!Input::KeyShift.pressed) {
			Operator::get().clearTarget();
		}
		bool tmp = false;
		for (auto i : objs) {
			if (i->range_mouseOver()) {
				Operator::get().addTarget(i);
				tmp = true;
			}
		}
		if (tmp == false) {
			Operator::get().clearTarget();
		}
	}

	//削除
	auto rmvIter = std::remove_if(objs.begin(), objs.end(), [](const std::shared_ptr<Object>& a) {
		return a->isDead;
	});
	objs.erase(rmvIter, objs.end());

}

void ObjectManager::draw(bool select) {

	for (auto i : objs) {
		i->draw();
	}

	if (*use != L"" && Operator::get().getTergetSize() == 0 && select) {
		Vec2 pos = Mouse::Pos() - TextureAsset(*use).size / 2.0;
		TextureAsset(*use).draw(pos, Color(255, 255, 255, 128));
	}
}


void ObjectManager::write_csv(CSVWriter& writer) {
	for (auto i : objs) {
		writer.nextLine();
		writer.write(type);
		i->write_csv(writer);
	}
}