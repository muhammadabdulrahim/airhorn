/**
 * Airhorn Ctrl+Z
 * Muhammad Abdul-Rahim
 * Created in 2017
 */
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

/* Constant definitions */
const UINT Z_KEY = 0x5A;
const char g_class_name[] = "Airhorn";

/* Function prototypes */
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

/* Function definitions */

/*
int _cdecl _tmain( int argc, TCHAR *argv[])
{
	if( RegisterHotKey(NULL,1,MOD_CONTROL,Z_KEY) )
	{
		_tprintf(_T("Hotkey 'CTRL+b' registered\n"));
	}

	MSG msg = {0};
	while( GetMessage(&msg,NULL,0,0)!=0 )
	{
		if( msg.message == WM_HOTKEY )
		{
			_tprintf(_T("WM_HOTKEY received\n"));
		}
	}

	return 0;
}
*/

/* Handle callbacks */
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
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
	wc.lpfnWndProc		= WndProc;//TODO: Specify name of function
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

	/*
	ShowWindow(hwnd,SW_SHOWNORMAL);
	UpdateWindow(hwnd);
	ShowWindow(GetConsoleWindow(),SW_HIDE);
	*/

	ShowWindow(hwnd,nCmdShow);
	UpdateWindow(hwnd);

	// Message loop
	while( GetMessage(&Msg,NULL,0,0)>0 )
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}
