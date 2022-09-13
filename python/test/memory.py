import time

"""
Look at python's memory footprint while doing nothing.
If it is a linux operating system, you can use "cat /proc/pid/status" to view the process information, "VmRSS" and "VmHWM" are the memory usage information of the process.
"""


def main() -> None:
    while True:
        time.sleep(1)


if __name__ == "__main__":
    main()
