# Datalog
Datalog is a multi-sensor data collection system base on Qt development.
And the verson of Qt is Qt 5.9.9 MSVC2017 64bit. These sensors
are base on RS485 Modbus. We connect them to a 16-port RS485 hub / Repeater.
These sensors including the tilt sensors (HCA726S, from Shenzhen
Ruifen Technology Co., Ltd.)，the motion detector sensors (LVDT HQH8B-10A-M2-C8P,
from Shenzhen Haoquan Technology Co., Ltd.), and the Torque Sensors(ZNNT-2000NM,
from Bengbu Transducer Sensor Technology Co., Ltd.).

In this program, we mainly use three threads. The main thread is responsible
for the response and interaction of the UI interface. And we put
sending requests and receiving data in one thread. In addition, processing
and saving the received data in the third thread.

- The application program can support up to 16 sensors to read data.
  Through the add more button, you can add more Reader to read.

- The data read by each sensor can be saved to a single file, or all
  the data can be saved to a specific file.

- When reading for the first time, it will check the correctness of
  the data sent, and judge whether the sensor type and ID match.

- When reading, the received data fails, it will be saved with a value
  of 255, and the request will be sent again.

- The user can customize the reading interval. If the total time for
  sending and reading of all sensors is less than this interval, wait
  for a sufficient interval before sending and reading. Otherwise, the
  serial port will continue to send and read data at a high frequency
  without any pause. To operate the serial port too frequently can easily
  cause write timeout errors.

- The user can customize the path and the name of the saved file.

 If you need more information, please feel free to contact me by email:
 dongdashu.aa@gmail.com or dong_dashu@yeah.net


![Snipaste_2021-03-28_17-17-49](https://user-images.githubusercontent.com/57821839/112747721-b7477e80-8fe9-11eb-8afd-8b123992f600.png)
