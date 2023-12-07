
***//====CHI====//***

`bsp.c/.h` 是外部設備統整的地方，有助於管理外設初始化並減少 `main.c` 的程式碼大小。主要關注於 `button.c/.h`，將其整合到專案後需注意以下事項：

在 `button.c` 中：
```c
Button_t Button1; // 按鈕宣告
Read_KEY1_Level(); // 需要實現的讀取 Pin 腳電位的函數
```

在 `button.h` 中：
```c
#define KEY_ON	0		// 根據電路圖設定按鈕觸發電位
// 其他參數定義可調整
```






***//====ENG====//***

`bsp.c/.h` is where external devices are organized to facilitate the management of peripheral initialization and reduce the size of the `main.c` code. Mainly, `button.c/.h` should be the focus after integrating it into your project.

In `button.c`:
```c
Button_t Button1; // Button declaration
Read_KEY1_Level(); // The function for reading pin potential needs to be implemented
```

In `button.h`:
```c
#define KEY_ON 0 // Set the button trigger potential according to the circuit diagram
// Other parameter definitions can be adjusted
```

