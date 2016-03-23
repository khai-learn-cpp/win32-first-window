
#include <windows.h>
#include "resource.h"

/* GLOBAL */

static WCHAR cname[] = L"WindowClass";
static WCHAR title[] = L"The very first win32 hello-world by MinGW";

/* PROTOTYPES */

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);
ATOM mkWinClass(WNDCLASSEXW &, HINSTANCE, LPWSTR);
HWND mkWin(WNDCLASSEXW, LPWSTR);

/* DEFINITIONS */

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int show) {

	WNDCLASSEXW wclass;
	if (!mkWinClass(wclass, instance, cname)) {
		MessageBoxW(NULL, L"Register window failed", L"Error", MB_OK | MB_ICONERROR);
		return 1;
	}

	auto window = mkWin(wclass, title);
	if (!window) {
		MessageBoxW(NULL, L"Create window failed", L"Error", MB_OK | MB_ICONERROR);
		return 2;
	}

	ShowWindow(window, show);
	UpdateWindow(window);

	MSG message;
	while (GetMessage(&message, NULL, 0, 0)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return message.wParam;

}

LRESULT CALLBACK WinProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {

	PAINTSTRUCT paint;
	HDC hdc;
	WCHAR hello[] = L"Hello, World!!";

	switch (message) {
		case WM_PAINT:
			hdc = BeginPaint(window, &paint);
			TextOutW(hdc, 5, 5, hello, sizeof(hello) / sizeof(WCHAR));
			EndPaint(window, &paint);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProcW(window, message, wParam, lParam);
	}

	return 0;

}

ATOM mkWinClass(WNDCLASSEXW &wclass, HINSTANCE instance, LPWSTR cname) {
	wclass.cbSize = sizeof(wclass);
	wclass.style = CS_HREDRAW | CS_VREDRAW;
	wclass.lpfnWndProc = WinProc;
	wclass.cbClsExtra = 0;
	wclass.cbWndExtra = 0;
	wclass.hInstance  = instance;
	wclass.hIcon = LoadIcon(instance, MAKEINTRESOURCE(IDR_MAINFRAME));
	wclass.hIconSm = LoadIcon(instance, MAKEINTRESOURCE(IDR_MAINFRAME));
	wclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wclass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wclass.lpszMenuName = NULL;
	wclass.lpszClassName = cname;
	return RegisterClassExW(&wclass);
}

HWND mkWin(WNDCLASSEXW wclass, LPWSTR title) {
	return CreateWindowW(
		wclass.lpszClassName, title, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 450, 300,
		NULL, NULL, wclass.hInstance, NULL
	);
}
