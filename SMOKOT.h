#pragma once
#pragma comment(lib,"ws2_32.lib")
#include <WS2tcpip.h>
#include "winsock2.h"
#pragma warning(disable:4996)

#include <functional>
#include "string"
#include "windows.h"
#include "sstream"
#include "vector"
#include "tuple"
#include "ctime"
#include <gdiplus.h>
#pragma comment(lib, "GdiPlus.lib")
using namespace std;
using namespace Gdiplus;
static const GUID png =
{ 0x557cf406, 0x1a04, 0x11d3, { 0x9a, 0x73, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e } };

struct GetPixelColor_One {
public:
	int r, g, b;
	void GetColor(int x, int y)
	{
		ref = GetPixel(GetDC(0), x, y);

		r = GetRValue(ref);
		g = GetGValue(ref);
		b = GetBValue(ref);
	}
private:
	COLORREF ref;
	int x, y;
};

class SMOKOT {
public:

	size_t b64_encoded_size(size_t inlen)
	{
		size_t ret;

		ret = inlen;
		if (inlen % 3 != 0)
			ret += 3 - (inlen % 3);
		ret /= 3;
		ret *= 4;

		return ret;
	}

	char* b64_encode(const char* in, size_t len)
	{
		const char b64chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
		char * out;
		size_t  elen;
		size_t  i;
		size_t  j;
		size_t  v;

		if (in == NULL || len == 0)
			return NULL;

		elen = b64_encoded_size(len);
		out = (char*)malloc(elen + 1);
		out[elen] = '\0';

		for (i = 0, j = 0; i < len; i += 3, j += 4) {
			v = in[i];
			v = i + 1 < len ? v << 8 | in[i + 1] : v << 8;
			v = i + 2 < len ? v << 8 | in[i + 2] : v << 8;

			out[j] = b64chars[(v >> 18) & 0x3F];
			out[j + 1] = b64chars[(v >> 12) & 0x3F];
			if (i + 1 < len) {
				out[j + 2] = b64chars[(v >> 6) & 0x3F];
			}
			else {
				out[j + 2] = '=';
			}
			if (i + 2 < len) {
				out[j + 3] = b64chars[v & 0x3F];
			}
			else {
				out[j + 3] = '=';
			}
		}

		return out;
	}







	SOCKET get_sock()
	{
		return sock;
	}

	void create_server(const char * ip, int port, int connection_type)
	{
		if (WSAStartup(MAKEWORD(2, 1), &WS) != 0) {
			
		}
		else {
			connection_type_ = connection_type;
			addr.sin_addr.S_un.S_addr = inet_addr(ip);

			addr.sin_port = htons(port);
			addr.sin_family = AF_INET;
			
			
			

			sock = socket(AF_INET, connection_type, NULL);

			size = sizeof(addr);

			bind(sock, (sockaddr*)&addr, size);

			listen(sock, SOMAXCONN);


		}
		
	}

	void connect_server(char* ip, int port, int connection_type)
	{
		if (WSAStartup(MAKEWORD(2, 1), &WS) != 0) {

		}
		else {

			addr.sin_addr.S_un.S_addr = inet_addr(ip);

			addr.sin_port = htons(port);
			addr.sin_family = AF_INET;
		
			sock = socket(AF_INET, connection_type, NULL);

			size = sizeof(addr);	
			
			connect(sock, (sockaddr*)&addr, size);
		}
	}
	void sock_send(SOCKET to_send, const char * x)
	{
		send(to_send, x, sizeof(x), 0);
	}

	void sock_send(SOCKET to_send, stringstream x)
	{
		send(to_send, x.str().c_str(), x.str().length(), 0);
	}

	int sock_recv(char* x,SOCKET s)
	{
		int res = recv(s, x, sizeof(x), 0);
		return res;
	}
	SOCKET accept_connection()
	{
		res_accept_connection = accept(sock, (sockaddr*)&addr, &size);
		return res_accept_connection;
	}
	sockaddr* get_addr()
	{
		return (sockaddr*)&addr;
	}
	int get_addr_size()
	{
		return size;
	}

	void keyboard_write(string word)
	{
		INPUT input;
		input.type = INPUT_KEYBOARD;


		for (int i = 0; i < word.size(); i++)
		{
			if (isupper(word[i]))
			{
				input.ki.wVk = VK_CAPITAL;
				input.ki.dwFlags = KEYEVENTF_EXTENDEDKEY;
				SendInput(1, &input, sizeof(input));


				input.ki.wVk = VK_CAPITAL;
				input.ki.dwFlags = KEYEVENTF_KEYUP;
				SendInput(1, &input, sizeof(input));

				input.ki.wVk = toupper(word[i]);
				input.ki.dwFlags = KEYEVENTF_EXTENDEDKEY;
				SendInput(1, &input, sizeof(input));
				
				input.ki.wVk = toupper(word[i]);
				input.ki.dwFlags = KEYEVENTF_KEYUP;
				SendInput(1, &input, sizeof(input));

				input.ki.wVk = VK_CAPITAL;
				input.ki.dwFlags = KEYEVENTF_EXTENDEDKEY;
				SendInput(1, &input, sizeof(input));

				input.ki.wVk = VK_CAPITAL;
				input.ki.dwFlags = KEYEVENTF_KEYUP;
				SendInput(1, &input, sizeof(input));

				

				continue;
			}
			input.ki.wVk = toupper(word[i]);
			input.ki.dwFlags = KEYEVENTF_EXTENDEDKEY;
			SendInput(1, &input, sizeof(input));

			input.ki.wVk = toupper(word[i]);
			input.ki.dwFlags = KEYEVENTF_KEYUP;
			SendInput(1, &input, sizeof(input));
			
			
		}
		
	}
	//Example: key = VK_F9, flag = KEYEVENTF_EXTENDKEY;
	
	//Example: key = VK_F9
	void keyboard(DWORD key, BOOL flag)
	{
		UINT scan = MapVirtualKey(key, MAPVK_VK_TO_VSC);
		INPUT input;
		input.type = INPUT_KEYBOARD;
		input.ki.wScan = scan;
		
		input.ki.dwFlags = KEYEVENTF_SCANCODE | (flag ? KEYEVENTF_KEYUP : 0);

		SendInput(1, &input, sizeof(input));

	}


	void LeftClick()
	{
		INPUT input;
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

		SendInput(1, &input, sizeof(input));

		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_LEFTUP;

		SendInput(1, &input, sizeof(input));
		
		
	}

	void RightClick()
	{
		INPUT input;
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;

		SendInput(1, &input, sizeof(input));

		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;

		SendInput(1, &input, sizeof(input));


	}


	


	tuple <int, int, int> GetPixelColor_Two(int x, int y)
	{
		


		tuple <int, int, int> color;
		COLORREF ref;
		ref = GetPixel(GetDC(0), x, y);

		get<0>(color) = GetRValue(ref);
		get<1>(color) = GetGValue(ref);
		get<2>(color) = GetBValue(ref);
		return color;
	}


	HBITMAP Screenshot(int x1, int y1, int x2, int y2) {
		

		HDC scrdc, memdc;
		HBITMAP membit;

		scrdc = GetDC(0);

		memdc = CreateCompatibleDC(scrdc);
		membit = CreateCompatibleBitmap(scrdc, x2, y2);
		SelectObject(memdc, membit);


		BitBlt(memdc, 0, 0, x2, y2, scrdc, x1, y1, SRCCOPY);
		HBITMAP hBitmap;
		hBitmap = (HBITMAP)SelectObject(memdc, membit);
		//DeleteObject(hBitmap);
		return hBitmap;
	}


	void SaveBitMap(HBITMAP Hbitmap, const wchar_t * path) {
		GdiplusStartupInput gdiplusStartupInput;
		ULONG_PTR gdiplusToken;
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
		
		Gdiplus::Bitmap bitmap(Hbitmap, NULL);
		bitmap.Save(path, &png); //Сохранял для проверки

	}





	vector<string> split(string x, char sign)
	{
		string word;
		vector<string> result;
		for (int i = 0; i <= x.size(); i++)
		{
			if (x[i] == sign)
			{
				result.push_back(word);
				word = "";
				continue;
			}
			word += x[i];
		}
		result.push_back(word);

		return result;
	}

	char * int_to_char(int x)
	{
		SMOKOT smokot;
		string take = smokot.int_to_string(x);
		char * result = smokot.string_to_char(take);
		return result;
	}

	string int_to_string(int x)
	{
		string result = "";
		stringstream ss;
		ss << x;

		result = ss.str();
		return result;
	}


	int string_to_int(string x)
	{
		SMOKOT smokot;
		int result = 0;
		char * swap = smokot.string_to_char(x);
		result = smokot.char_to_int(swap);


		return result;
	}

	int char_to_int(const char * x)
	{
		int result = 0;
		result = atoi(x);
		return result;
	}



	char * string_to_char(std::string x) // ПЕРЕВОД STRING В CHAR
	{
		int size = x.size(); size++;
		char * ch = new char[size];
		ZeroMemory(ch, size);
		for (int i = 0; i < size; i++) {
			ch[i] = x[i];
		}
		ch[size] = '\0';
		char * out = ch;
		//delete[] ch;
		return ch;
	}

	std::string char_to_string(char*x) // ПЕРЕВОД CHAR В STRING
	{
		int size = strlen(x);
		std::string word = "";
		for (int i = 0; i < size; i++)
		{
			word += x[i];
		}
		return word;
	}
	void msg_box(LPCSTR word, LPCSTR title) // УПРОЩЕННЫЙ MessageBox
	{
		MessageBox(NULL, title, word, NULL);
	}

	void draw_dot(int x, int y, COLORREF ref, int pen_size)
	{
		HDC dc = GetDC(0);

		HPEN pen = CreatePen(PS_SOLID, pen_size, ref);

		SelectObject(dc, pen);

		POINT point;

		MoveToEx(dc, x, y, &point);
		LineTo(dc, x, y);

	}
	void draw_line(int x, int y, int x2, int y2, COLORREF color, int pen_size)
	{
		HDC dc = GetDC(0);

		HPEN pen = CreatePen(PS_SOLID, pen_size, color);

		SelectObject(dc, pen);

		POINT point;

		MoveToEx(dc, x, y, &point);
		LineTo(dc, x2, y2);

	}
	void draw_text(int x, int y, char * str)
	{
		HDC dc = GetDC(0);

		TextOut(dc, x, y, str, strlen(str));
		
	}
	private:
		WSAData WS;
		SOCKADDR_IN addr;
		SOCKET sock;
		int size;
		int connection_type_;
		SOCKET res_accept_connection;
		
};

static HWND hEdit = NULL;
HINSTANCE savehinst = NULL;
static HWND hButton = NULL;
static HWND hButton2 = NULL;
HWND hEdit2 = NULL;













class BUTTON {
public:
	COLORREF background_color = RGB(255, 0, 255);
	COLORREF text_color = RGB(255,255,0);
	int text_x=0, text_y=0;
	int height = 100;
	int width = 100;
	int x = 10;
	int y = 10;
	DWORD flags_style = WS_CHILD | WS_VISIBLE | WS_BORDER | BS_OWNERDRAW;
	const char* button_text = "CLICK";
	int text_length=5;
	HMENU onclick_number = NULL;
	function<void()>onclick_func;
	HWND button_hwnd;
	void onclick_do_action(){
		onclick_func();
	}
	HWND return_hwnd(){
		return button_hwnd;
	}
private:
	
};


vector<BUTTON>all_buttons;
vector<HWND>all_hwnds;
int counter = 0;
LRESULT WINAPI WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lparam)
{



	switch (uMsg)
	{
		case WM_CTLCOLORSTATIC :
		{
			SetTextColor(GetDC(all_hwnds[0]), all_buttons[0].text_color);
			
		}
		case WM_CTLCOLORBTN:
		{
		
			/*for (int i = counter; i < all_buttons.size(); i++)
			{
				if (counter >= all_buttons.size())counter = 0;
				HDC hdcButton = GetDC(all_hwnds[i]);
				HBRUSH hb = CreateSolidBrush((all_buttons[i].background_color));
				SetBkColor(hdcButton, all_buttons[i].background_color);
				SetTextColor(hdcButton, RGB(255, 255, 255));
				TextOut(hdcButton, 5, 5, "HALO BICH", 10);
				counter++;
			
				return (long)hb;
			}*/
			/*for (int i = 0; i < all_hwnds.size(); i++)
			{
				RECT rect; GetClientRect(all_hwnds[i], &rect);
				HBRUSH brush = CreateSolidBrush(all_buttons[i].background_color);

				FillRect(GetDC(all_hwnds[i]), &rect, brush);
				SetTextColor(GetDC(all_hwnds[i]), all_buttons[i].text_color);
				TextOut(GetDC(all_hwnds[i]), all_buttons[i].text_x, all_buttons[i].text_y, all_buttons[i].button_text, all_buttons[i].text_length);
				
				
				
			}*/

			
			TextOut(GetDC(all_hwnds[0]), all_buttons[0].text_x, all_buttons[0].text_y, all_buttons[0].button_text, all_buttons[0].text_length);


			break;
		}

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			
			BeginPaint(hwnd, &ps);
			
			
			EndPaint(hwnd, &ps);
		}

		



		case WM_CREATE:
		{

			all_hwnds.clear();
			for (int i = 0; i < all_buttons.size(); i++)
			{
				HWND take = CreateWindow("BUTTON", all_buttons[i].button_text, all_buttons[i].flags_style
					, all_buttons[i].x, all_buttons[i].y, all_buttons[i].width, all_buttons[i].height, hwnd, HMENU(i), NULL, NULL);
				all_buttons[i].button_hwnd = take;
				all_hwnds.push_back(take);

			}

		}
		return 0;

		case WM_COMMAND:
		{
			for (int i = 0; i < all_buttons.size(); i++)
			{
				if (wParam == (int)all_buttons[i].onclick_number)
				{
					all_buttons[i].onclick_do_action();
				}
			}

			break;
		}

		case WM_DESTROY:
		{
			PostQuitMessage(EXIT_SUCCESS);
		}
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lparam);
}














class FORM : BUTTON{
public:
	
	

	
	COLORREF background_color = RGB(255,255,255);
	const char* window_name;
	int height = 500;
	int width = 500;
	int x = 400;
	int y = 400;
	HWND main_hwnd = NULL;
	DWORD flags_style = WS_OVERLAPPEDWINDOW;

	void start()
	{
		wWinMain(hInstance, NULL, szCmdLine, nCmdShow);
	}

	void AddElement(BUTTON btn)
	{
		all_buttons.push_back(btn);
	}

	
	

private:
	HINSTANCE hInstance = NULL;
	PWSTR szCmdLine = NULL;
	int nCmdShow = 1;
	
	int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow)
	{
		WNDCLASSEX wc{ sizeof(WNDCLASSEX) };

		MSG msg{};
		HWND hwnd{};
		HBRUSH background = CreateSolidBrush(background_color);
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hbrBackground = reinterpret_cast<HBRUSH>(background);
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
		wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
		wc.hInstance = hInstance;
		wc.lpfnWndProc = WndProc;
		wc.lpszClassName = "MyappClass";
		wc.lpszMenuName = nullptr;
		wc.style = CS_VREDRAW | CS_HREDRAW;

		if (!RegisterClassEx(&wc))
			return EXIT_FAILURE;

		hwnd = CreateWindow(wc.lpszClassName, window_name, flags_style, x, y, width, height, nullptr, nullptr, wc.hInstance, nullptr);


		ShowWindow(hwnd, nCmdShow);
		UpdateWindow(hwnd);

		main_hwnd = hwnd;


		while (GetMessage(&msg, nullptr, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return static_cast<int>(msg.wParam);
	}



	

};

float main_pressed = clock(); // Время нажатия
float time_pressed = clock(); // Время нажатия
float save_time = 0;
int counter_start = 0;
bool hidden_press = false;
vector<int>keys; // Клавиши
vector<int>time_to_press; // Время нажатий клавиш
bool flag_active = true; // Контроль записи нажатий
PKBDLLHOOKSTRUCT pHook; // КНОПКА 


HHOOK hook; //
float end_pressed = 0;
LRESULT CALLBACK toHook(int iCode, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
		
		case WM_KEYDOWN:
		{
			if (hidden_press) {
				end_pressed = clock();
				time_pressed = end_pressed - main_pressed;
				time_to_press.push_back(time_pressed);
				keys.push_back(127);
				main_pressed = clock();
				hidden_press = false;
			}

			
			if (counter_start < 1) {
				main_pressed = clock();
				counter_start++;
			}
			/*else {
				
				time_pressed = clock();
				save_time += time_pressed-main_pressed;
			}*/
			
			
			
			
			
			
			
			//cout << "key: " << (char)pHook->vkCode << " time: " << time_pressed << " mlsek" << endl;
			
			
			

			
			break;
		}
		
		case WM_KEYUP:
		{
			if (hidden_press) {
				end_pressed = clock();
				time_pressed = end_pressed - main_pressed;
				time_to_press.push_back(time_pressed * 1);
				keys.push_back(pHook->vkCode);
			}
			else {
				pHook = (PKBDLLHOOKSTRUCT)lParam;

				if (pHook->vkCode == 90) {
					cout << "END RECORDING\n";
					UnhookWindowsHookEx(hook);
					PostQuitMessage(0);
					break;
				}

				end_pressed = clock();

				time_pressed = end_pressed - main_pressed;
				time_to_press.push_back(time_pressed * 1);
				keys.push_back(pHook->vkCode);
				//cout << time_pressed <<endl;
				main_pressed = clock();
				//counter_start = 0;
				hidden_press = true;
				save_time = 0;
			}
			
			break;
		}
		
		
	}
	return CallNextHookEx(NULL, iCode, wParam, lParam);
}


class KEYBOARD {
public:
	
	
	void start_record()
	{
		wWinMain(hInstance, NULL, szCmdLine, nCmdShow);
	}
	void stop_record()
	{
		flag_active = false;
	}

	void play_record()
	{
		SMOKOT smokot;
		if (keys.size() == time_to_press.size())
		{
			cout << "ALL GOOD";
		}
		else {
			cout << "SHIT";
		}
		for (int i = 0; i < keys.size(); i++)
		{
			
			smokot.keyboard(keys[i], false);
			Sleep(time_to_press[i]);
			smokot.keyboard(keys[i], true);

		}
	}
	
	

private:
	HINSTANCE hInstance = NULL;
	PWSTR szCmdLine = NULL;
	int nCmdShow = 1;
	

	


	int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow)
	{
		MSG msg{};
		time_pressed = clock();
		
		hook = SetWindowsHookEx(WH_KEYBOARD_LL, toHook, 0, 0);
		while (GetMessage(&msg, 0, 0, 0))
		{

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return static_cast<int>(msg.wParam);
	}
	
};

