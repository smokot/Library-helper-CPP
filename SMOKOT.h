#pragma once
#pragma comment(lib,"ws2_32.lib")
#include <WS2tcpip.h>
#include "winsock2.h"
#pragma warning(disable:4996)


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
	private:
		WSAData WS;
		SOCKADDR_IN addr;
		SOCKET sock;
		int size;
		int connection_type_;
		SOCKET res_accept_connection;
		
};


