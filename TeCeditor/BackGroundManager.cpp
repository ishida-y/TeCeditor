#include"BackGroundManager.h"

BackGroundManager::BackGroundManager(String _type, Vec2 _moveRate) :
	type(_type),
	moveRate(_moveRate) {
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

	use = names.begin();
	obj = std::make_shared<BackGround>(BackGround(L"", moveRate, Vec2(0, 0)));

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
					use += j;
					obj.reset();
					obj = std::make_shared<BackGround>(*use, moveRate, csv.get<Vec2>(i, 2), csv.get<double>(i, 3), csv.get<Vec2>(i, 4), csv.get<int>(i, 5));
					break;
				}
			}
			break;
		}
	}
}

void BackGroundManager::update() {
	//ホイールでの画像切り替え
	if (Mouse::Wheel() > 0 && !Input::MouseM.pressed) {
		++use;
		if (use == names.end()) {
			use = names.begin();
		}
		change_obj();
	}
	if (Mouse::Wheel() < 0 && !Input::MouseM.pressed) {
		if (use == names.begin()) {
			use = names.end();
		}
		--use;
		change_obj();
	}
}

void BackGroundManager::draw(Vec2 camera) {
	//描画処理
	if (*use != L"") {
		obj->draw(camera);
	}
}


void BackGroundManager::show_gui() {
	if (*use != L"") {
		Operator::get().changeTarget(obj);
	}
}

void BackGroundManager::change_obj() {
	Vec2 tmp = obj->get_pos();
	obj.reset();
	obj = std::make_shared<BackGround>(*use, moveRate, tmp);
	Operator::get().clearTarget();
	show_gui();
}


void BackGroundManager::write_csv(CSVWriter& writer) {
	writer.nextLine();
	writer.write(type);
	obj->write_csv(writer);
}