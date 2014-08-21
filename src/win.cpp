/* ABC123 for Curious Toddlers  www.hackorama.com Summer 2008 */

#include "win.h" 

const char Win::startupmsg_1[] = "Ready for Your Toddler to Start Pressing Letter and Number Keys";
const char Win::startupmsg_2[] = "Please press \"Esc\" key three times for toddler proof exit";
const char Win::startupmsg_3[] = "Using a separate spare keyboard will save your laptop key board";
const char Win::startupmsg_4[] = "And removing all non alpha-numeric keys from it will make it even better";
const char Win::startupmsg_5[] = "ABC123 is Made for Curious Toddlers Like Eva in Summer of 2008";
const char Win::startupmsg_6[] = "www.hackorama.com";
const char Win::escapemsg_1[]  = "Please Press \"Esc\" Key Twice More to Exit";
const char Win::escapemsg_2[]  = "Please Press \"Esc\" Key Once More to Exit";
const char Win::windowClassName[] = "AppWindow";

Win::Win(HINSTANCE hInstance)
: MSG_DELAY_MILLISECS(30)
{
	bigfont			= NULL;
	smallfont 		= NULL;
	mediumfont 		= NULL;
	counter 		= 0;
	white_brush 	= NULL;
	pressedKey[0] 	= ' ';
	pressedKey[1] 	= '\0';
	lastkey 	  	= 0;
	textcolor 	  	= 0;
	nokeypressed  	= true;
	kioskmode     	= false;
	escape_counter 	= 0;

	initWindow(hInstance);
}

Win::~Win()
{
	if(bigfont != NULL )  	DeleteObject(bigfont);
	if(smallfont != NULL )  DeleteObject(smallfont);
	if(mediumfont != NULL ) DeleteObject(mediumfont);
	if(white_brush != NULL) DeleteObject(white_brush);
}

int
Win::initApp()
{
	big_font.lfStrikeOut 		= 0;
	big_font.lfUnderline 		= 0;
	big_font.lfHeight 			= GetSystemMetrics(SM_CYMAXIMIZED) - 100;
	big_font.lfEscapement 		= 0;
	big_font.lfItalic 			= FALSE;
	big_font.lfWeight 			= FW_BOLD;
	big_font.lfPitchAndFamily 	= FF_SWISS;
	bigfont = CreateFontIndirect(&big_font);

	small_font.lfStrikeOut 		= 0;
	small_font.lfUnderline 		= 0;
	small_font.lfHeight 		= 20;
	small_font.lfEscapement 	= 0;
	small_font.lfItalic 		= FALSE;
	small_font.lfWeight 		= FW_BOLD;
	small_font.lfPitchAndFamily = FF_SWISS;
	smallfont = CreateFontIndirect(&small_font);

	medium_font.lfStrikeOut 		= 0;
	medium_font.lfUnderline 		= 0;
	medium_font.lfHeight 			= 30;
	medium_font.lfEscapement 		= 0;
	medium_font.lfItalic 			= FALSE;
	medium_font.lfWeight 			= FW_BOLD;
	medium_font.lfPitchAndFamily 	= FF_SWISS;
	mediumfont = CreateFontIndirect(&medium_font);

	white_brush = (HBRUSH)CreateSolidBrush(RGB(230,255,255));

	return 0;
}

void
Win::paintStartup(HDC hdc)
{
	POINT pntArray[2];
	int width = GetSystemMetrics(SM_CXMAXIMIZED);
	pntArray[0].x=0;
	pntArray[0].y=80;
	pntArray[1].x=width;
	pntArray[1].y=80;
	Polyline(hdc, pntArray, 2);
	SelectObject(hdc, mediumfont);
	SetTextColor(hdc, RGB(0, 200, 0));
	TextOut(hdc, width/2, 50, startupmsg_1, strlen(startupmsg_1));
	SetTextColor(hdc, RGB(0, 0, 0));
	TextOut(hdc, width/2, 85, startupmsg_2, strlen(startupmsg_2));
	SelectObject(hdc, smallfont);
	TextOut(hdc, width/2, 120, startupmsg_3, strlen(startupmsg_3));
	TextOut(hdc, width/2, 140, startupmsg_4, strlen(startupmsg_4));
	SetTextColor(hdc, RGB(0, 0, 255));
	TextOut(hdc, width/2, 165, startupmsg_5, strlen(startupmsg_5));
	SetTextColor(hdc, RGB(0, 0, 0));
	TextOut(hdc, width/2, 185, startupmsg_6, strlen(startupmsg_6));
}

void
Win::paintExit(HDC hdc)
{
	POINT pntArray[2];
	int width = GetSystemMetrics(SM_CXMAXIMIZED);
	pntArray[0].x=0;
	pntArray[0].y=40;
	pntArray[1].x=width;
	pntArray[1].y=40;
	Polyline(hdc, pntArray, 2);
	SelectObject(hdc, smallfont);
	if(escape_counter == 1) SetTextColor(hdc, RGB(200, 200, 200));
	if(escape_counter == 2) SetTextColor(hdc, RGB(100, 100, 100));
	if(escape_counter == 1) TextOut(hdc, width/2, 10, escapemsg_1, strlen(escapemsg_1));
	if(escape_counter == 2) TextOut(hdc, width/2, 10, escapemsg_2, strlen(escapemsg_2));
}

void
Win::paintApp(HWND hwnd, bool newletter)
{
	counter++;

	HDC hdc = GetDC(hwnd);

	RECT rect;	
	GetClientRect(hwnd, &rect);
	FillRect(hdc, &rect, white_brush);

	SetTextAlign(hdc, TA_CENTER | VTA_CENTER );
	SetBkMode(hdc, TRANSPARENT);

	int width = GetSystemMetrics(SM_CXMAXIMIZED);

	if(nokeypressed) 		paintStartup(hdc);
	if(escape_counter > 0)  paintExit(hdc);

	SelectObject(hdc, bigfont);
	if(newletter) textcolor = counter % 4;
	switch(textcolor)
	{
	case 0: SetTextColor(hdc, RGB(0, 230, 0));  break;
	case 1: SetTextColor(hdc, RGB(255, 100, 0));  break;
	case 2: SetTextColor(hdc, RGB(0, 0, 230));  break;
	case 3: SetTextColor(hdc, RGB(255, 20, 20));  break;
	}
	TextOut(hdc, width/2, 0, pressedKey, strlen(pressedKey));

	ReleaseDC(hwnd, hdc);
}

LRESULT CALLBACK 
Win::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Win* winptr = (Win*)GetWindowLongPtr(hwnd, GWLP_USERDATA); 
	switch(msg)
	{
	case WM_PAINT:
		winptr->paintApp(hwnd, false);
		return DefWindowProc(hwnd, msg, wParam, lParam);
		break;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		winptr->closeKioskMode();
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		{
			winptr->nokeypressed = false;
			WORD key = 0;
			GetKeyboardState(winptr->allKeys);
			ToAscii(wParam,lParam,winptr->allKeys,&key,0);
			if( isalpha((char)key) || isdigit((char)key) ){
				winptr->pressedKey[0] = toupper((char)key);
				if( key != winptr->lastkey ) winptr->paintApp(hwnd, true);
				winptr->lastkey = key;
			}else if( winptr->escape_counter > 0 ){
				winptr->paintApp(hwnd, false);
			}
		}break;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

void
Win::initKioskMode()
{
	/* TODO : Vista Compatibility
	EnableWindow( FindWindowEx(0, 0, "Shell_TrayWnd", NULL), FALSE);
	ShowWindow(FindWindowEx(NULL, NULL, MAKEINTATOM(0xC017), NULL), SW_HIDE);
	EnableWindow(FindWindowEx(FindWindow("Shell_TrayWnd", NULL), 0,"Button", NULL),FALSE) ;	
	*/

}

void
Win::closeKioskMode()
{
	/* TODO : Vista Compatibility
	EnableWindow( FindWindowEx(0, 0, "Shell_TrayWnd", NULL), TRUE);
	ShowWindow(FindWindowEx(NULL, NULL, MAKEINTATOM(0xC017), NULL), SW_SHOW);
	EnableWindow(FindWindowEx(FindWindow("Shell_TrayWnd", NULL), 0,"Button", NULL),TRUE) ;	
	*/
}

void
Win::initWindow(HINSTANCE hInst)
{
	wc.cbSize 			= sizeof(WNDCLASSEX);
	wc.hInstance 		= hInst;
	wc.style 			= CS_BYTEALIGNCLIENT | CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
	wc.lpfnWndProc 		= WndProc;
	wc.cbClsExtra 		= 0;
	wc.cbWndExtra 		= sizeof(long);
	wc.hIcon 			= LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON));
	wc.hIconSm 			= (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON), IMAGE_ICON, 16, 16, 0);
	wc.hCursor 			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground 	= CreateSolidBrush(RGB(230, 255, 255));;
	wc.lpszMenuName 	= NULL;
	wc.lpszClassName 	= windowClassName;

	RegisterClassEx(&wc);

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, windowClassName, "ABC123 | Alphabets and Numbers for Curious Eva",
		WS_MAXIMIZE|WS_VISIBLE|WS_POPUP, 0, 0,  
		GetSystemMetrics(SM_CXFULLSCREEN), 
		GetSystemMetrics(SM_CYFULLSCREEN),  
		0, 0, 0, NULL); 
	SetWindowLongPtr(hwnd, GWLP_USERDATA, (long)this);
	int status = initApp();
	SetWindowPos(hwnd, 0, 0, 0, 
		GetSystemMetrics(SM_CXMAXIMIZED), 
		GetSystemMetrics(SM_CYMAXIMIZED),  
		SWP_NOZORDER|SWP_NOMOVE);	
	ShowWindow(hwnd,SW_SHOW);

	initKioskMode();
	escape_counter=0;
	while ( msg.message != WM_QUIT) {
		if( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) ) {
			TranslateMessage( &msg );
			if(msg.message == WM_KEYDOWN) {
				if(msg.wParam==VK_ESCAPE){
					if(escape_counter++ >= 2){
						DispatchMessage( &msg ); //for escape_counter++
						closeKioskMode();
						break;
					}
				}else{ //continous 3 press of escape, reset otherwise
					escape_counter=0;
				}
			}
			DispatchMessage(  &msg );
		}
		Sleep(MSG_DELAY_MILLISECS);
	}
}
