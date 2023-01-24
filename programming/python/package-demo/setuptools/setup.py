from setuptools import find_namespace_packages, setup

setup(
    name="package_demo",
    version="1.0.0",
    install_requires=[
        "requests"
    ],
    packages=find_namespace_packages(),
    entry_points={
        "console_scripts": [
            "demo = package_demo.main:main"
        ]
    }
)
