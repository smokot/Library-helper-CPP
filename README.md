# Library-helper-C++
Библиотека для конвертации типов и остальные функции 

` GetPixelColor_One ` - Получаем цвет пикселя первый вариант

``` C++
GetPixelColor_One obj;
obj.GetColor(0, 0);
cout << obj.r << " " << obj.g << " " << obj.b;

//output: 45 45 48
```


` GetPixelColor_Two ` - Получаем цвет пикселя второй вариант

```
SMOKOT smokot;
std::tuple<int,int,int> take = smokot.GetPixelColor_Two(0, 0);
cout << get<0>(take) << " " << get<1>(take) << " " << get<2>(take);

//output: 45 45 48
 ```
 
 
` keyboard_write ` - Писать с клавиатуры программно

````
SMOKOT smokot;
smokot.keyboard_write("Test of the WORLD");

//output: Test of the WORLD
````
` keyboard ` - Нажатия клавиш
````
SMOKOT smokot;
smokot.keyboard(VK_F9);
smokot.keyboard(VK_F9, KEYEVENTF_EXTENDEDKEY);

````

` LeftClick/RightClick ` - Нажатие мыши
````
SMOKOT smokot;
smokot.LeftClick();
smokot.RightClick();

````

` Screenshot ` - Скрин области экрана

````
SMOKOT smokot;
HBITMAP bitmap = smokot.Screenshot(0, 0, 100, 100); 
smokot.SaveBitMap(bitmap, L"test.png");

````

` Split ` - Split как в Python, C#, добавление в массив после разделителя
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

` int_to_char ` - Конвертация int в char
````
SMOKOT smokot;
char * take = smokot.int_to_char(228);
cout << take;

//output: "228"
````



` int_to_string ` - Конвертация int в string 
````
SMOKOT smokot;
string take = smokot.int_to_string(228);
cout << take;

//output: "228"
````


` string_to_int ` - Конвертация string в int
````
SMOKOT smokot;
int take = smokot.string_to_int("6363");
cout << take;

//output: 6363
````


` char_to_int ` - Конвертация char в int
````
SMOKOT smokot;
int take = smokot.char_to_int("987");
cout << take;

//output: 987
````

` string_to_char ` - Конвертация string в char
````
SMOKOT smokot;
char * take = smokot.string_to_char("987");
cout << take;

//output: "987"
````


` char_to_string ` - Конвертация string в char
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

` draw_dot ` - Рисует точку в указанных координатах
````
SMOKOT smokot;
smokot.draw_dot(0, 10, (255, 255, 255), 10);
````
