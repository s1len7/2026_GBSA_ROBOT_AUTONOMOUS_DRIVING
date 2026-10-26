import json

import rclpy
from rclpy.node import Node
from std_msgs.msg import String


class RobotProcessor(Node):
    def __init__(self):
        super().__init__("robot_processor")

        self.x = 0
        self.y = 0

        self.key_subscription = self.create_subscription(
            String,
            "/robot/key",
            self.key_callback,
            10,
        )

        self.position_publisher = self.create_publisher(
            String,
            "/robot/position",
            10,
        )

        self.publish_position()

    def key_callback(self, message):
        key = message.data.lower()

        if key == "w":
            self.y += 1
        elif key == "s":
            self.y -= 1
        elif key == "a":
            self.x -= 1
        elif key == "d":
            self.x += 1
        else:
            return

        self.publish_position()

    def publish_position(self):
        message = String()
        message.data = json.dumps(
            {"x": self.x, "y": self.y}
        )
        self.position_publisher.publish(message)

        self.get_logger().info(
            f"Robot position: ({self.x}, {self.y})"
        )


def main(args=None):
    rclpy.init(args=args)
    node = RobotProcessor()

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()