from launch import LaunchDescription
from launch.actions import ExecuteProcess, RegisterEventHandler
from launch.event_handlers import OnProcessStart

workspace_path = '~/2026_GBSA_ROBOT_AUTONOMOUS_DRIVING'
pkg_name = 'A_talk_listener'

def generate_launch_description():

    talker = ExecuteProcess(
        cmd=[
            'gnome-terminal', '--', 'bash', '-c',
            f'source {workspace_path}/robot_navigation/colcon_ws/install/setup.bash; '
            f'ros2 run {pkg_name} talker; '
            'exec bash'
        ],
        output='screen'
    )

    listener = ExecuteProcess(
        cmd=[
            'gnome-terminal', '--', 'bash', '-c',
            f'source {workspace_path}/robot_navigation/colcon_ws/install/setup.bash; '
            f'ros2 run {pkg_name} listener; '
            'exec bash'
        ],
        output='screen'
    )


    return LaunchDescription([
        talker,
        listener,
    ])