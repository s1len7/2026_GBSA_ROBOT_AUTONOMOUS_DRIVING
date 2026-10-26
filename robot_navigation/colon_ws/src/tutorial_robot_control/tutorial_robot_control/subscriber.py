import json

import rclpy
from rclpy.node import Node
from std_msgs.msg import String


class RobotSubscriber(Node):
    def __init__(self):
        super().__init__("robot_subscriber")

        self.x = 0
        self.y = 0

        self.position_subscription = self.create_subscription(
            String,
            "/robot/position",
            self.position_callback,
            10,
        )

        self.timer = self.create_timer(1.0, self.timer_callback)

    def position_callback(self, message):
        try:
            position = json.loads(message.data)
            self.x = int(position["x"])
            self.y = int(position["y"])
        except (
            json.JSONDecodeError,
            KeyError,
            TypeError,
            ValueError,
        ) as error:
            self.get_logger().warning(
                f"Invalid position message: {error}"
            )

    def timer_callback(self):
        self.get_logger().info(
            f"Robot current coordinate: ({self.x}, {self.y})"
        )


def main(args=None):
    rclpy.init(args=args)
    node = RobotSubscriber()

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()