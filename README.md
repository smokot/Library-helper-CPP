# Library-helper-C++
Library for Convert of types and other functions

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
smokot.keyboard(VK_F9);
smokot.keyboard(VK_F9, KEYEVENTF_EXTENDEDKEY);

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
