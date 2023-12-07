/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
	*	CCE 20231207
	*	Button_Driver v1
	*	
  ******************************************************************************
  */
#include	"main.h"

//USER加入自己的按鍵
Button_t Button1;
Button_t Button2;


/*******************************************************************
 *                          變數聲明
 *******************************************************************/

static struct button* Head_Button = NULL;


/*******************************************************************
 *                         函數聲明
 *******************************************************************/
static char *StrnCopy(char *dst, const char *src, uint32_t n);
static void Add_Button(Button_t* btn);


/************************************************************
  * @brief   按鍵初始化
	* @param   NULL
  * @return  NULL
  * @version v1.0
  * @note    目前實現長按 短按 雙擊
  ***********************************************************/
void	Button_Inital(void)
{
    Button_Create("Button1", &Button1,Read_KEY1_Level,KEY_ON);
    Button_Attach(&Button1,BUTTON_DOWM,Btn1_Down_CallBack);
    Button_Attach(&Button1,BUTTON_DOUBLE,Btn1_Double_CallBack);
//  Button_Attach(&Button1,BUTTON_CONTINUOS,Btn1_Continuos_CallBack);
//  Button_Attach(&Button1,BUTTON_CONTINUOS_FREE,Btn1_ContinuosFree_CallBack);
    Button_Attach(&Button1,BUTTON_LONG,Btn1_Long_CallBack);


    Button_Create("Button2",&Button2,Read_KEY2_Level,KEY_ON);
    Button_Attach(&Button2,BUTTON_DOWM,Btn2_Down_CallBack);
    Button_Attach(&Button2,BUTTON_DOUBLE,Btn2_Double_CallBack);
//  Button_Attach(&Button2,BUTTON_CONTINUOS,Btn2_Continuos_CallBack);
//  Button_Attach(&Button2,BUTTON_CONTINUOS_FREE,Btn2_ContinuosFree_CallBack);
    Button_Attach(&Button2,BUTTON_LONG,Btn2_Long_CallBack);

    Get_Button_Event(&Button1);
    Get_Button_Event(&Button2);
}

/************************************************************
  * @brief   按鍵創建
	* @param   name : 按鍵名稱
	* @param   btn : 按鍵結構體
  * @param   read_btn_level : 按鍵電位讀取函數，需要用戶自己實現返回uint8_t類型
  * @param   btn_trigger_level : 按鍵觸發電位
  * @return  NULL
  * @version v1.0
  * @note    NULL
  ***********************************************************/
void Button_Create(const char *name,
                   Button_t *btn,
                   uint8_t(*read_btn_level)(void),
                   uint8_t btn_trigger_level)
{
    if( btn == NULL)
    {
        //   printf("struct button is null!");
    }

    memset(btn, 0, sizeof(struct button));  //清除結構體信息，建議USER在之前清除

    StrnCopy(btn->Name, name, BTN_NAME_MAX); /* 創建按鍵名稱 */


    btn->Button_State = NONE_TRIGGER;           //按鍵狀態
    btn->Button_Last_State = NONE_TRIGGER;      //按鍵上一次狀態
    btn->Button_Trigger_Event = NONE_TRIGGER;   //按鍵觸發事件
    btn->Read_Button_Level = read_btn_level;    //按鍵讀電位函數
    btn->Button_Trigger_Level = btn_trigger_level;  //按鍵觸發電位
    btn->Button_Last_Level = btn->Read_Button_Level(); //按鍵當前電位
    btn->Debounce_Time = 0;

    //   printf("button create success!");

    Add_Button(btn);          //創建後添加到單鏈表中
}

/************************************************************
  * @brief   按鍵觸發事件與回調函數映射鏈接
	* @param   btn : 按鍵結構體
	* @param   btn_event : 按鍵觸發事件
  * @param   btn_callback : 按鍵觸發之後的回調處理函數。需要USER實現自行
  * @return  NULL
  * @version v1.0
  ***********************************************************/
void Button_Attach(Button_t *btn,Button_Event btn_event,Button_CallBack btn_callback)
{
    if( btn == NULL)
    {
        //   printf("struct button is null!");
    }

    if(BUTTON_ALL_RIGGER == btn_event)
    {
        for(uint8_t i = 0 ; i < number_of_event-1 ; i++)
            btn->CallBack_Function[i] = btn_callback; //按鍵事件觸發的回調函數，用於處理按鍵事件
    }
    else
    {
        btn->CallBack_Function[btn_event] = btn_callback; //按鍵事件觸發的回調函數，用於處理按鍵事件
    }
}


/************************************************************
  * @brief   獲取按鍵觸發的事件訊息並打印
	* @param   NULL
  * @return  NULL
  * @version v1.0
  ***********************************************************/
void Get_Button_EventInfo(Button_t *btn)
{
    //按鍵事件觸發的回調函數，用於處理按鍵事件
    for(uint8_t i = 0 ; i < number_of_event-1 ; i++)
    {
        if(btn->CallBack_Function[i] != 0)
        {
               printf("Button_Event:%d",i);
        }
    }
}

/************************************************************
  * @brief   獲取按鍵觸發的事件
	* @param   NULL
  * @return  NULL
  * @version v1.0
  ***********************************************************/
uint8_t Get_Button_Event(Button_t *btn)
{
    return (uint8_t)(btn->Button_Trigger_Event);
}

/************************************************************
  * @brief   獲取按鍵觸發的事件
	* @param   NULL
  * @return  NULL
  * @version v1.0
  ***********************************************************/
uint8_t Get_Button_State(Button_t *btn)
{
    return (uint8_t)(btn->Button_State);
}

/************************************************************
  * @brief   Button cycle processing function
  * @param   btn: Button to be processed
  * @return  NULL
  * @version v1.0
  * @note    Must be called periodically, suggested cycle is 20~50ms
  ***********************************************************/
void Button_Cycle_Process(Button_t *btn)
{
    uint8_t current_level = (uint8_t)btn->Read_Button_Level(); // Get current button level

    if ((current_level != btn->Button_Last_Level) && (++(btn->Debounce_Time) >= BUTTON_DEBOUNCE_TIME)) // Button level changes, debounce
    {
        btn->Button_Last_Level = current_level; // Update current button level
        btn->Debounce_Time = 0;                 // Confirmed as pressed

        // If the button is not pressed, change the button state to pressed (first press/double press)
        if ((btn->Button_State == NONE_TRIGGER) || (btn->Button_State == BUTTON_DOUBLE))
        {
            btn->Button_State = BUTTON_DOWM;
        }
        // Release the button
        else if (btn->Button_State == BUTTON_DOWM)
        {
            btn->Button_State = BUTTON_UP;
            TRIGGER_CB(BUTTON_UP); // Trigger release
            //   printf("Released the button");
        }
    }

    switch (btn->Button_State)
    {
    case BUTTON_DOWM: // Pressed state
    {
        if (btn->Button_Last_Level == btn->Button_Trigger_Level) // Button pressed
        {
#if CONTINUOS_TRIGGER // Support continuous triggering

            if (++(btn->Button_Cycle) >= BUTTON_CONTINUOS_CYCLE)
            {
                btn->Button_Cycle = 0;
                btn->Button_Trigger_Event = BUTTON_CONTINUOS;
                TRIGGER_CB(BUTTON_CONTINUOS); // Continuous press
                   printf("Continuous press");
            }

#else

            btn->Button_Trigger_Event = BUTTON_DOWM;

            if (++(btn->Long_Time) >= BUTTON_LONG_TIME) // Update trigger event to long press before releasing the button
            {
#if LONG_FREE_TRIGGER

                btn->Button_Trigger_Event = BUTTON_LONG;

#else

                if (++(btn->Button_Cycle) >= BUTTON_LONG_CYCLE) // Continuous triggering period for long press
                {
                    btn->Button_Cycle = 0;
                    btn->Button_Trigger_Event = BUTTON_LONG;
                    TRIGGER_CB(BUTTON_LONG); // Long press
                }

#endif

                if (btn->Long_Time == 0xFF) // Update time overflow
                {
                    btn->Long_Time = BUTTON_LONG_TIME;
                }
                 //  printf("Long press");
            }

#endif
        }

        break;
    }

    case BUTTON_UP: // Release state
    {
        if (btn->Button_Trigger_Event == BUTTON_DOWM) // Trigger single click
        {
            if ((btn->Timer_Count <= BUTTON_DOUBLE_TIME) && (btn->Button_Last_State == BUTTON_DOUBLE)) // Double click
            {
                btn->Button_Trigger_Event = BUTTON_DOUBLE;
                TRIGGER_CB(BUTTON_DOUBLE);
                //   printf("Double click");
                btn->Button_State = NONE_TRIGGER;
                btn->Button_Last_State = NONE_TRIGGER;
            }
            else
            {
                btn->Timer_Count = 0;
                btn->Long_Time = 0; // Check long press failure, reset to 0

#if (SINGLE_AND_DOUBLE_TRIGGER == 0)
                TRIGGER_CB(BUTTON_DOWM); // Single click
#endif
                btn->Button_State = BUTTON_DOUBLE;
                btn->Button_Last_State = BUTTON_DOUBLE;
            }
        }
        else if (btn->Button_Trigger_Event == BUTTON_LONG)
        {
#if LONG_FREE_TRIGGER
            TRIGGER_CB(BUTTON_LONG); // Long press
#else
            TRIGGER_CB(BUTTON_LONG_FREE); // Long press release
#endif
            btn->Long_Time = 0;
            btn->Button_State = NONE_TRIGGER;
            btn->Button_Last_State = BUTTON_LONG;
        }

#if CONTINUOS_TRIGGER
        else if (btn->Button_Trigger_Event == BUTTON_CONTINUOS) // Continuous press
        {
            btn->Long_Time = 0;
            TRIGGER_CB(BUTTON_CONTINUOS_FREE); // Continuous press release
            btn->Button_State = NONE_TRIGGER;
            btn->Button_Last_State = BUTTON_CONTINUOS;
        }

#endif

        break;
    }

    case BUTTON_DOUBLE:
    {
        btn->Timer_Count++; // Time record
        if (btn->Timer_Count >= BUTTON_DOUBLE_TIME)
        {
            btn->Button_State = NONE_TRIGGER;
            btn->Button_Last_State = NONE_TRIGGER;
        }

#if SINGLE_AND_DOUBLE_TRIGGER

        if ((btn->Timer_Count >= BUTTON_DOUBLE_TIME) && (btn->Button_Last_State != BUTTON_DOWM))
        {
            btn->Timer_Count = 0;
            TRIGGER_CB(BUTTON_DOWM); // Single click
            btn->Button_State = NONE_TRIGGER;
            btn->Button_Last_State = BUTTON_DOWM;
        }

#endif

        break;
    }

    default:
        break;
    }
}

/************************************************************
  * @brief   Traverse and scan buttons without losing any button
	* @param   NULL
  * @return  NULL
  * @version v1.0
  * @note    This function must be called periodically, suggested every 20-50ms
  ***********************************************************/
void Button_Process(void)
{
    struct button *pass_btn;
    for (pass_btn = Head_Button; pass_btn != NULL; pass_btn = pass_btn->Next)
    {
        Button_Cycle_Process(pass_btn);
    }
}

/************************************************************
  * @brief   Traverse buttons
	* @param   NULL
  * @return  NULL
  * @version v1.0
  * @note    NULL
  ***********************************************************/
void Search_Button(void)
{
    struct button *pass_btn;
    for (pass_btn = Head_Button; pass_btn != NULL; pass_btn = pass_btn->Next)
    {
        //   printf("button node have %s", pass_btn->Name);
    }
}

/************************************************************
  * @brief   Process all button callback functions 
	* @param   NULL
  * @return  NULL
  * @version v1.0
  * @note    未使用，可自行添加
  ***********************************************************/
void Button_Process_CallBack(void *btn)
{
    uint8_t btn_event = Get_Button_Event(btn);

    switch (btn_event)
    {
    case BUTTON_DOWM:
    {
        //添加你的連續觸發釋放的處理邏輯
        break;
    }

    case BUTTON_UP:
    {
        //添加你的連續觸發釋放的處理邏輯
        break;
    }

    case BUTTON_DOUBLE:
    {
        //添加你的連續觸發釋放的處理邏輯
        break;
    }

    case BUTTON_LONG:
    {
        //添加你的連續觸發釋放的處理邏輯
        break;
    }

    case BUTTON_LONG_FREE:
    {
        //添加你的連續觸發釋放的處理邏輯
        break;
    }

    case BUTTON_CONTINUOS:
    {
        //添加你的連續觸發釋放的處理邏輯
        break;
    }

    case BUTTON_CONTINUOS_FREE:
    {
        //添加你的連續觸發釋放的處理邏輯
        break;
    }
    }
}

/**************************** 內部函數 ********************/

/************************************************************
  * @brief   複製指定長度的字符串
  * @param   NULL
  * @return  NULL
  * @version v1.0
  * @note    NULL
  ***********************************************************/
static char *StrnCopy(char *dst, const char *src, uint32_t n)
{
    if (n != 0)
    {
        char *d = dst;
        const char *s = src;
        do
        {
            if ((*d++ = *s++) == 0)
            {
                while (--n != 0)
                    *d++ = 0;
                break;
            }
        } while (--n != 0);
    }
    return (dst);
}


/************************************************************
  * @brief   使用單鏈表將按鈕連接起來
  * @param   NULL
  * @return  NULL
  * @version v1.0
  * @note    NULL
  ***********************************************************/
static void Add_Button(Button_t *btn)
{
    btn->Next = Head_Button;
    Head_Button = btn;
}


/************************************************************
  * @brief   刪除一個已經創建的按鍵
	* @param   NULL
  * @return  NULL
  * @version v1.0
  * @note    NULL
  ***********************************************************/
void Button_Delete(Button_t *btn)
{
    struct button** curr;
    for(curr = &Head_Button; *curr;)
    {
        struct button* entry = *curr;
        if (entry == btn)
        {
            *curr = entry->Next;
        }
        else
        {
            curr = &entry->Next;
        }
    }
}
