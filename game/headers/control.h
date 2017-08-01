
namespace control {
	void begin();
	bool enterSettings();
	bool exitSettings();
	bool confirm();
}

#define WAIT_FOR_CONFIRMING while(!control::confirm())
