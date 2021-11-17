#pragma once

#include "string"
#include "windows.h"
#include "sstream"
#include "vector"
#include "tuple"

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
	void keyboard(DWORD key, DWORD flag)
	{
		
		INPUT input;
		input.type = INPUT_KEYBOARD;
		input.ki.wVk = key;
		input.ki.dwFlags = flag;
		SendInput(1, &input, sizeof(input));	
	}
	//Example: key = VK_F9
	void keyboard(DWORD key)
	{
		INPUT input;
		input.type = INPUT_KEYBOARD;
		input.ki.wVk = key;
		input.ki.dwFlags = KEYEVENTF_EXTENDEDKEY;

		SendInput(1, &input, sizeof(input));

		input.ki.wVk = key;
		input.ki.dwFlags = KEYEVENTF_KEYUP;
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
		bitmap.Save(path, &png); //Ñîõðàíÿë äëÿ ïðîâåðêè

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



	char * string_to_char(std::string x) // ÏÅÐÅÂÎÄ STRING Â CHAR
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

	std::string char_to_string(char*x) // ÏÅÐÅÂÎÄ CHAR Â STRING
	{
		int size = strlen(x);
		std::string word = "";
		for (int i = 0; i < size; i++)
		{
			word += x[i];
		}
		return word;
	}
	void msg_box(LPCSTR word, LPCSTR title) // ÓÏÐÎÙÅÍÍÛÉ MessageBox
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

};


