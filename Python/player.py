NON_PURCHASABLE = {"Go", "Quest", "Scroll", "Stocks", "Quest2", "TwnSqr", "Scroll2", "Sheriff"}


class Player:
    def __init__(self, name, sigil, money):
        self.name = name
        self.sigil = sigil
        self.money = money
        self.position = 0
        self.owned_property = []
        self.mortgaged_property = []

    def add_money(self, amount):
        if amount > 0:
            self.money += amount
        else:
            print(f"{amount} is an invalid amount of money.")

    def sub_money(self, amount):
        if amount > 0:
            self.money -= amount
        else:
            print(f"{amount} is not a valid amount.")

    def buy_prop(self, unowned_property, board):
        pos = self.position
        prop_to_buy = board[pos].name

        for i, prop in enumerate(unowned_property):
            if prop_to_buy in NON_PURCHASABLE:
                print(f"Cannot purchase {prop_to_buy} as it is not a purchaseable property.")
                break
            elif board[pos].name == prop_to_buy and board[pos].is_owned:
                print(f"This property already has an owner ({prop.owner}).")
                print(f"{prop.name} was not purchased.")
                break
            elif prop.name == prop_to_buy and not prop.is_owned and self.money >= prop.cost:
                self.sub_money(prop.cost)
                self.owned_property.append(prop)
                unowned_property.pop(i)
                print(f"{self.name} has purchased {prop.name}")
                board[pos].owner = self.name
                board[pos].is_owned = True
                break
            elif prop.name == prop_to_buy and self.money < prop.cost:
                print(f"{self.name} has {self.money} but needs {prop.cost} to purchase {prop.name}")
                print(f"{prop.name} was not purchased.")
                break

    def buy_hotel(self, board):
        pos = self.position
        cur_rent = board[pos].rent

        for prop in self.owned_property:
            if board[pos].name == prop.name:
                board[pos].add_upgrade("H")
                board[pos].rent = cur_rent + 150
                prop.rent = cur_rent + 150
                print(f"Hotel bought for {prop.name}.")
                self.sub_money(250)  # Hotel Price

    def sell_property(self, unowned_property, board):
        to_sell = input("What property would you like to sell?: ")
        for prop in list(self.owned_property):
            if prop.name == to_sell:
                self.owned_property.remove(prop)
                self.add_money(prop.cost)
                unowned_property.append(prop)
                print(f"{self.name} has sold {prop.name}")
                board[self.position].owner = " "
                board[self.position].is_owned = False

    def mortgage_property(self, prop):
        prop.mortgage()
        self.add_money(prop.cost)

    def unmortgage_prop(self, prop):
        prop.unmortgage()
        self.sub_money(prop.cost)
