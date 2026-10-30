from setuptools import find_packages, setup

package_name = 'C_transform'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='edu29',
    maintainer_email='20176737+s1len7@users.noreply.github.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    extras_require={
        'test': [
            'pytest',
        ],
    },
    entry_points={
        'console_scripts': [
            'tf_static = C_transform.tf_static:main',
            'tf_dynamic = C_transform.tf_dynamic:main',
            'tf_listener = C_transform.tf_listener:main',
            'tf_listener_laser = C_transform.tf_listener_laser:main',
            'lidar_mapper = C_transform.lidar_mapper:main',
            'tf_listener_laser_template = C_transform.tf_listener_laser_template:main',
        ],
    },
)
