# 경기 스타트업 아카데미 · 딥테크 과정 - 로봇연계 · 자율주행

> ROS2로 로봇 하드웨어를 제어하고, SLAM·Navigation2로 자율주행을 완성하는 5일 과정

📢 [경기스타트업플랫폼 - 사업 공고 바로가기](https://www.gsp.or.kr/supportProject/UVSD0001.do?sportSeq=6404)

<details>
<summary>🖼️ 딥테크 교육 메인 포스터 보기</summary>

![딥테크 교육 메인 포스터](https://www.gsp.or.kr:8443/common/dext5upload/handler/dext5handler.jsp?dext5CMD=openRequest&fileNameRuleEx=_&fileOrgName=%EB%94%A5%ED%85%8C%ED%81%AC%20%EA%B5%90%EC%9C%A1%20%EB%A9%94%EC%9D%B8%20%ED%8F%AC%EC%8A%A4%ED%84%B0.png&fileVirtualPath=/data/prod/upload//2026/10/3F9F1011-2B2B-4217-37BB-34E2E22FF436.png)

</details>

<details>
<summary>🖼️ 교육 상세 커리큘럼 보기</summary>

![교육 상세페이지 1](https://www.gsp.or.kr:8443/common/dext5upload/handler/dext5handler.jsp?dext5CMD=openRequest&fileNameRuleEx=_&fileOrgName=%EA%B5%90%EC%9C%A1%20%EC%83%81%EC%84%B8%ED%8E%98%EC%9D%B4%EC%A7%801.png&fileVirtualPath=/data/prod/upload//2026/10/F2B96DDE-F6AD-9BB0-ECC2-2F482AE7E4F1.png)

</details>

## 📚 과정 구성

| 구분 | 과정명 | 일정 | 시간 | 총 시수 |
| :--: | --- | --- | :--: | :--: |
| 2-1 | **ROS2 하드웨어 인터페이스 및 모터 제어 실무** | 2026. 10. 26.(월) ~ 10. 27.(화) | 10:00 ~ 17:00 | 2일 · 12시간 |
| 2-2 | **ROS2 기반 SLAM 및 자율주행(Navigation2) 실전** | 2026. 10. 28.(수) ~ 10. 30.(금) | 10:00 ~ 17:00 | 3일 · 18시간 |

- **강사**: 김규래 ([github.com/kyu-rae-kim](https://github.com/kyu-rae-kim), [kkr.kyurae.kim@gmail.com](mailto:kkr.kyurae.kim@gmail.com))
<!-- kkr0913 -->
- **교육 장소**: 경기스타트업벨리(E동) 4층 도약실 (경기도 성남시 수정구 금토로 52)


## 🗓️ 일자별 커리큘럼

| 일자 | 과정 | 주제 |
| :--: | :--: | --- |
| 10. 26.(월) | 2-1 | 마이크로컨트롤러 환경설정 및 통신 연결 |
| 10. 27.(화) | 2-1 | 모터 드라이버 제어 및 기구부 주행 |
| 10. 28.(수) | 2-2 | 센서 데이터 융합 및 실시간 SLAM |
| 10. 29.(목) | 2-2 | Navigation2 스택 아키텍처 및 경로 계획 |
| 10. 30.(금) | 2-2 | 위치 추정 최적화 및 통합 자율주행 |

## Memo

<!-- i will memo anything about the lecture. you will trim, rewrite and post above in korean. -->

- Reference
  - https://docs.ros.org/en/jazzy/


- Env: Ubuntu 24.04 LTS
<!-- - ID: edu14, PW:1234 -->

<!-- 
sudo apt install ibus-hangul
ibus engine hangul 
-->


- installed vscode
  - setup **python, cmake tools, jupyter** extension


- in Terminal,
  - Copy: Ctrl + **shift** + C
  - paste: Ctrl + **shift** + V


- To update the lecturer's repository(submodule):

```bash
git submodule update --init --remote --recursive DeepTech-Robot-Navigation/
```


- To run `turtlesim`,
```bash
# execute in each terminal
ros2 run turtlesim turtlesim_node
ros2 run turtlesim turtle_teleop_key
```



- To **create** custom package, in `colcon_ws/**src**`,
```bash
ros2 pkg create <pkg_name> --build-type ament_python --dependencies rclpy std_msgs geometry_msgs sensor_msgs nav_msgs
```

  - for example,
```bash
.../colcon_ws/src$ ros2 pkg create tutorial_robot_control --build-type ament_python --dependencies rclpy std_msgs geometry_msgs sensor_msgs nav_msgs
```


- To **build** custom python package, in `colcon_ws/`,
```bash
colcon build
source install/setup.bash
```

- To **run** package, in `colcon_ws/`,
```bash
# execute in each terminal
ros2 run <pkg_name> <executable_name:defined in colcon_ws/src/<pkg_name>/setup.py>
```

  - for example,
```bash
# execute in each terminal
ros2 run A_pubsub talker
ros2 run A_pubsub listener
```

- To visualize modules relationship,
```bash
rqt_graph
```


- launch file: `.../colcon_ws/src/<pkg_name>/launch/<pkg_name>.launch.py`
  - for example, [src/A_pubsub/launch/A_pubsub.launch.py](robot_navigation/colcon_ws/src/A_pubsub/launch/A_pubsub.launch.py)

- also, to use `launch.py`, it is required to modify **`setup.py`** 
  - for example, [src/A_pubsub/setup.py](robot_navigation/colcon_ws/src/A_pubsub/setup.py)
```python
      ...
    data_files=[
      ...
        # To use <pkg_name>.launch.py
        ('share/' + package_name + '/launch',
            ['launch/A_pubsub.launch.py']),
      ...
```



- then re-build the package and **launch**,

```bash
colcon build
source install/setup.bash
ros launch <pkg_name> <pkg_name>.launch.py
```

for example,

```bash
.../colcon_ws$ ros launch A_pubsub A_pubsub.launch.py
```


BTW, We also need to know how to use our ESP32 board.

- ESP32R Pin Map: https://makerselectronics.com/product/wemos-d1-r32-esp32-wifi-bluetooth-uno-r3-pinout/?srsltid=AYCX9vKp3jPbDMPrFh7Z9ri447VV0HaBWqJo06a4ydxUy9PhmqqONIwJ


- Arduino UNO R3
  - in [TinkerCAD](https://www.tinkercad.com/), we can simulate our custom circuit.


- To install Arduino IDE,

```bash
sudo apt update
sudo apt install -y curl libfuse2t64

sudo mkdir -p /opt/arduino-ide
cd /opt/arduino-ide

sudo curl -fL \
    https://github.com/arduino/arduino-ide/releases/latest/download/arduino-ide_2.3.10_Linux_64bit.AppImage \
    -o arduino-ide.AppImage

cd /opt/arduino-ide
sudo chmod +x arduino-ide.AppImage
./arduino-ide.AppImage --no-sandbox

# To create shortcut,
echo '#!/bin/sh
exec /opt/arduino-ide/arduino-ide.AppImage --no-sandbox "$@"' > ./robot_navigation/scripts/arduino-ide
chmod +x ./robot_navigation/scripts/arduino-ide

# and create symbolic link
sudo ln -s $HOME/2026_GBSA_ROBOT_AUTONOMOUS_DRIVING/robot_navigation/scripts/arduino-ide /usr/local/bin/arduino-ide
```

- To use our development board, In Arduino IDE, 
  - install **BOARD MANAGER > esp32** by Espressif Systems
  - and Select **WEMOS D1 R32**

- To use the servo motor, 
  - install **LIBRARY MANAGER > ESP32Servo**

<!-- - Processing: https://processing.org -->


- To install EIM
  - Custom Installation > esp32 > [x] show old stable version > v5.5.5 > ...(proceeed with default setting)

- To setup virtual environment,

```bash
mkdir -p ~/2026_GBSA_ROBOT_AUTONOMOUS_DRIVING/robot_navigation/scripts && \
_ACTIVATE_IDF_SH_PATH="$(find ~/.espressif -type f -name 'activate_idf_v5.5.5.sh' -print -quit 2>/dev/null)" && \
[ -n "$_ACTIVATE_IDF_SH_PATH" ] && \
cat > ~/2026_GBSA_ROBOT_AUTONOMOUS_DRIVING/robot_navigation/scripts/idfsh <<EOF
#!/usr/bin/env bash
env -i \\
HOME="\$HOME" \\
USER="\$USER" \\
TERM="\$TERM" \\
DISPLAY="\${DISPLAY:-}" \\
XAUTHORITY="\${XAUTHORITY:-}" \\
PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin" \\
bash --noprofile --norc -c '
    source "$_ACTIVATE_IDF_SH_PATH"
    export PATH="\$IDF_PATH/tools:\$PATH"
    export PATH="\$HOME/.local/bin:\$PATH"
    exec bash --noprofile --norc
'
EOF
chmod +x ~/2026_GBSA_ROBOT_AUTONOMOUS_DRIVING/robot_navigation/scripts/idfsh && \
bash -n ~/2026_GBSA_ROBOT_AUTONOMOUS_DRIVING/robot_navigation/scripts/idfsh && \
echo "완료: ~/2026_GBSA_ROBOT_AUTONOMOUS_DRIVING/robot_navigation/scripts/idfsh"

echo "스크립트 실행 권한 부여:"
chmod +x ~/2026_GBSA_ROBOT_AUTONOMOUS_DRIVING/robot_navigation/scripts/idfsh

echo "실행 명령어 등록:"
sudo ln -sf /usr/bin/as /usr/local/bin/as
sudo ln -sf /usr/bin/ld /usr/local/bin/ld
sudo ln -s ~/2026_GBSA_ROBOT_AUTONOMOUS_DRIVING/robot_navigation/scripts/idfsh /usr/local/bin/idfsh

source ~/.bashrc
```

- To **build** example,

```bash
echo "ESP-IDF 기본 예제 복사:"
cp -a "$IDF_PATH/examples/get-started/hello_world/." ~/2026_GBSA_ROBOT_AUTONOMOUS_DRIVING/robot_navigation/firmware/esp32/


echo "To move to the example directory,"
cd ~/2026_GBSA_ROBOT_AUTONOMOUS_DRIVING/robot_navigation/firmware/esp32

echo "컴파일 대상 칩을 ESP32로 지정 및 빌드:"
idf.py set-target esp32
idf.py build

echo "ESP32에 펌웨어 Flash:"
idf.py -p /dev/ttyUSB0 flash
echo '실패하면 "BOOT 버튼 누른 상태로 flash하고, Connecting... 나오면 놓기"'

echo "Serial Monitor:"
idf.py -p /dev/ttyUSB0 monitor
```

```bash
echo "flash와 monitor 동시에 하려면"
idf.py -p /dev/ttyUSB0 flash monitor
```

- To terminate it,
  - press `Ctrl + ]`

- To install micro-ROS dependency,
  - in the virtual environment,

```bash
python -m pip install catkin_pkg colcon-common-extensions lark
```

- To backup,
```bash
#cd ~/2026_GBSA_ROBOT_AUTONOMOUS_DRIVING/robot_navigation/firmware/esp32/ && \
echo "25. 기존 파일 백업"
mv main/hello_world_main.c main/hello_world_main.c.backup
cp main/CMakeLists.txt main/CMakeLists.txt.backup

echo "체크:"
ls main

echo "expected result: >> CMakeLists.txt  CMakeLists.txt.backup  hello_world_main.c.backup"
```

- To make micro-ROS dependency file,

```bash
#cd ~/2026_GBSA_ROBOT_AUTONOMOUS_DRIVING/robot_navigation/firmware/esp32/ && \
mkdir -p main && \
echo 'dependencies:
  micro-ros/micro_ros_espidf_component:
    version: "^24.0.0"' > main/idf_component.yml && \
echo '{
    "names": {
        "rmw_microxrcedds": {
            "cmake-args": [
                "-DRMW_UXRCE_TRANSPORT=custom"
            ]
        }
    }
}' > app-colcon.meta
```

- and modify `firmware/esp32/main/CMakeLists.txt`
```
idf_component_register(SRCS "main.cpp" # hello_world_maim.c -> main.cpp
                       PRIV_REQUIRES spi_flash
                       INCLUDE_DIRS "")
```


- and reconfigure ESP-IDF
```bash
idf.py reconfigure
```

- in `robot_navigation/firmware/esp32`,
```bash
idf.py menuconfig
```

- check and modify setting
  - "micro-ROS Settings" -> 
    - "micro-ROS middleware" -> "micro-ROS over eProsima Micro XRCE-DDS"
    - "micro-ROS network interface select" -> "Micro XRCE-DDS over UART"
    - "UART Settings" -> 전부 "-1"인지 확인
- "S" 눌러 저장 -> "Esc" 눌러 종료

- expected verify result
```bash
(venv) grep MICRO_ROS_ESP_XRCE_DDS_MIDDLEWARE sdkconfig
>> CONFIG_MICRO_ROS_ESP_XRCE_DDS_MIDDLEWARE=y

(venv) grep MICRO_ROS_ESP_UART_TRANSPORT sdkconfig
>> CONFIG_MICRO_ROS_ESP_UART_TRANSPORT=y

(venv) grep MICROROS_UART sdkconfig
>> CONFIG_MICROROS_UART_TXD=-1
>> CONFIG_MICROROS_UART_RXD=-1
>> CONFIG_MICROROS_UART_RTS=-1
>> CONFIG_MICROROS_UART_CTS=-1
```

- To build UART transport를 사용하는 micro-ROS 펌웨어
  - in `2026_GBSA_ROBOT_AUTONOMOUS_DRIVING/robot_navigation/firmware/esp32`

```bash
idf.py build
```

- expected result
```
...
Successfully created esp32 image.
Generated /home/edu29/2026_GBSA_ROBOT_AUTONOMOUS_DRIVING/robot_navigation/firmware/esp32/build/hello_world.bin
[15/18] cd /home/edu29/2026_GBSA_ROBOT_AUTONOMOUS_DRIVING/robot_navigation/firmware/esp32/...9/2026_GBSA_ROBOT_AUTONOMOUS_DRIVING/robot_navigation/firmware/esp32/build/hello_world.bin
hello_world.bin binary size 0x3e150 bytes. Smallest app partition is 0x100000 bytes. 0xc1eb0 bytes (76%) free.

Project build complete. To flash, run:
 idf.py flash
or
 idf.py -p PORT flash
or
 python -m esptool --chip esp32 -b 460800 --before default_reset --after hard_reset write_flash --flash_mode dio --flash_size 2MB --flash_freq 40m 0x1000 build/bootloader/bootloader.bin 0x8000 build/partition_table/partition-table.bin 0x10000 build/hello_world.bin
or from the "/home/edu29/2026_GBSA_ROBOT_AUTONOMOUS_DRIVING/robot_navigation/firmware/esp32/build" directory
 python -m esptool --chip esp32 -b 460800 --before default_reset --after hard_reset write_flash "@flash_args"
(venv) 
```

```bash
sudo rosdep init
rosdep update

cd ~/2026_GBSA_ROBOT_AUTONOMOUS_DRIVING/robot_navigation/colcon_ws
git clone -b jazzy --depth 1 \
https://github.com/micro-ROS/micro_ros_setup.git \
src/micro_ros_setup

rosdep install \
    --from-paths src \
    --ignore-src \
    -y

cd ~/2026_GBSA_ROBOT_AUTONOMOUS_DRIVING/robot_navigation/colcon_ws
colcon build --symlink-install --packages-select micro_ros_setup
source install/setup.bash

ros2 run micro_ros_setup create_agent_ws.sh
ros2 run micro_ros_setup build_agent.sh
source install/setup.bash
```

- To start the agent,
```bash
ros2 run micro_ros_agent micro_ros_agent \
    serial \
    --dev /dev/ttyUSB0 \
    -b 115200 \
    -v6
```

- in firmware/esp32

```bash
cd ~/2026_GBSA_ROBOT_AUTONOMOUS_DRIVING/robot_navigation/firmware/esp32/

cp main/main.cpp main/main.cpp.uart.backup
cp main/CMakeLists.txt main/CMakeLists.txt.uart.backup
mv app-colcon.meta app-colcon.meta.backup
```


