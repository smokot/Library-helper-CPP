# Library-helper-C++
Библиотека для конвертации типов и остальные функции ````````
` GetPixelColor_One ` - Получаем цвет пикселя первый вариант

``` C++
GetPixelColor_One obj;
obj.GetColor(0, 0);
cout << obj.r << " " << obj.g << " " << obj.b;

//output 45 45 48
```


` GetPixelColor_Two ` - Получаем цвет пикселя второй вариант

```
SMOKOT smokot;
std::tuple<int,int,int> take = smokot.GetPixelColor_Two(0, 0);
cout << get<0>(take) << " " << get<1>(take) << " " << get<2>(take);
 ```
