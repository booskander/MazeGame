#pragma once
#include "Objects.hpp"
#include "Feature.hpp"
#include <vector>
using namespace std;
typedef vector<shared_ptr<Object>> ObjectList;
class Location : public Feature {
protected:
	map<string, shared_ptr<Location>> neighbors_;
	ObjectList objectsInRoom_;
public:
	Location(const string& name, const string& description) : Feature(name, description) {
	}
	
	virtual void display() override {
		cout << endl;
		cout << "---" << name_ << "---" << endl;
		Feature::display();
		displayNeighbors();
		displayObjects();
	}
	void addObject(shared_ptr<Object> obj) {
		this->objectsInRoom_.push_back(obj);
	}

	void addNeighbor(pair<string, shared_ptr<Location>> n) {
		neighbors_.insert(n);
	}
	shared_ptr<Location> getNeighbor(string key) {
		auto it = neighbors_.find(key);
		return it != neighbors_.end() ? it->second : nullptr;
	}
	void displayNeighbors() {
		for (auto&& el : neighbors_) 
			cout << el.second->name_ << " is to the " << el.first << " (" << el.first[0] << ")" << endl;
		
	}
	void displayObjects() {
		if (!objectsInRoom_.empty()) {
			cout << "You notice :" << endl;
			for (shared_ptr<Object> obj : this->objectsInRoom_)
				if (!obj->isTaken())
					obj->display();
			cout << " " << endl;
		}

	}

	const ObjectList& getObjects() {
		return objectsInRoom_;
	 }

};

