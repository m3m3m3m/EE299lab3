
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

	bool nothing();
	bool confirm();

	// up, right, down, left
	void attachRod(callback, callback, callback, callback);
	void attachButton(callback, callback, callback, callback);
	// rod * 4, button * 4
	void attachPad(
		callback, callback, callback, callback, 
		callback, callback, callback, callback);
}

#define WAIT_FOR_CONFIRMING \
	control::attachButton(			\
		&control::nothing, 	\
		&control::confirm, 	\
		&control::nothing, 	\
		&control::nothing	\
	)
