#pragma once

#include "Object.hpp"

class Objects {
public:
	shared_ptr<Object> piano_;
	shared_ptr<Object> ladder_;
	shared_ptr<Object> greenKey_;
public:
	Objects() {
		piano_ = make_shared<Object>(
			"piano",
			"A cheap electric piano", 
			"You play some chords on the piano. It does not sound very well.",
			"The piano is too cumbersome to carry around",
			 "This is an old entry-level Yamaha with 61 keys. It looks like any cheap stuff from the late 90s. ",
			false
			);
		ladder_ = make_shared<Object>(
			"ladder",
			"A ladder going up to a trap",
			"You go up the ladder",
			"There is no point in carrying this ladder",
			"An old wooden ladder...",
			false
			);
		greenKey_ = make_shared<Object>
			(
				"green key",
				"A green key",
				"A passage to room R opens",
				"You take the key in case you would find where it goes",
				"This is rusty green key",
				true
				);
	}
};

