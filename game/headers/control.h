
namespace control {
	enum Position {
		UP,
		RIGHT,
		DOWN,
		LEFT
	};

	void begin();
	bool enterSettings();
	bool exitSettings();
	bool confirm();

	// return whether to continue on this attachment
	typedef bool (*callback)();

	// up, right, down, left
	void attachButton(callback, callback, callback, callback);
	void attachRod(callback, callback, callback, callback);
}

#define WAIT_FOR_CONFIRMING while(!control::confirm())
