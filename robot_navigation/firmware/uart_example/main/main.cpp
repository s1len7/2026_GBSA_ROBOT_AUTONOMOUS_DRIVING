#include <unistd.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/uart.h"

#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <std_msgs/msg/int32.h>

#include <rmw_microxrcedds_c/config.h>
#include <rmw_microros/rmw_microros.h>

#include "esp32_serial_transport.h"


namespace
{

rcl_publisher_t publisher;
std_msgs__msg__Int32 message;


/**
 * @brief rcl/rclc 함수의 반환값을 검사하는 치명적 오류 처리 매크로.
 *
 * 전달된 함수 fn을 실행하고 반환값이 RCL_RET_OK가 아니면
 * 현재 실행 중인 FreeRTOS task를 종료한다.
 *
 * 주로 node, timer, executor 등의 초기화처럼
 * 실패했을 때 이후 실행을 계속하기 어려운 함수에 사용한다.
 *
 * @param fn rcl_ret_t 타입의 반환값을 가지는 rcl/rclc 함수 호출식
 */
#define RCCHECK(fn)                           \
    do {                                      \
        rcl_ret_t rc = (fn);                  \
        if (rc != RCL_RET_OK) {               \
            vTaskDelete(nullptr);             \
        }                                     \
    } while (0)


/**
 * @brief rcl/rclc 함수의 반환값을 무시하는 비치명적 오류 처리 매크로.
 *
 * 전달된 함수 fn을 실행하고 반환값을 rc에 저장하지만,
 * 함수 실행이 실패하더라도 현재 task를 종료하지 않고 계속 실행한다.
 *
 * 주로 일시적으로 실패할 수 있지만 프로그램 전체를 종료할 필요는 없는
 * publish 등의 함수에 사용한다.
 *
 * @param fn rcl_ret_t 타입의 반환값을 가지는 rcl/rclc 함수 호출식
 */
#define RCSOFTCHECK(fn)                       \
    do {                                      \
        rcl_ret_t rc = (fn);                  \
        (void)rc;                             \
    } while (0)


/**
 * @brief ROS timer 만료 시 호출되는 callback 함수.
 *
 * executor가 timer의 주기가 만료된 것을 감지하면 이 함수를 호출한다.
 * 현재 message를 publisher를 통해 publish한 뒤 message.data를 1 증가시킨다.
 *
 * publish에 실패하더라도 RCSOFTCHECK를 사용하므로
 * 현재 FreeRTOS task를 종료하지 않고 계속 실행한다.
 *
 * @param timer          callback을 발생시킨 ROS timer 객체의 포인터
 * @param last_call_time 이전 callback 호출과 관련된 시간 정보(ns).
 */
void timer_callback(
    rcl_timer_t *timer,
    int64_t last_call_time)
{
    (void)last_call_time;

    if (timer == nullptr) {
        return;
    }

    RCSOFTCHECK(
        rcl_publish(
            &publisher,   // message를 전송할 publisher
            &message,     // 전송할 ROS message
            nullptr)      // 별도의 RMW publisher allocation 정보 사용하지 않음
        );

    ++message.data;
}


/**
 * @brief micro-ROS node를 초기화하고 주기적으로 executor를 실행하는 FreeRTOS task.
 * 
 * 초기화가 끝난 뒤 무한 루프에서 executor를 반복 실행하여
 * timer callback 등의 ROS callback이 처리되도록 한다.
 *
 * @param argument FreeRTOS task 생성 시 전달되는 사용자 인자.
 */
void micro_ros_task(void *argument)
{
    (void)argument;

    // ROS node/executor가 사용할 공통 실행 환경 객체
    rclc_support_t support;

    // ROS 2 rcl 계층에서 사용할 기본 memory allocator 획득
    rcl_allocator_t allocator =
        rcl_get_default_allocator();

    // ROS 초기화 옵션 객체를 안전한 zero-initialized 상태로 생성
    rcl_init_options_t init_options =
        rcl_get_zero_initialized_init_options();

    // init_options를 실제 사용 가능한 상태로 초기화
    RCCHECK(
        rcl_init_options_init(
            &init_options,
            allocator));

    // 이 micro-ROS node가 사용할 ROS Domain ID
    constexpr size_t ros_domain_id = 본인_도메인_숫자;

    // init_options에 Domain ID 설정 추가
    RCCHECK(
        rcl_init_options_set_domain_id(
            &init_options,
            ros_domain_id));

    // support 초기화 및 공통 실행 환경 준비
    RCCHECK(
        rclc_support_init_with_options(
            &support,       // 초기화할 rclc support 객체
            0,              // argc
            nullptr,        // argv
            &init_options,  // Domain ID, RMW, Agent 설정 등이 들어 있는 ROS 초기화 옵션
            &allocator));   // ROS 객체 초기화에 사용할 memory allocator

    // ROS node 객체
    rcl_node_t node;

    // ROS node 생성
    RCCHECK(
        rclc_node_init_default(
            &node,                  // 생성할 노드
            "my_esp32_publisher",   // 노드 이름
            "",                     // 노드 namespace
            &support));


    // std_msgs.msg.Int32 메세지 타입의 publisher 생성
    rclc_publisher_init_default(
        &publisher,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(
            std_msgs,
            msg,
            Int32),
        "esp32_int32");   // publish할 topic 이름


    // ROS timer 객체
    rcl_timer_t timer;

    // timer의 주기(1000ms)
    constexpr unsigned int timer_period_ms = 1000;

    // 1초 주기의 ROS timer 생성 및 timer 만료 시 timer_callback이 호출되도록 등록
    RCCHECK(
        rclc_timer_init_default(
            &timer,
            &support,
            RCL_MS_TO_NS(timer_period_ms),
            timer_callback));


    // callback을 실행할 executor 객체
    rclc_executor_t executor;

    // executor 초기화
    RCCHECK(
        rclc_executor_init(
            &executor,
            &support.context,  // executor가 사용할 ROS context
            1,                 // executor가 관리할 handle 개수: timer 1개
            &allocator));

    // 위에서 생성한 timer를 executor에 등록
    RCCHECK(
        rclc_executor_add_timer(
            &executor,
            &timer));

    // 처음 publish할 Int32 message 값
    message.data = 0;


    // 등록된 ROS entity(timer 등)의 상태를 확인하고 실행 가능한 callback이 있으면 처리
    while (true) {
        rclc_executor_spin_some(
            &executor,
            RCL_MS_TO_NS(100));  // timeout

        usleep(10000);
    }
}


// micro-ROS serial transport에서 사용할 ESP32 UART 포트 번호
size_t uart_port = UART_NUM_0;

} // namespace


extern "C" void app_main(void)
{
#if defined(RMW_UXRCE_TRANSPORT_CUSTOM)

    rmw_uros_set_custom_transport(
        true,
        static_cast<void *>(&uart_port),
        esp32_serial_open,
        esp32_serial_close,
        esp32_serial_write,
        esp32_serial_read);

#else

#error "micro-ROS custom transport is not enabled"

#endif

    // micro-ROS 로직을 FreeRTOS task로 등록
    xTaskCreate(
        micro_ros_task,                   // 실행할 함수
        "micro_ros_task",                 // task 이름
        CONFIG_MICRO_ROS_APP_STACK,       // 스택 크기 (기본: 16000 bytes)
        nullptr,                          // 함수에 넘길 인자
        CONFIG_MICRO_ROS_APP_TASK_PRIO,   // 우선순위 (기본: 5)
        nullptr);                         // task handle 저장 안 함
}