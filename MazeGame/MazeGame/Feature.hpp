#pragma once
#include <memory>
#include <string>
#include <map>
#include <utility>
#include <algorithm>
#include <iostream>
using namespace std;

class Feature {
protected:
	string name_;
	string description_;
public:
	Feature() {
		name_ = "";
		description_ = "";
	}
	Feature(const string& name, const string& description)
		: name_(name), description_(description) {}

	virtual void display() {
		cout << description_ << endl;
	}
	string getName() {
		return name_;
	}
	string getDescription() {
		return description_;
	}

	void setDescription(const string& txt) {
		description_ = txt;
	}

};