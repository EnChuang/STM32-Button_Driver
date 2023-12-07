#ifndef BUTTON_H
#define BUTTON_H

#include "stdint.h"
#define KEY_ON	0											//按鈕觸發電位

#define BTN_NAME_MAX  32     //按鈕名稱輸入最大值

/* 按鈕消彈時間40ms, 建議調用週期為20ms
 只有連續檢測到40ms狀態不變才認為有效，包括彈起和按下兩種事件
*/

#define CONTINUOS_TRIGGER             0  //是否支持連續觸發，連發的話就不要檢測單雙擊與長按了	


/* 本功能是否支持同時存在單擊和雙擊觸發的情況，若選擇開啟巨集定義，則單擊和雙擊均會觸發，
不過單擊的響應會延遲，因為系統需要判斷單擊之後是否觸發了雙擊，延遲時間為雙擊間隔時間 BUTTON_DOUBLE_TIME。
若不啟用巨集定義，建議在工程中僅保留單擊或雙擊中的一種，以免在雙擊響應時觸發不必要的單擊，因為雙擊需要在一次按下和釋放後才會生成。 */
#define SINGLE_AND_DOUBLE_TRIGGER     1

/* 是否允許僅在長按且釋放後才觸發功能，若啟用此巨集定義，則僅在用戶長按並釋放後才會觸發一次單次長按事件。
反之，若未啟用此定義，則在長按指定時間後將持續觸發長按事件，觸發週期則由 BUTTON_LONG_CYCLE 參數所決定。 */#define LONG_FREE_TRIGGER             0

#define BUTTON_DEBOUNCE_TIME        2   //消除彈跳時間      (n-1)*調用週期
#define BUTTON_CONTINUOS_CYCLE     1	  //連按觸發週期時間  (n-1)*調用週期  
#define BUTTON_LONG_CYCLE          1	  //長按觸發週期時間  (n-1)*調用週期 
#define BUTTON_DOUBLE_TIME         25  //雙擊間隔時間  (n-1)*調用週期  建議在200-600ms
#define BUTTON_LONG_TIME            150  /* 持續n秒((n-1)*調用週期 ms)，認為長按事件 */

#define TRIGGER_CB(event)   \
        if(btn->CallBack_Function[event]) \
          btn->CallBack_Function[event]((Button_t*)btn)

typedef void (*Button_CallBack)(void*);   /* 按鈕觸發回調函數，需要用戶實現 */



typedef enum {
    BUTTON_DOWM = 0,
    BUTTON_UP,
    BUTTON_DOUBLE,
    BUTTON_LONG,
    BUTTON_LONG_FREE,
    BUTTON_CONTINUOS,
    BUTTON_CONTINUOS_FREE,
    BUTTON_ALL_RIGGER,
    number_of_event, /* 觸發的callback事件 */
    NONE_TRIGGER
} Button_Event;

/*每個按鍵所對應的結構體變量。*/
typedef struct button
{
    uint8_t (*Read_Button_Level)(void); /* 讀取按鍵電位函數，需要用戶自己實現 */

    char Name[BTN_NAME_MAX];

    uint8_t Button_State : 4;										/* 按鍵當前狀態（按下還是彈起） */
    uint8_t Button_Last_State : 4;						/* 上一次的按鍵狀態，用於判斷雙擊 */
    uint8_t Button_Trigger_Level : 2;				/* 按鍵觸發電平 */
    uint8_t Button_Last_Level : 2;						/* 按鍵當前電位 */
    uint8_t Button_Trigger_Event;     			/* 按鍵觸發事件，單擊，雙擊，長按等 */
    Button_CallBack CallBack_Function[number_of_event];
    uint8_t Button_Cycle;	           						/* 按鍵週期 */
    uint8_t Timer_Count;												/* 計時 */
    uint8_t Debounce_Time;										/* 消除彈跳時間 */
    uint8_t Long_Time;		 											 /* 長按設定時間 */
    struct button *Next;
} Button_t;

/* 供外部調用的函數聲明 */
void	Button_Inital(void);
void Button_Create(const char *name,Button_t *btn,uint8_t(*read_btn_level)(void),uint8_t btn_trigger_level);
void Button_Attach(Button_t *btn,Button_Event btn_event,Button_CallBack btn_callback);
void Button_Cycle_Process(Button_t *btn);
void Button_Process(void);
uint8_t Get_Button_Event(Button_t *btn);
uint8_t Get_Button_State(Button_t *btn);
void Button_Process_CallBack(void *btn);
void Btn1_Down_CallBack(void *btn);
void Btn1_Double_CallBack(void *btn);
void Btn1_Long_CallBack(void *btn);
void Btn1_Continuos_CallBack(void *btn);
void Btn1_ContinuosFree_CallBack(void *btn);
void Btn2_Down_CallBack(void *btn);
void Btn2_Double_CallBack(void *btn);
void Btn2_Long_CallBack(void *btn);
void Btn2_Continuos_CallBack(void *btn);
void Btn2_ContinuosFree_CallBack(void *btn);

void Get_Button_EventInfo(Button_t *btn);
void Button_Delete(Button_t *btn);
void Search_Button(void);
#endif
