#include "dynamic_load.hpp"

#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>

void print_random_name() {
    static std::vector<std::string> first_names{
        "Bumblebee",
        "Bandersnatch",
        "Broccoli",
        "Rinkydink",
        "Bombadil",
        "Boilerdang",
        "Bandicoot",
        "Fragglerock",
        "Muffintop",
        "Congleton",
        "Blubberdick",
        "Buffalo",
        "Benadryl",
        "Butterfree",
        "Burberry",
        "Whippersnatch",
        "Buttermilk",
        "Beezlebub",
        "Budapest",
        "Boilerdang",
        "Blubberwhale",
        "Bumberstump",
        "Bulbasaur",
        "Cogglesnatch",
        "Liverswort",
        "Bodybuild",
        "Johnnycash",
        "Bendydick",
        "Burgerking",
        "Bonaparte",
        "Bunsenburner",
        "Billiardball",
        "Bukkake",
        "Baseballmitt",
        "Blubberbutt",
        "Baseballbat",
        "Rumblesack",
        "Barister",
        "Danglerack",
        "Rinkydink",
        "Bombadil",
        "Honkytonk",
        "Billyray",
        "Bumbleshack",
        "Snorkeldink",
        "Anglerfish",
        "Beetlejuice",
        "Bedlington",
        "Bandicoot",
        "Boobytrap",
        "Blenderdick",
        "Bentobox",
        "Anallube",
        "Pallettown",
        "Wimbledon",
        "Buttercup",
        "Blasphemy",
        "Syphilis",
        "Snorkeldink",
        "Brandenburg",
        "Barbituate",
        "Snozzlebert",
        "Tiddleywomp",
        "Bouillabaisse",
        "Wellington",
        "Benetton",
        "Bendandsnap",
        "Timothy",
        "Brewery",
        "Bentobox",
        "Brandybuck",
        "Benjamin",
        "Buckminster",
        "Bourgeoisie",
        "Bakery",
        "Oscarbait",
        "Buckyball",
        "Bourgeoisie",
        "Burlington",
        "Buckingham",
        "Barnoldswick"
    };

    static std::vector<std::string> last_names{
        "Coddleswort",
        "Crumplesack",
        "Curdlesnoot",
        "Calldispatch",
        "Humperdinck",
        "Rivendell",
        "Cuttlefish",
        "Lingerie",
        "Vegemite",
        "Ampersand",
        "Cumberbund",
        "Candycrush",
        "Clombyclomp",
        "Cragglethatch",
        "Nottinghill",
        "Cabbagepatch",
        "Camouflage",
        "Creamsicle",
        "Curdlemilk",
        "Upperclass",
        "Frumblesnatch",
        "Crumplehorn",
        "Talisman",
        "Candlestick",
        "Chesterfield",
        "Bumbersplat",
        "Scratchnsniff",
        "Snugglesnatch",
        "Charizard",
        "Carrotstick",
        "Cumbercooch",
        "Crackerjack",
        "Crucifix",
        "Cuckatoo",
        "Cockletit",
        "Collywog",
        "Capncrunch",
        "Covergirl",
        "Cumbersnatch",
        "Countryside", "Coggleswort",
        "Splishnsplash",
        "Copperwire",
        "Animorph",
        "Curdledmilk",
        "Cheddarcheese",
        "Cottagecheese",
        "Crumplehorn",
        "Snickersbar",
        "Banglesnatch",
        "Stinkyrash",
        "Cameltoe",
        "Chickenbroth",
        "Concubine",
        "Candygram",
        "Moldyspore",
        "Chuckecheese",
        "Cankersore",
        "Crimpysnitch",
        "Wafflesmack",
        "Chowderpants",
        "Toodlesnoot",
        "Clavichord",
        "Cuckooclock",
        "Oxfordshire",
        "Cumbersome",
        "Chickenstrips",
        "Battleship",
        "Commonwealth",
        "Cunningsnatch",
        "Custardbath",
        "Kryptonite",
        "Curdlesnoot",
        "Cummerbund",
        "Coochyrash",
        "Crackerdong",
        "Crackerdong",
        "Curdledong",
        "Crackersprout",
        "Crumplebutt",
        "Colonist",
        "Coochierash"
    };

    static std::string GREEN = "\033[032;1m";
    static std::string WHITE = "\033[0m";

    unsigned int n1 = std::rand() % first_names.size();
    unsigned int n2 = std::rand() % last_names.size();

    std::cout << GREEN << first_names[n1] << ' ' << last_names[n2] << std::endl << WHITE;
}
