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

- Env: Ubuntu 24.04 LTS
<!-- - ID: edu14, PW:1234 -->

<!-- sudo apt install ibus-hangul
ibus engine hangul -->


- installed vscode
  - setup **python, cmake tools, jupyter** extension

- in Terminal,
  - Copy: Ctrl + **shift** + C
  - paste: Ctrl + **shift** + V

- To update the lecturer's repository(submodule):

```bash
  git submodule update --init --remote --recursive DeepTech-Robot-Navigation/
```



- To **create** custom package, in `colcon_ws/**src**`,
```bash
ros2 pkg create <pkg_name> --build-type ament_python --dependencies rclpy std_msgs geometry_msgs sensor_msgs nav_msgs
```
ros2 pkg create tutorial_robot_control --build-type ament_python --dependencies rclpy std_msgs geometry_msgs sensor_msgs nav_msgs


- To **build** custom python package, in `colcon_ws/`,
```bash
colcon build
source install/setup.bash
```

- To **run** package, in `colcon_ws/`,
```bash
# ros2 run <package_name> <executable_name:defined in colcon_ws/src/A_pubsub/setup.py>
# execute in each terminal

# ros2 run A_pubsub talker
# ros2 run A_pubsub listener

ros2 run A_pubsub publisher
ros2 run A_pubsub processor
ros2 run A_pubsub subscriber
```

- To visualize modules relationship:
```bash
rqt_graph
```


