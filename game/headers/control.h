
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

	typedef bool (*callback)();

	void attachButton(callback, callback, callback, callback);
}

#define WAIT_FOR_CONFIRMING while(!control::confirm())
