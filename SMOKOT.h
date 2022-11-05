#pragma once
#pragma comment(lib,"ws2_32.lib")
#include <WS2tcpip.h>
#include "winsock2.h"
#pragma warning(disable:4996)
#include "iostream"
#include <functional>
#include "fstream"
#include "string"
#include "windows.h"
#include "sstream"
#include "vector"
#include <algorithm>
#include "tuple"
#include "string"
#include "ctime"
#include <utility>
#include <thread>
#include <functional>
#include <gdiplus.h>
#pragma comment(lib, "GdiPlus.lib")
using namespace std;
using namespace Gdiplus;

typedef vector<vector<float>>matrix;
static const GUID png =
{ 0x557cf406, 0x1a04, 0x11d3, { 0x9a, 0x73, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e } };

struct  {
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
}GetPixelColor_One;

class BUTTON {
public:
	COLORREF background_color = RGB(255, 0, 255);
	COLORREF text_color = RGB(255, 255, 0);
	int text_x = 0, text_y = 0;
	int height = 100;
	int width = 100;
	int x = 10;
	int y = 10;
	DWORD flags_style = WS_CHILD | WS_VISIBLE | WS_BORDER | BS_OWNERDRAW;
	const char* button_text = "CLICK";
	int text_length = 5;
	HMENU onclick_number = NULL;
	function<void()>onclick_func;
	HWND button_hwnd;
	void onclick_do_action() {
		onclick_func();
	}
	HWND return_hwnd() {
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
	case WM_CTLCOLORSTATIC:
	{
		SetTextColor(GetDC(all_hwnds[0]), all_buttons[0].text_color);
		break;

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
		break;
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

	case WM_SIZE:
	{

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






class FORM : BUTTON {
public:

	COLORREF background_color = RGB(255, 255, 255);
	const char* window_name;
	int height = 500;
	int width = 500;
	int x = 400;
	int y = 400;
	HWND main_hwnd = NULL;
	DWORD flags_style = WS_OVERLAPPEDWINDOW;

	
	void init()
	{
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)start, this, 0, NULL);
	}

	void AddElement(BUTTON btn)
	{
		all_buttons.push_back(btn);
	}


private:
	HINSTANCE hInstance = NULL;
	PWSTR szCmdLine = NULL;
	int nCmdShow = 1;

	static void start(FORM* pointer)
	{
		pointer->wWinMain(pointer->hInstance, NULL, pointer->szCmdLine, pointer->nCmdShow);
	}
	

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


class Graphic{
public:
	
	HDC dc;
	
	int formWidth, formHeight;
	void setDC(HDC _dc) {
		dc = _dc;
	}

	
	template<typename nums>
	void updateGraphic(vector<nums> data, bool left_score, bool text_value, COLORREF dot_color, COLORREF line_color, int size)
	{
		int max_num = max_value(data);
		vector<nums>data_copy_forLines;
		for (int i = 0; i < data.size(); i++)
		{
			data_copy_forLines.push_back(data[i]);
		}


		vector<nums>data_pos_step;
		vector<nums>data_pos_value;
		vector<nums>data_sorted;

		int size_dot = size * 2;

		

		while (1) {
			
			draw_line(5, 0, 5, formHeight - 50, line_color, size, dc); // Y osi
			draw_line(5, formHeight - 50, formWidth, formHeight - 50, line_color, size, dc); // X osi

			std::sort(data.begin(), data.end());
			data.resize(unique(data.begin(), data.end()) - data.begin());
			data_sorted = reverse_vec(data);

			
			//--------Draw data nums--------//
			for (int i = 0, step = 0; i < data_sorted.size(); i++, step += (formHeight / data.size()) - 3)
			{
				float value = data_sorted[i];
				string word = float_to_string(value);
				auto out = string_to_char(word);
				data_pos_step.push_back(step);
				data_pos_value.push_back(value);
				if (left_score) {
					draw_text(dc, 5, step, out);
					draw_text(dc, 5, step, out);
				}
				
			}
			
			//--------Save data poses--------//
			vector<nums>out_poses;
			for (int i = 0; i < data_copy_forLines.size(); i++)
			{
				for (int j = 0; j < data_pos_value.size(); j++)
				{
					if (data_copy_forLines[i] == data_pos_value[j]) {
						out_poses.push_back(data_pos_step[j]);
						break;
					}
				}
			}



			int lastX = formWidth;
			int lastY = formHeight;
			for (int i = 0, step = (formWidth / data_copy_forLines.size()/2); i < out_poses.size(); i++, step += (formWidth / data_copy_forLines.size())-1)
			{
				string value = float_to_string(data_copy_forLines[i]);
				auto out_value = string_to_char(value);
				if (i == 0) {
					//draw_line(lastX, lastY, lastX, lastY, RGB(25, 25, 25), 2, dc);
					if (text_value) {
						draw_text(dc, step, out_poses[i], out_value);
						draw_text(dc, step, out_poses[i], out_value);
					}
					
					lastX = step;
					lastY = out_poses[i];
					continue;
				}
				draw_line(lastX, lastY, step, out_poses[i], line_color, size, dc);
				draw_dot(dc, lastX, lastY, dot_color, size_dot);
				
				if (text_value) {
					draw_text(dc, step, out_poses[i], out_value);
					draw_text(dc, step, out_poses[i], out_value);
				}
				lastX = step;
				lastY = out_poses[i];
			}
			
			

			Sleep(300);
		}

	}
	


private:
	
	template<typename nums>
	vector<nums>reverse_vec(vector<nums>arr)
	{
		vector<nums>result;
		for (int i = arr.size()-1; i >= 0; i--)
		{
			result.push_back(arr[i]);
		}
		return result;
	}

	template<typename nums>
	nums max_value(vector<nums>arr)
	{
		nums max = 0;
		for (int i = 0; i < arr.size(); i++)
		{
			if (max < arr[i]) {
				max = arr[i];
			}
		}
		return max;
	}
	void draw_dot(HDC dc, int x, int y, COLORREF ref, int pen_size)
	{
		HPEN pen = CreatePen(PS_SOLID, pen_size, ref);
		SelectObject(dc, pen);
		POINT point;
		MoveToEx(dc, x, y, &point);
		LineTo(dc, x, y);
	}

	void draw_line(int x, int y, int x2, int y2, COLORREF color, int pen_size, HDC dc = NULL)
	{
		HPEN pen = CreatePen(PS_SOLID, pen_size, color);
		SelectObject(dc, pen);
		POINT point;
		MoveToEx(dc, x, y, &point);
		LineTo(dc, x2, y2);
	}
	void draw_text(HDC dc, int x, int y, char* str)
	{
		TextOut(dc, x, y, str, strlen(str));
	}
	string float_to_string(float x)
	{
		string result = "";
		stringstream ss;
		ss << x;
		result = ss.str();
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
	char* string_to_char(std::string x) // ПЕРЕВОД STRING В CHAR
	{
		int size = x.size(); size++;
		char* ch = new char[size];
		ZeroMemory(ch, size);
		for (int i = 0; i < size; i++) {
			ch[i] = x[i];
		}
		ch[size] = '\0';
		char* out = ch;
		//delete[] ch;
		return ch;
	}
};


class SMOKOT {
public:


	template<typename nums>
	void createGraphic(FORM graphic, vector<nums>data, bool left_score, bool text_value, COLORREF dot_color, COLORREF line_color, int size)
	{
		HWND hwnd = FindWindow(NULL, graphic.window_name);
		while(!hwnd) {
			hwnd = FindWindow(NULL, graphic.window_name);
			Sleep(1000);
		}
		SMOKOT smokot;
		HDC dc = GetDC(hwnd);
		Graphic graph;
		graph.formWidth = graphic.width;
		graph.formHeight = graphic.height;
		graph.setDC(dc);
		graph.updateGraphic(data, left_score, text_value,dot_color, line_color , size);
	}

	vector<int> min_nums(vector<int>nums)
	{
		vector<int> res = { nums[0] };
		int save = 0;
		for (int i = 0; i < nums.size(); i++)
		{
			if (nums[i] < res[0]) {
				res[0] = nums[i];
				save = i;
			}
		}
		res.push_back(save);
		return res;
	}

	float Monochrome(COLORREF cr)
	{
		// два любых опорных цвета
		const COLORREF black = 0;
		const COLORREF white = 0x00ffffff;
		const COLORREF gray = RGB(20, 20, 20);
		const COLORREF gray2 = RGB(70, 70, 70);
		const COLORREF gray3 = RGB(120, 120, 120);

		// квадрат расстояния до первой опорной точки
		int blackR = int(GetRValue(cr)) - int(GetRValue(black));
		int blackG = int(GetGValue(cr)) - int(GetGValue(black));
		int blackB = int(GetBValue(cr)) - int(GetBValue(black));
		unsigned blackDist = blackR * blackR + blackG * blackG + blackB * blackB;

		// квадрат расстояния до второй опорной точки
		int whiteR = int(GetRValue(cr)) - int(GetRValue(white));
		int whiteG = int(GetGValue(cr)) - int(GetGValue(white));
		int whiteB = int(GetBValue(cr)) - int(GetBValue(white));
		unsigned whiteDist = whiteR * whiteR + whiteG * whiteG + whiteB * whiteB;

		// квадрат расстояния до третьей опорной точки
		int grayR = int(GetRValue(cr)) - int(GetRValue(gray));
		int grayG = int(GetGValue(cr)) - int(GetGValue(gray));
		int grayB = int(GetBValue(cr)) - int(GetBValue(gray));
		unsigned grayDist = grayR * grayR + grayG * grayG + grayB * grayB;

		int grayR2 = int(GetRValue(cr)) - int(GetRValue(gray2));
		int grayG2 = int(GetGValue(cr)) - int(GetGValue(gray2));
		int grayB2 = int(GetBValue(cr)) - int(GetBValue(gray2));
		unsigned grayDist2 = grayR2 * grayR2 + grayG2 * grayG2 + grayB2 * grayB2;

		int grayR3 = int(GetRValue(cr)) - int(GetRValue(gray3));
		int grayG3 = int(GetGValue(cr)) - int(GetGValue(gray3));
		int grayB3 = int(GetBValue(cr)) - int(GetBValue(gray3));
		unsigned grayDist3 = grayR3 * grayR3 + grayG3 * grayG3 + grayB3 * grayB3;


		if (blackDist < whiteDist &&  blackDist < grayDist && blackDist < grayDist2 && blackDist < grayDist3) {
			return 1;
		}
		else if (whiteDist < blackDist && whiteDist < grayDist && whiteDist < grayDist2 && whiteDist < grayDist3) {
			return 2;
		}
		else if (grayDist < blackDist && grayDist < whiteDist && grayDist < grayDist2 && grayDist < grayDist3) {
			return 3;
		}
		else if (grayDist2 < blackDist && grayDist2 < whiteDist && grayDist2 < grayDist && grayDist2 < grayDist3) {
			return 4;
		}
		else if (grayDist3 < blackDist && grayDist3 < whiteDist && grayDist3 < grayDist && grayDist3 < grayDist2) {
			return 5;
		}
		else {
			return 0;
		}

		/*vector<int>vec;
		vec.push_back(blackDist);
		vec.push_back(whiteDist);
		vec.push_back(grayDist);
		vec.push_back(grayDist2);
		vec.push_back(grayDist3);
		
		// проверяем какое расстояние меньше
		vector<int>result = min_nums(vec);
		if (result[1] == 0) {
			return 1;
		}
		if (result[1] == 1) {
			return 2;
		}
		if (result[1] == 2) {
			return 3;
		}
		if (result[1] == 3) {
			return 4;
		}
		if (result[1] == 4) {
			return 5;
		}*/
		
		
		//return (whiteDist < blackDist) ? 0 : 1;
	}

	//-------------------------------------------------------------------------------------------------
	// преобразовании горизонтальной пиксельной линии в текстовую строку
	//-------------------------------------------------------------------------------------------------
	void TranslateLine(COLORREF* line, int cx, std::string& str)
	{
		// очищаем строку
		str.clear();

		// пробегаемся по всем пикселях одной горизонтальной линии картинки
		for (int i = 0; i < cx; i++)
		{
			// добавляем в строку '0' или '1' в зависимости от цвета пикселя (заменить ' ' на '0')
			if (Monochrome(line[i]) == 0) {
				str.push_back('0');
			}
			if (Monochrome(line[i]) == 1) {
				str.push_back('0');
			}
			if (Monochrome(line[i]) == 2) {
				str.push_back('1');
			}
			if (Monochrome(line[i]) == 3) {
				str.push_back('2');
			}
			if (Monochrome(line[i]) == 4) {
				str.push_back('3');
			}
			if (Monochrome(line[i]) == 5) {
				str.push_back('4');
			}
			//str.push_back(Monochrome(line[i]) ? '1' : '0'/*'0'*/);
		}
	}

	//-------------------------------------------------------------------------------------------------
	// преобразование картинки в текст
	//-------------------------------------------------------------------------------------------------
	void Bitmap_To_Txt(HBITMAP hbmp, std::string& text)
	{
		// очищаем строку
		text.clear();

		// достаём размеры картинки
		BITMAP bm = {};
		GetObject(hbmp, sizeof(bm), &bm);

		// небольшая проверка
		if (bm.bmHeight <= 0 || bm.bmWidth <= 0)
			return;

		// буфер под горизонтальную линию картинки
		std::vector<char> line;
		line.resize(bm.bmWidthBytes);

		//
		HDC hDC = GetDC(0);
		//
		BITMAPINFO bmi = {};
		bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
		bmi.bmiHeader.biWidth = bm.bmWidth;
		bmi.bmiHeader.biHeight = bm.bmHeight;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 32;
		bmi.bmiHeader.biCompression = BI_RGB;
		bmi.bmiHeader.biSizeImage = bm.bmWidth * bm.bmHeight * 4;

		// пробегаемся по всем горизонтальным линиям картинки
		for (int i = 0; i < bm.bmHeight; i++)
		{
			// чтение одной горизонтальной линии (bm.bmHeight-i-1 - вертикальное отражение)
			GetDIBits(hDC, hbmp, bm.bmHeight - i - 1, 1, line.data(), &bmi, DIB_RGB_COLORS);

			// формирование из линии текстовой строки
			std::string str;
			TranslateLine((COLORREF*)line.data(), bm.bmWidth, str);

			// формирование всего текста
			text += str + "\n";
		}

		ReleaseDC(0, hDC);
	}


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

	int char_number(char x)
	{
		switch (x) {
		case '0':
			return 0;
			break;
		case '1':
			return 1;
			break;
		case '2':
			return 2;
			break;
		case '3':
			return 3;
			break;
		case '4':
			return 4;
			break;
		case '5':
			return 5;
			break;
		case '6':
			return 6;
			break;
		case '7':
			return 7;
			break;
		case '8':
			return 8;
			break;
		case '9':
			return 9;
			break;
		}
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
		
		x2 = x2 - x1;
		y2 = y2 - y1;

		HDC scrdc, memdc;
		HBITMAP membit;

		scrdc = GetDC(0);

		memdc = CreateCompatibleDC(scrdc);
		membit = CreateCompatibleBitmap(scrdc, x2, y2);
		SelectObject(memdc, membit);

		

		BitBlt(memdc, 0, 0, x2, y2, scrdc, x1, y1, SRCCOPY);

		//BitBlt(memdc, 0, 0, x2, y2, scrdc, x1, y1, SRCCOPY);
		HBITMAP hBitmap;
		hBitmap = (HBITMAP)SelectObject(memdc, membit);

		
		ReleaseDC(NULL, scrdc);
		DeleteDC(memdc);
		
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

	string float_to_string(float x)
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

	int char_to_int(char* x)
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
	void draw_line(int x, int y, int x2, int y2, COLORREF color, int pen_size, HDC dc = NULL )
	{
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



              //-----NEURO-----//
//------------------------------------------//

class Neuro{
public:	

	float relu2deriv(float x)
	{
		return (x > 0);
	}

	float relu(float x)
	{
		return (x > 0) * x;	
	}

	template<typename numbers>
	vector<vector<numbers>> transpon(vector<vector<numbers>>vec, int size)
	{
		vector<vector<numbers>>result;
		result.resize(size);
		for (int i = 0; i < vec[0].size(); i++)
		{
			for (int j = 0; j < vec.size(); j++)
			{
				result[i].push_back(vec[j][i]);
			}
		}

		return result;
	}

	template<typename numbers>
	vector<numbers> transpon(vector<numbers>vec)
	{
		vector<numbers>result;
		result.resize(vec.size());

		for (int i = 0; i < vec[0].size(); i++)
		{
			for (int j = 0; j < vec.size(); j++)
			{
				result[i].push_back(vec[j][i]);
			}
		}

		return result;
	}



	template<typename numbers>
	void unload_weights(string path, vector<vector<numbers>>weigths)
	{
		ofstream file; file.open(path);
		for (int i = 0; i < weigths.size(); i++)
		{
			file << weigths[i] << ",";
		}
		file.close();
	}

	template<typename numbers>
	void load_weights(string path, vector<vector<numbers>>& weigths)
	{
		ifstream file(path);
		SMOKOT smokot;
		string take;
		while (!file.eof())
		{
			file >> take;
		}

		string swap;

		for (int i = 0; i < take.size(); i++)
		{
			float num;
			if (take[i] == ',') {


				num = atof(swap.c_str());

				weigths.push_back(num);
				swap = "";
				continue;
			}
			swap += take[i];

		}

		file.close();
	}



	template<typename numbers>
	void unload_weights(string path, vector<numbers>weigths)
	{
		ofstream file; file.open(path);
		for (int i = 0; i < weigths.size(); i++)
		{
			file << weigths[i] << ",";
		}
		file.close();
	}

	template<typename numbers>
	void load_weights(string path, vector<numbers>& weigths)
	{
		ifstream file(path);
		SMOKOT smokot;
		string take;
		while (!file.eof())
		{
			file >> take;
		}

		string swap;

		for (int i = 0; i < take.size(); i++)
		{
			float num;
			if (take[i] == ',') {


				num = atof(swap.c_str());

				weigths.push_back(num);
				swap = "";
				continue;
			}
			swap += take[i];

		}

		file.close();
	}


	template<typename numbers>
	vector<numbers> weight_sum(vector<numbers>vec1, vector<vector<numbers>>vec2, string reludiv)
	{
		vector<numbers>output;
		if (reludiv == "relu") {
			
			if (vec1.size() != vec2.size())
				return output;

			for (int m = 0; m < vec2[0].size(); m++)
			{
				float res = 0;
				for (int i = 0; i < vec1.size(); i++)
				{
					res += vec1[i] * vec2[i][m];

				}
				output.push_back(relu(res));
			}
		}
		else if (reludiv == "relu2deriv") {

			
			if (vec1.size() != vec2.size())
				return output;

			for (int m = 0; m < vec2[0].size(); m++)
			{
				float res = 0;
				for (int i = 0; i < vec1.size(); i++)
				{
					res += vec1[i] * vec2[i][m];

				}
				output.push_back(relu2deriv(res));
			}
		}
		
		

		return output;
	}


	template<typename numbers>
	numbers weight_sum(vector<numbers>vec1, vector<numbers>vec2)
	{
		numbers res = 0;
		
		if (vec1.size() != vec2.size())
			return -1;

		for (int i = 0; i < vec1.size(); i++)
		{
			res += vec1[i] * relu(vec2[i]);
		}

		return res;
	}



	template<typename numbers>
	vector<numbers>ele_mul(numbers num, vector<numbers>vec2)
	{
		vector <numbers>result;
		result.resize(vec2.size());
		
		if (result.size() != vec2.size())
			return (result);
		
		for (int i = 0; i < vec2.size(); i++)
		{
			result[i]= num * vec2[i];
		}

		return result;
	}


	template<typename numbers>
	vector<numbers>vec_mat_mul(vector<numbers> num, vector<vector<numbers>>vec2)
	{
		vector<numbers>result;
		result.resize(num.size());


		if (num.size() != vec2.size())
			return (result);

		for (int i = 0; i < num.size(); i++)
		{	
			result[i] = weight_sum(num, vec2[i]);
		}

		return result;
	}

	template<typename num>
	void training(vector<vector<num>>input, vector<num>&weights, vector<num>goals,  float alpha, int epoch)
	{
		
		for (int i = 0; i < epoch; i++) {
			
			for (int j = 0; j < goals.size(); j++) {
				
				float prediction = weight_sum(input[j], weights);
				float error = pow((prediction - goals[j]), 2);
				float delta = (prediction - goals[j]);
				vector<num> w_delta = ele_mul(delta, input[j]);
				for (int m = 0; m < w_delta.size(); m++) {
					weights[m] -= w_delta[m] * alpha;
				}
				
			}
		}
	}

	
	vector<float> training(float input, float &weight, float goal, float alpha, int epoch)
	{
		vector<float>errors;
		for (int i = 0; i < epoch; i++) {
			float prediction = input * weight;
			float error = pow((prediction - goal), 2);
			errors.push_back(error);
			cout << error << endl;
			float delta = (prediction - goal) * input;
			weight -= delta * alpha;	
		}
		return errors;
	}

	float predict(float input, float weight)
	{
		return input * weight;
	}

	template<typename numbers>
	float predict(vector<numbers> input, vector<numbers> weight)
	{
		return weight_sum(input, weight);
	}

	template<typename numbers>
	void load_inputs(vector<vector<numbers>>&vec, vector<numbers>&goals, string path)
	{
		ifstream file(path);
		SMOKOT smokot;
		string line;
		int counter = 0;
		vec.resize(10001);
		bool flag = false;
		while (!file.eof())
		{
			file >> line;
			for (int i = 0; i < line.size(); i++)
			{
				if (line[i] == '=')
				{
					string save;
					for (int j = i+1; j < line.size(); j++)
					{
						save += line[j];
						flag = true;
					}
					goals.push_back(smokot.string_to_int(save));
					continue;
				}
				if (flag) {
					flag = false;
					break;
				}
				if (line[i] == '|')
				{
					counter++;
					continue;
				}
				vec[counter].push_back((float)smokot.char_number(line[i])/100);
				
			}
			
			
		}
		
	}


	template<typename numbers>
	void generate_weights(vector<vector<numbers>>& vec,int vec_size ,int quantity)
	{
		vec.resize(vec_size);
		
		srand(time(0));
		for (int m = 0; m < vec_size; m++)
		{
			for (int i = 0; i < quantity; i++)
			{
				int number = rand() % 3;
				switch (number) {
				case 0:
					vec[m].push_back(0.001);
					break;
				case 1:
					vec[m].push_back(0.002);
					break;
				case 2:
					vec[m].push_back(0.003);
					break;
				case 3:
					vec[m].push_back(0.004);
					break;
				}
			}
		}

		
	}



	template<typename numbers>
	void generate_weights(vector<numbers>& vec, int quantity)
	{
		srand(time(0));
		for (int i = 0; i < quantity; i++)
		{
			int number = rand() % 3;
			switch (number) {
				case 0:
					vec.push_back(0.001);
				break;

				case 1:
					vec.push_back(0.002);
					break;
				case 2:
					vec.push_back(0.003);
					break;
				case 3:
					vec.push_back(0.004);
					break;
			}
		}
	}
};