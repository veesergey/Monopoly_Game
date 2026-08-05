class Property:
    def __init__(self, name="", cost=0, rent=0, is_owned=False):
        self.name = name
        self.cost = cost
        self.rent = rent
        self.is_owned = is_owned
        self.owner = " "
        self.on_tile = []
        self.upgrades = []
        self.mortgage_status = False

    def add_to_tile(self, sigil):
        self.on_tile.append(sigil)

    def take_off_tile(self, sigil):
        if sigil in self.on_tile:
            self.on_tile.remove(sigil)

    def get_on_tile_str(self):
        return "".join(self.on_tile)

    def add_upgrade(self, upgrade):
        self.upgrades.append(upgrade)

    def get_upgrade_str(self):
        return "".join(self.upgrades)

    def mortgage(self):
        self.mortgage_status = True

    def unmortgage(self):
        self.mortgage_status = False
