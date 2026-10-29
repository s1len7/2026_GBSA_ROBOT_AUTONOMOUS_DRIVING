from setuptools import find_packages, setup

package_name = 'A_talk_listener'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),

        # To use <pkg_name>.launch.py
        ('share/' + package_name + '/launch',
            ['launch/A_talk_listener.launch.py']),

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
            # identifier = package_name.module_name:function_name
            "talker = A_talk_listener.talker:main",
            "listener = A_talk_listener.listener:main",
        ],
    },
)
