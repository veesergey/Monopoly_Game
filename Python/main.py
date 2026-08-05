from functions import pause_console
from game import Game


def main():
    monopoly = Game()

    monopoly.player_turns()

    monopoly.victory()

    pause_console()


if __name__ == "__main__":
    main()
