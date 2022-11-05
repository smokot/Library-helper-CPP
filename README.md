# Library-helper-C++
Library for Convert of types and other functions

`1)mouse/keyboard Emulation`

`2)Work with Screen`

`3)NETWORK TCP-UDP/ip commands`

`4)Convertation of default datatypes`

`5)FORMS, Buttons` (BETA)

and other..


` createGraphic ` - Creating 2D Graphic with your data

``` 
SMOKOT smokot;
FORM graphic;
graphic.window_name = "graphic";
graphic.init();      
COLORREF dot_color = RGB(0, 0, 255);
COLORREF line_color = RGB(0, 0, 0);
int size = 5;
vector<float>inps = { 0.0722, 0.11, 0.05, 0.07, 0.06,0.16,0.10,0.07,0.11,0.17,0.23,0.20,0.26};
smokot.createGraphic(graphic, inps, true, true, dot_color, line_color, size); // where flag left_score = true, text_value = true
![image](https://user-images.githubusercontent.com/58879890/200120775-f7e64bd0-9481-4ba3-8c71-bdd2d80ab38f.png)


smokot.createGraphic(graphic, inps, true, true, dot_color, line_color, size); // where flag left_score = false, text_value = false
![image](https://user-images.githubusercontent.com/58879890/200120830-7122b749-e2ec-440d-8104-712da2ae0d00.png)


```



` GetPixelColor_One ` - Get color of pixel (V1)

``` C++
GetPixelColor_One obj;
obj.GetColor(0, 0);
cout << obj.r << " " << obj.g << " " << obj.b;

//output: 45 45 48
```


` GetPixelColor_Two ` - Get color of pixel (V2)

```
SMOKOT smokot;
std::tuple<int,int,int> take = smokot.GetPixelColor_Two(0, 0);
cout << get<0>(take) << " " << get<1>(take) << " " << get<2>(take);

//output: 45 45 48
 ```
 
 
` keyboard_write ` - Keyboard writing

````
SMOKOT smokot;
smokot.keyboard_write("Test of the WORLD");

//output: Test of the WORLD
````
` keyboard ` - Press keyboard
````
SMOKOT smokot;
smokot.keyboard(VK_F9, true);
smokot.keyboard(VK_F9, false);

````

` LeftClick/RightClick ` - Mouse click
````
SMOKOT smokot;
smokot.LeftClick();
smokot.RightClick();

````

` Screenshot ` - Screen Region

````
SMOKOT smokot;
HBITMAP bitmap = smokot.Screenshot(0, 0, 100, 100); 
smokot.SaveBitMap(bitmap, L"test.png");

````

` Split ` - Separator in array
````
SMOKOT smokot;
string word = "123.321.456.678";
vector<string> take = smokot.split(word,'.');
for (auto x : take)
{
	cout << x << endl;
}

//output: 
123
321
456
678
````

` int_to_char ` - Convert int in char
````
SMOKOT smokot;
char * take = smokot.int_to_char(228);
cout << take;

//output: "228"
````



` int_to_string ` - Convert int in string 
````
SMOKOT smokot;
string take = smokot.int_to_string(228);
cout << take;

//output: "228"
````


` string_to_int ` - Convert string in int
````
SMOKOT smokot;
int take = smokot.string_to_int("6363");
cout << take;

//output: 6363
````


` char_to_int ` - Convert char in int
````
SMOKOT smokot;
int take = smokot.char_to_int("987");
cout << take;

//output: 987
````

` string_to_char ` - Convert string in char
````
SMOKOT smokot;
char * take = smokot.string_to_char("987");
cout << take;

//output: "987"
````


` char_to_string ` - Convert char in string
````
SMOKOT smokot;
string take = smokot.char_to_string("fafg");
cout << take;

//output: "fafg"
````

` msg_box ` - MessageBox 
````
SMOKOT smokot;
smokot.msg_box("HELLO WORLD", "WARNING");
````

` draw_dot ` - Draw dot in selection region
````
SMOKOT smokot;
smokot.draw_dot(0, 10, (255, 255, 255), 10);
````

` draw_line ` - Draw line
````
SMOKOT smokot;
smokot.draw_line(0, 0, 20, 20, (255, 255, 255), 10);
````


` draw_text ` - Draw text on the Screen
````
SMOKOT smokot;
char text[] = "Garry";
smokot.draw_text(500, 500, text);
````

` b64_encode ` - Encode string to Base64
````
SMOKOT smokot;
string text = "dog";
smokot.b64_encode(text, text.size());
````

` create_sever/connect_server/sock_send/sock_recv/accept_connection ` - Create new TCP/UDP server
````
SMOKOT smokot;
smokot.create_server("127.0.0.1", 25565, SOCK_STREAM);
smokot.connect("127.0.0.1", 25565, SOCK_STREAM);
smokot.sock_send_ss(socket, stringstream);
smokot.sock_send_c(socket, char *);
smokot.sock_recv(buffer, socket);
smokot.accept_connection();
````


