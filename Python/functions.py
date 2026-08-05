import os
import sys


def clear_screen():
    os.system("cls" if os.name == "nt" else "clear")


def pause_console():
    print("Press any key to continue . . .", end="", flush=True)
    try:
        if os.name == "nt":
            import msvcrt
            msvcrt.getch()
        else:
            import termios
            import tty
            fd = sys.stdin.fileno()
            old_settings = termios.tcgetattr(fd)
            try:
                tty.setraw(fd)
                sys.stdin.read(1)
            finally:
                termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
    except Exception:
        input()
    print()


def read_int(prompt=None):
    if prompt is not None:
        print(prompt, end="")
    try:
        return int(input())
    except ValueError:
        return 0
