# -STM32F4
2023年学嵌入式的课程项目，包含蓝牙控制和自动寻路<br><br>

systick.c主要实现时钟中断,在小车调速中起作用<br><br>

motor.c对应函数操作小车的前进，对应的pin脚为PC6,PC7,PC8,PC9<br>
PC6对应左轮发动机正极，PC7对应左轮发动机负极<br>
PC8对应右轮发动机正极，PC9对应右轮发动机负极<br><br>

usart.c实现蓝牙连接和接收数据<br>
track.c
