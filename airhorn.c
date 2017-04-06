/**
 * Airhorn Ctrl+Z
 * Muhammad Abdul-Rahim
 * Created in 2017
 */
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "inc/fmod.h"

/* Constant definitions */
const UINT Z_KEY = 0x5A;
const char g_class_name[] = "Airhorn";

/* FMOD globals */
FMOD_RESULT		result;
FMOD_SYSTEM		*fmod_system;
FMOD_SOUND		*sound;
FMOD_CHANNEL		*channel = 0;
FMOD_CHANNELGROUP	*channelgroup = 0;

/* Handle callbacks */
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_HOTKEY:
			result = FMOD_System_PlaySound(fmod_system,sound,channelgroup,0,&channel);
			return 0;
		case WM_CLOSE:
			DestroyWindow(hwnd);
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		default:
			return DefWindowProc(hwnd,msg,wParam,lParam);
	}
}

/* Create the window */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	// Describe the window structure
	wc.cbSize		= sizeof(WNDCLASSEX);
	wc.style		= 0;
	wc.lpfnWndProc		= WndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= hInstance;
	wc.hIcon		= LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= g_class_name;
	wc.hIconSm		= LoadIcon(NULL, IDI_APPLICATION);

	// Register window, or quit on error
	if( !RegisterClassEx(&wc) )
	{
		MessageBox(NULL,"Window failed to register","Window failed to register",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	// Create the window
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_class_name,
		g_class_name,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 240, 120,
		NULL, NULL, hInstance, NULL
	);

	if( hwnd==NULL )
	{
		MessageBox(NULL,"Window failed to create","Window failed to create",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	// Sample the audio into memory
	result = FMOD_System_Create(&fmod_system);
	result = FMOD_System_Init(fmod_system,32,FMOD_INIT_NORMAL,0);
	result = FMOD_System_CreateSound(fmod_system,"airhorn.wav",FMOD_DEFAULT,0,&sound);
	

	if( result!=FMOD_OK )
	{
		MessageBox(NULL,"Error","Error",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	// Show the window
	ShowWindow(hwnd,nCmdShow);
	UpdateWindow(hwnd);

	// Register the hotkeys
	RegisterHotKey(hwnd,100,MOD_CONTROL,Z_KEY);
	
	// Message loop
	while( GetMessage(&Msg,NULL,0,0)>0 )
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}
