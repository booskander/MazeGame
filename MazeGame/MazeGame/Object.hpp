#pragma once

#include "Feature.hpp"

class Object : public Feature {
private:
	string action_;
	string taking_;
	string look_;
	bool canBeTaken_;
	bool isTaken_ = false;
	bool isUsed_ = false;
public:
	Object() : Feature(), action_(""), taking_(""), look_(""), canBeTaken_(false) {}
	Object(const string& name, const string& description, const string& action, const string& taking, const string& look, bool take)
		: Feature(name, description), action_(action), taking_(taking), canBeTaken_(take), look_(look) {}
	void take() {
		cout << taking_ << endl << endl;
		if (canBeTaken_)
			isTaken_ = true;
	}
	void use() {
		cout << action_ << endl << endl;
		isUsed_ = true;
	}
	void look() {
		cout << look_ << endl << endl;
	}
	bool isTaken() {
		return isTaken_;
	}
	bool canBeTaken() {
		return canBeTaken_;
	}

	void setAction(const string& str) {
		action_ = str;
	}
	bool isUsed() {
		return isUsed_;
	}
};