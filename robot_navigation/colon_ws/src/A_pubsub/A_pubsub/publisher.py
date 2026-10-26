import sys
import termios
import tty

import rclpy
from rclpy.node import Node
from std_msgs.msg import String


class KeyboardPublisher(Node):
    def __init__(self):
        super().__init__("keyboard_publisher")
        self.publisher = self.create_publisher(String, "/robot/key", 10)

    def publish_key(self, key):
        message = String()
        message.data = key
        self.publisher.publish(message)
        self.get_logger().info(f"Published key: {key}")


def main(args=None):
    rclpy.init(args=args)
    node = KeyboardPublisher()
    stdin_fd = sys.stdin.fileno()
    original_settings = termios.tcgetattr(stdin_fd)

    try:
        tty.setcbreak(stdin_fd)
        print("Control the robot with W/A/S/D. Press Q to quit.")

        while rclpy.ok():
            key = sys.stdin.read(1).lower()

            if key == "q":
                break

            if key in ("w", "a", "s", "d"):
                node.publish_key(key)

    except KeyboardInterrupt:
        pass
    finally:
        termios.tcsetattr(
            stdin_fd,
            termios.TCSADRAIN,
            original_settings,
        )
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()