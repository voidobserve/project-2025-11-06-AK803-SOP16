SINGLE_LED_GPIO_INDEX 宏，表示LED所在的引脚序号，例如 SINGLE_LED_GPIO_INDEX == 0x08,说明LED脚在GPIO_BIT_8对应的引脚上

PRODUCT_SELECTION(在 "app_select.h" 中定义)
    选择产品类型，例如
    PRODUCT_SELECTION == RMT_LMP_PUBLIC_KEY_VALUE_04KEY，4个按键的遥控器
    PRODUCT_SELECTION == RMT_LMP_PUBLIC_KEY_VALUE_28KEY，28个按键的遥控器
    RMT_LMP_PUBLIC_KEY_VALUE_xxKEY 在 "rmt_lmp_def.h" 中定义,每个定义只需要与其他的 RMT_LMP_PUBLIC_KEY_VALUE_xxKEY 做好区分，避免一致

在 "rmt_lmp_cfg.h" 内定义按键个数所对应的 
    1. 硬件检测类型               HW_DETECT_TYPE 
        1.1 例如 RC_SCAN_30KEY_TYPE，表示30个按键对应的硬件检测类型，在 "app_common.h" 中定义，与其他的 RC_SCAN_xxKEY_TYPE 做好区分，避免一致
    2. 每组发送多少个相同的数据包  GROUP_INDEX_MAX
    3. 按键个数                  KEYS_FUNCTION_NUM
    4. LED所在引脚               SINGLE_LED_GPIO_INDEX
   
在 "rcscan.h" 内定义硬件检测类型对应的上拉输入脚和低电平输出脚

    需要注意在 803 型号的ic中， BIT10内部没有上拉电阻，不能配置为上拉输入脚
    不能选择GNDB(芯片的GND脚)作为上拉输入脚


- 如果要修改发送的数据包的长度，在`ble_viot_encoder()`中修改`out_data_len`的值


 


