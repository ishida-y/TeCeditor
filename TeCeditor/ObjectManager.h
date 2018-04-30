#pragma once
#include"Object.h"
#include "Operator.h"

class ObjectManager {
public:
	ObjectManager(String _type);
	void update();
	void draw(bool select);
private:
	String type;
	std::vector<String>::iterator use;
	std::vector<String> names;
	std::vector<std::shared_ptr<Object>> objs;
};
