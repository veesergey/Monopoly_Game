import random

from functions import clear_screen, pause_console, read_int
from property import Property
from player import Player

# (name, cost, rent, is_special, in_unowned_list)
TILE_DATA = [
    ("Go", 0, 0, True, False),
    ("Farm", 60, 40, False, True),
    ("Quest", 0, 0, True, False),
    ("Cave", 60, 40, False, True),
    ("RockyR", 200, 0, False, True),
    ("Smithy", 100, 80, False, True),
    ("IncomeTax", 0, 0, True, False),
    ("Inn", 120, 80, False, True),
    ("Stocks", 0, 0, True, False),
    ("Torch", 150, 0, False, True),
    ("Cart", 200, 0, False, True),
    ("Hamlet", 180, 140, False, True),
    ("W.Pump", 150, 0, False, False),
    ("TwnSqr", 0, 0, True, False),
    ("Church", 260, 140, False, True),
    ("Scroll", 0, 0, True, False),
    ("Barn", 260, 160, False, True),
    ("SmoothR", 200, 0, False, True),
    ("Mill", 280, 160, False, True),
    ("LuxTax", 0, 0, True, True),
    ("Oasis", 280, 160, False, True),
    ("Sheriff", 0, 0, True, False),
    ("Tavern", 320, 200, False, True),
    ("Cart2", 200, 0, False, True),
    ("Granary", 350, 220, False, True),
    ("Mansion", 400, 250, False, True),
]

RAILROADS = {4: "RockyR", 10: "Cart", 17: "SmoothR", 23: "Cart2"}


class Game:
    def __init__(self):
        random.seed()

        self.sigil_list = ["@", "#", "$", "%", "&", "*", "!", "^", "~", "+"]

        self.board = [Property(name, cost, rent, special) for name, cost, rent, special, _ in TILE_DATA]
        self.unowned_property = [
            Property(name, cost, rent, special)
            for name, cost, rent, special, in_unowned in TILE_DATA
            if in_unowned
        ]

        self.player_list = []

        self.welcome()
        self.create_players()
        self.add_players_to_board()

    # ---- Setup ----------------------------------------------------------

    def welcome(self):
        print("\nWelcome to Monopoly!")

    def get_humans(self):
        while True:
            print("Enter the number of human players (1-6): ", end="")
            raw = input()
            try:
                num_humans = int(raw)
            except ValueError:
                continue
            if 1 <= num_humans <= 6:
                return num_humans

    def create_players(self):
        num_humans = self.get_humans()

        for x in range(num_humans):
            name = ""
            while len(name) < 1 or len(name) > 4:
                print(f"Enter name for player {x + 1} (Must be under 4 characters): ", end="")
                name = input().strip()

            valid_sigil = False
            while not valid_sigil:
                print("Available Sigils")
                print(" ".join(self.sigil_list))
                print(f"\nEnter sigil for {name} (Must be 1 character): ", end="")
                sigil = input().strip()
                if sigil not in self.sigil_list:
                    print("Not a valid sigil.")
                else:
                    self.sigil_list.remove(sigil)
                    valid_sigil = True

            self.player_list.append(Player(name, sigil, 1000))

    def add_players_to_board(self):
        for player in self.player_list:
            self.board[player.position].add_to_tile(player.sigil)

    # ---- Printing ---------------------------------------------------------

    def print_players(self, player_list):
        print("List of Players: ")
        for player in player_list:
            print(f"Name: {player.name}")
            print(f"Sigil: {player.sigil}")
            print(f"Money: {player.money}")

    def print_tile(self, prop):
        top_line = "---------------"
        print(top_line)
        print(f"|  {prop.name:>9}  |")
        print(top_line)
        print("|             |")
        print("| ", end="")
        print(f"{prop.get_on_tile_str():>10}", end="")
        print("  |")
        for _ in range(2):
            print("|             |")
        print(top_line, end="")

    def print_top_row(self, board, player):
        out = ["=" * 127, "\n|"]
        for x in range(9):
            out.append(f"{board[x].name:>7}{board[x].owner:>6}|")
        out.append(f"{'Current Player':>23}")
        out.append("\n" + "-" * 127)
        out.append(f"{'-------------':>22}\n")
        out.append("|")
        for x in range(9):
            out.append(f"{board[x].get_on_tile_str():>6}{'|':>8}")
        out.append(f"{'Name: ':>15}{player.name:>8}")
        out.append("\n|")
        for x in range(9):
            out.append(f"C:{board[x].cost:>3}{'|':>9}")
        out.append(f"{'Money:':>15}{player.money:>8}")
        out.append("\n|")
        for x in range(9):
            out.append(f"R:{board[x].rent:>3}{'|':>9}")
        out.append(f"{'Loc:  ':>15}{board[player.position].name:>8}")
        out.append("\n|")
        for x in range(9):
            out.append(f"U:{board[x].get_upgrade_str():>6}{'|':>6}")
        out.append(f"{'Sigil:':>15}{player.sigil:>8}")
        out.append("\n" + "-" * 127)
        print("".join(out), end="")

    def print_mid_row1(self, board, left, right, player):
        out = ["\n"]
        out.append(f"|{board[left].name:>10}{board[left].owner:>3}|")
        out.append(f"{'|':>98}{board[right].name:>10}{board[right].owner:>3}|")
        out.append("\n")
        out.append(f"|{board[left].get_on_tile_str():>6}{'|':>8}")
        out.append(f"{'|':>98}{board[right].get_on_tile_str():>6}{'|':>8}")
        out.append(f"{'Owned Properties':>15}")
        out.append("\n")
        out.append(f"|C:{board[left].cost:>3}{'|':>9}")
        out.append(f"{'|':>98}C:{board[right].cost:>3}{'|':>9}")
        for prop in player.owned_property:
            out.append(f"{prop.name}...")
        out.append("\n")
        out.append(f"|R:{board[left].rent:>3}{'|':>9}")
        out.append(f"{'|':>98}R:{board[right].rent:>3}{'|':>9}")
        out.append("\n")
        out.append(f"|U:{board[left].get_upgrade_str():>6}{'|':>6}")
        out.append(f"{'|':>98}U:{board[right].get_upgrade_str():>6}{'|':>6}")
        out.append("\n---------------" + f"{'---------------':>112}")
        print("".join(out), end="")

    def print_mid_row2(self, board, left, right, player):
        out = ["\n"]
        out.append(f"|{board[left].name:>10}{board[left].owner:>3}|")
        out.append(f"{'|':>98}{board[right].name:>10}{board[right].owner:>3}|")
        out.append("\n")
        out.append(f"|{board[left].get_on_tile_str():>6}{'|':>8}")
        out.append(f"{'|':>98}{board[right].get_on_tile_str():>6}{'|':>8}")
        out.append(f"{'Mortaged Properties':>15}")
        out.append("\n")
        out.append(f"|C:{board[left].cost:>3}{'|':>9}")
        out.append(f"{'|':>98}C:{board[right].cost:>3}{'|':>9}")
        for prop in player.mortgaged_property:
            out.append(f"{prop.name}...")
        out.append("\n")
        out.append(f"|R:{board[left].rent:>3}{'|':>9}")
        out.append(f"{'|':>98}R:{board[right].rent:>3}{'|':>9}")
        out.append("\n")
        out.append(f"|U:{board[left].get_upgrade_str():>6}{'|':>6}")
        out.append(f"{'|':>98}U:{board[right].get_upgrade_str():>6}{'|':>6}")
        out.append("\n---------------" + f"{'---------------':>112}")
        print("".join(out), end="")

    def print_mid_row(self, board, left, right, player):
        out = ["\n"]
        out.append(f"|{board[left].name:>10}{board[left].owner:>3}|")
        out.append(f"{'|':>98}{board[right].name:>10}{board[right].owner:>3}|")
        out.append("\n")
        out.append(f"|{board[left].get_on_tile_str():>6}{'|':>8}")
        out.append(f"{'|':>98}{board[right].get_on_tile_str():>6}{'|':>8}")
        out.append("\n")
        out.append(f"|C:{board[left].cost:>3}{'|':>9}")
        out.append(f"{'|':>98}C:{board[right].cost:>3}{'|':>9}")
        out.append("\n")
        out.append(f"|R:{board[left].rent:>3}{'|':>9}")
        out.append(f"{'|':>98}R:{board[right].rent:>3}{'|':>9}")
        out.append("\n")
        out.append(f"|U:{board[left].get_upgrade_str():>6}{'|':>6}")
        out.append(f"{'|':>98}U:{board[right].get_upgrade_str():>6}{'|':>6}")
        out.append("\n---------------" + f"{'---------------':>112}")
        print("".join(out), end="")

    def print_bot_row(self, board, player):
        out = ["\n", "-" * 127, "\n|"]
        for x in range(21, 12, -1):
            out.append(f"{board[x].name:>7}{board[x].owner:>6}|")
        out.append("\n" + "-" * 127 + "\n")
        out.append("|")
        for x in range(21, 12, -1):
            out.append(f"{board[x].get_on_tile_str():>6}{'|':>8}")
        out.append("\n|")
        for x in range(21, 12, -1):
            out.append(f"C:{board[x].cost:>3}{'|':>9}")
        out.append("\n|")
        for x in range(21, 12, -1):
            out.append(f"R:{board[x].rent:>3}{'|':>9}")
        out.append("\n|")
        for x in range(21, 12, -1):
            out.append(f"U:{board[x].get_upgrade_str():>6}{'|':>6}")
        out.append("\n" + "-" * 127)
        print("".join(out), end="")

    def print_board(self, board, player):
        self.print_top_row(board, player)
        self.print_mid_row1(board, 25, 9, player)
        self.print_mid_row2(board, 24, 10, player)
        self.print_mid_row(board, 23, 11, player)
        self.print_mid_row(board, 22, 12, player)
        self.print_bot_row(board, player)

    # ---- Movement ---------------------------------------------------------

    def dice_roll(self):
        return random.randint(1, 5)

    def move_player(self, player):
        old_pos = player.position
        dice1 = self.dice_roll()
        dice2 = self.dice_roll()
        total = dice1 + dice2
        new_pos = old_pos + total

        if new_pos > 25:
            new_pos = new_pos - 26
            player.add_money(200)

        print(f"Old Position: {old_pos}")
        print(f"Dice Roll1: {dice1}")
        print(f"Dice Roll2: {dice2}")
        print(f"total:{total}")
        print(f"New Pos:{new_pos}")

        player.position = new_pos

        self.board[old_pos].take_off_tile(player.sigil)
        self.board[new_pos].add_to_tile(player.sigil)

        print(f"{player.name} has moved {total} spaces.", end="")
        print(f"Position: {new_pos}")

    def move_player_manual(self, player, new_pos):
        old_pos = player.position
        player.position = new_pos

        self.board[old_pos].take_off_tile(player.sigil)
        self.board[new_pos].add_to_tile(player.sigil)

        print(f"{player.name} has moved from {self.board[old_pos].name} to {self.board[new_pos].name}")

    # ---- Tile effects -------------------------------------------------------

    def check_new_tile(self, board, player_list, cur_player):
        tile = board[cur_player.position]
        cur_pos = tile.name

        if cur_pos == "Sheriff":
            self.move_player_manual(cur_player, 8)
            print(f"{cur_player.name} pays $50 to leave the Stockade!")
            cur_player.sub_money(50)
        elif cur_pos == "Scroll":
            print("Supposed to do the scroll thing!")
        elif cur_pos == "Quest":
            print("Supposed to do the quest things.")
        elif tile.is_owned and tile.rent != 0 and not tile.mortgage_status:
            print(f"{tile.name} is owned by {tile.owner}. ", end="")
            person_to_pay = tile.owner
            print(f"{cur_player.name} must pay {person_to_pay}.", end="")
            pay_amount = tile.rent
            cur_player.sub_money(pay_amount)
            for player in player_list:
                if player.name == tile.owner:
                    print(f"\n{cur_player.name} paid {tile.owner}${tile.rent}")
                    player.add_money(pay_amount)
        elif cur_pos == "LuxTax":
            print(f"{cur_player.name} has landed on Luxury Tax! Must pay a flat rate of $100 to the bank!")
            cur_player.sub_money(100)
        elif cur_pos == "IncomeTax":
            total_assets = cur_player.money
            for prop in cur_player.owned_property:
                total_assets += prop.cost
                total_assets += prop.rent

            to_pay = total_assets // 10

            choice = 0
            while choice != 1 and choice != 2:
                print(
                    f"{cur_player.name} has landed on Income Tax. "
                    f"Must pay 200 cash or 10% of total Assets ({to_pay})."
                )
                print("1. Pay $200")
                print(f"2. Pay 10% ({to_pay}){total_assets}")
                choice = read_int()

                if choice == 1:
                    cur_player.sub_money(200)
                    print("Paid $200")
                elif choice == 2:
                    cur_player.sub_money(to_pay)
                    print(f"Paid 10% ({to_pay}).")
                else:
                    print("Invalid Option")

    def travel_rail_road(self, cur_player):
        cur_pos = self.board[cur_player.position].name
        if cur_pos not in ("Cart", "Cart2", "RockyR", "SmoothR"):
            return

        choice = 0
        while choice != 1 and choice != 2:
            choice = read_int("Would you like to pay $100 to go to a different railroad? 1 for yes 2 for no:")
            if choice == 1:
                to_go = 0
                while to_go not in (1, 2, 3, 4):
                    to_go = read_int(
                        "What RR do you want to go to? \nRockyR = 1\nCart = 2\nSmoothR = 3\nCart2 = 4 \nChoice:"
                    )
                    if to_go == 1:
                        self.move_player_manual(cur_player, 4)
                    elif to_go == 2:
                        self.move_player_manual(cur_player, 10)
                    elif to_go == 3:
                        self.move_player_manual(cur_player, 17)
                    elif to_go == 4:
                        self.move_player_manual(cur_player, 23)
                    else:
                        print("Not a valid choice.")

    # ---- Turn loop ----------------------------------------------------------

    def check_players(self, player_list):
        for player in list(player_list):
            if player.money < 0 and len(player.owned_property) == 0:
                player_list.remove(player)
                print(f"{player.name} does not have any money or properties. They have lost.")
            elif player.money < 0 and len(player.owned_property) > 0:
                print("You are bankrupt! Mortage whatever property you need to get your balance above zero.")
                while player.money < 0 and len(player.owned_property) > 0:
                    for prop in player.owned_property:
                        if not prop.mortgage_status:
                            print(f"{prop.name}:{prop.cost}", end="")
                    print("\nType in a property to mortage:", end="")
                    prop_to_mortgage = input()
                    for prop in list(player.owned_property):
                        if prop_to_mortgage == prop.name:
                            player.mortgage_property(prop)
                            self.board[player.position].mortgage_status = True
                            player.mortgaged_property.append(prop)
                            player.owned_property.remove(prop)

    def player_turns(self):
        while len(self.player_list) > 1:
            for player in list(self.player_list):
                if player not in self.player_list:
                    continue

                print("-------------------------------")
                choice = 0
                can_end_turn = False
                can_move = True
                self.check_players(self.player_list)

                if player not in self.player_list:
                    continue

                while not (choice == 5 and can_end_turn):
                    pause_console()
                    clear_screen()
                    self.print_board(self.board, player)
                    print()

                    if player.position in (4, 10, 17, 23):
                        print("0. Travel RailRoad.")
                    print("1. Move.")
                    print(f"2. Buy property. ({self.board[player.position].name})")
                    print("3. Sell property.")
                    print("4. Buy hotel. ($200)")
                    print("5. End Turn.")
                    print("6. See all players, money, sigils, and their properties")
                    print("7. Cheat Menu. ")
                    print("8. Unmortage a property")
                    print("9. Trade Properties")
                    print("----------------------------")
                    choice = read_int(f"{player.name}, What would you like to do?:")

                    if choice == 0:  # travel railroad
                        if can_move:
                            clear_screen()
                            self.print_board(self.board, player)
                            self.travel_rail_road(player)
                            can_end_turn = True
                            can_move = False
                        else:
                            clear_screen()
                            self.print_board(self.board, player)
                            print()
                            print("\nYou already moved once this turn!")

                    elif choice == 1:  # move
                        if can_move:
                            clear_screen()
                            self.print_board(self.board, player)
                            self.move_player(player)
                            self.check_new_tile(self.board, self.player_list, player)
                            can_end_turn = True
                            can_move = False
                        else:
                            clear_screen()
                            self.print_board(self.board, player)
                            print()
                            print("\nYou already moved once this turn!")

                    elif choice == 2:  # buy property
                        clear_screen()
                        self.print_board(self.board, player)
                        print()
                        player.buy_prop(self.unowned_property, self.board)

                    elif choice == 3:  # sell property
                        clear_screen()
                        self.print_board(self.board, player)
                        print()
                        player.sell_property(self.unowned_property, self.board)

                    elif choice == 4:  # upgrade prop
                        clear_screen()
                        self.print_board(self.board, player)
                        print()
                        player.buy_hotel(self.board)

                    elif choice == 5:  # end turn
                        clear_screen()
                        self.print_board(self.board, player)
                        print()
                        if can_end_turn:
                            print("Ending Turn.")
                        else:
                            clear_screen()
                            self.print_board(self.board, player)
                            print()
                            choice = 0
                            print(f"{player.name} has not moved yet! Must move to end turn.")

                    elif choice == 7:  # cheat menu
                        clear_screen()
                        self.print_board(self.board, player)
                        print()
                        print("Cheat Menu")
                        print("1. Set Money")
                        print("2. Set Position")
                        choice2 = read_int("What would you like to do?: ")

                        if choice2 == 1:
                            new_money = read_int("Whats the new money amount?: ")
                            player.money = new_money
                        elif choice2 == 2:
                            for i in range(0, 5):
                                print(f"{self.board[i].name}...{i}   ", end="")
                            print()
                            for i in range(5, 10):
                                print(f"{self.board[i].name}...{i}   ", end="")
                            print()
                            for i in range(10, 15):
                                print(f"{self.board[i].name}...{i}   ", end="")
                            print()
                            for i in range(15, 20):
                                print(f"{self.board[i].name}...{i}   ", end="")
                            print()
                            for i in range(20, 25):
                                print(f"{self.board[i].name}...{i}   ", end="")
                            print()
                            new_pos = read_int("Enter new position: ")
                            self.move_player_manual(player, new_pos)
                            self.check_new_tile(self.board, self.player_list, player)
                        else:
                            print("Not a valid choice.")

                    elif choice == 6:  # print all players and money
                        for p in self.player_list:
                            print(f"\nName:{p.name}")
                            print(f"Sigil:{p.sigil}")
                            print(f"Money: {p.money}")
                            print("Properties:", end="")
                            for prop in p.owned_property:
                                print(f"{prop.name}...", end="")
                            print("\n-------------------------------------")

                    elif choice == 8:  # unmortgage
                        if len(player.mortgaged_property) == 0:
                            print("You have no mortaged properties.")
                        else:
                            for prop in player.mortgaged_property:
                                print(f"{prop.name}:${prop.cost}")
                            print("Which property do you want to unmortage?:", end="")
                            to_unmortgage = input()
                            for prop in list(player.mortgaged_property):
                                if to_unmortgage == prop.name and player.money >= prop.cost:
                                    player.unmortgage_prop(prop)
                                    self.board[player.position].mortgage_status = False
                                    player.owned_property.append(prop)
                                    player.mortgaged_property.remove(prop)

                    # choice 9 (Trade Properties) is not implemented

    def victory(self):
        print(f"Congratulations! {self.player_list[0].name} has won!")
