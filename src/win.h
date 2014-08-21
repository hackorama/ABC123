#ifndef _WIN_H_INCLUDED
#define _WIN_H_INCLUDED

/* ABC123 for Curious Toddlers  www.hackorama.com Summer 2008 */

#include <windows.h>
#include "resource.h"

#define WM_GRAPHNOTIFY  WM_APP + 1

class Win
{

public:
	Win(HINSTANCE hInstance);
	~Win();

	void initWindow(HINSTANCE hInstance);
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	const int MSG_DELAY_MILLISECS;

	bool nokeypressed;
	bool kioskmode;
	unsigned long counter;
	int escape_counter;
	int textcolor;
	WORD lastkey;
	BYTE allKeys[256];
	char pressedKey[2];

	HRESULT hr;
	HWND hwnd; 
	WNDCLASSEX wc;
	MSG msg; 
	LPCWSTR filename;
	HFONT bigfont, smallfont, mediumfont;
	LOGFONT big_font, small_font, medium_font;
	HBRUSH white_brush;

	static const char windowClassName[];
	static const char escapemsg_1[];
	static const char escapemsg_2[];
	static const char startupmsg_1[];
	static const char startupmsg_2[];
	static const char startupmsg_3[];
	static const char startupmsg_4[];
	static const char startupmsg_5[];
	static const char startupmsg_6[];

	int  initApp();
	void paintApp(HWND hwnd, bool newletter);
	void paintStartup(HDC hdc);
	void paintExit(HDC hdc);
	void showAbout();
	void initKioskMode();
	void closeKioskMode();
};


#endif /* _WIN_H_INCLUDED */
