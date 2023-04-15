# -STM32F4
2023年学嵌入式的课程项目，包含蓝牙控制和自动寻路<br><br>
systick.c主要实现时钟中断,在小车调速中起作用<br><br>
motor.c对应函数操作小车的前进，对应的引脚为PC6,PC7,PC8,PC9<br>
PC6对应左轮发动机正极，PC7对应左轮发动机负极<br>
PC8对应右轮发动机正极，PC9对应右轮发动机负极<br><br>
usart.c实现蓝牙连接和接收数据<br>
track.c实现自动寻路功能<br>
初始化红外检测的引脚<br>
控制小车前进、左右转和停止<br><br>
main.c可以自由填写实现蓝牙控制的数字<br>
直接在app中的edit中填写recv_byte就行(注意先右上角连接蓝牙)<br>
