
#include <dinput.h>
#include <d3dx9.h>

//macro to detect key presses
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

class InputManager
{
	LPDIRECTINPUT8 dinput;
	LPDIRECTINPUTDEVICE8 dimouse;
	LPDIRECTINPUTDEVICE8 dikeyboard;
	DIMOUSESTATE mouse_state;
	char keys[256];

public:
	InputManager();
	~InputManager();
	bool Input_Init(HWND, LPDIRECT3DDEVICE9 d3ddev);
	void Input_Update();
	void Input_Shutdown();

	bool Key_Down(int);
	int Mouse_Button(int);
	int Mouse_X();
	int Mouse_Y();

};