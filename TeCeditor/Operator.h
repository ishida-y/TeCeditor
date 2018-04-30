#pragma once
#include"Object.h"

class Operator {
private:
	Operator();
	Operator(const Operator& r) {}
	Operator& operator=(const Operator& r) {}

	GUI multiGui;
	GUI singleGui;
	std::vector<std::shared_ptr<Object>> target;

public:
	static Operator& get() {
		static Operator inst;
		return inst;
	}
	void addTarget(std::shared_ptr<Object> _tar);
	void changeTarget(std::shared_ptr<Object> _tar);
	void clearTarget();
	void update();
	void draw();
	int getTergetSize();
};