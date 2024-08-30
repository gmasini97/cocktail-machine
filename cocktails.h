#ifndef COCKTAILS_H
#define COCKTAILS_H

// To review: Cosmopolitan

struct PYD_ingredient_t
{
    char * name;
    uint8_t quantity;
    bool optional;
};

struct PYD_cocktail_t
{
    char* name;
    uint8_t len;
    PYD_ingredient_t ingredients[];
};

const PYD_cocktail_t cocktailAmericano = {
    "Americano",
    3,
    {
        {"Campari",30,0},
        {"Vermouth",30,0},
        {"Soda",10,1}
    }
};
const PYD_cocktail_t cocktailAperolSpritz = {
    "Aperol Spritz",
    3,
    {
        {"Prosecco",60,0},
        {"Aperol",40,0},
        {"Soda",10,1}
    }
};
const PYD_cocktail_t cocktailBellini = {
    "Bellini",
    2,
    {
        {"Prosecco",100,0},
        {"Succo Di Pesca",50,0}
    }
};
const PYD_cocktail_t cocktailBlackRussian = {
    "Black Russian",
    2,
    {
        {"Vodka",50,0},
        {"Liquore Al Caffè",20,0}
    }
};
const PYD_cocktail_t cocktailCampariSpritz = {
    "Campari Spritz",
    3,
    {
        {"Prosecco",60,0},
        {"Campari",40,0},
        {"Soda",10,1}
    }
};
const PYD_cocktail_t cocktailCosmopolitan = {
    "Cosmopolitan",
    4,
    {
        {"Vodka",40,0},
        {"Triple Sec",15,0},
        {"Succo Di Lime",15,0},
        {"Succo Di Mirtilli Rossi",30,0}
    }
};
const PYD_cocktail_t cocktailCubaLibre = {
    "Cuba Libre",
    3,
    {
        {"Rum",50,0},
        {"Cola",125,0},
        {"Succo Di Lime",10,1}
    }
};
const PYD_cocktail_t cocktailDaiquiri = {
    "Daiquiri",
    3,
    {
        {"Rum Bianco",45,0},
        {"Succo Di Lime",25,0},
        {"Sciroppo Di Zucchero",15,0}
    }
};
const PYD_cocktail_t cocktailDarkNStormy = {
    "Dark 'n' Stormy",
    2,
    {
        {"Rum Scuro",60,0},
        {"Ginger Beer",100,0}
    }
};
const PYD_cocktail_t cocktailFrench75 = {
    "French 75",
    3,
    {
        {"Gin",30,0},
        {"Succo Di Limone",15.0,0},
        {"Champagne",60,0}
    }
};
const PYD_cocktail_t cocktailFrenchMartini = {
    "French Martini",
    3,
    {
        {"Vodka",45,0},
        {"Succo Di Lampone",15,0},
        {"Succo D'Ananas",15,0}
    }
};
const PYD_cocktail_t cocktailGinFizz = {
    "Gin Fizz",
    4,
    {
        {"Gin",45,0},
        {"Succo Di Limone",30,0},
        {"Sciroppo Di Zucchero",10,0},
        {"Soda",80,0}
    }
};
const PYD_cocktail_t cocktailGinLemon = {
    "Gin Lemon",
    2,
    {
        {"Gin",50,0},
        {"Lemon Soda",125,0}
    }
};
const PYD_cocktail_t cocktailGinTonic = {
    "Gin Tonic",
    2,
    {
        {"Gin",50,0},
        {"Tonica",125,0}
    }
};
const PYD_cocktail_t cocktailJohnCollins = {
    "John Collins",
    4,
    {
        {"Gin",45.0,0},
        {"Succo Di Limone",30,0},
        {"Sciroppo Di Zucchero",15,0},
        {"Soda",60,0}
    }
};
const PYD_cocktail_t cocktailKamikaze = {
    "Kamikaze",
    3,
    {
        {"Vodka",25,0},
        {"Triple Sec",25,0},
        {"Succo Di Limone ",25,0}
    }
};
const PYD_cocktail_t cocktailLemonDropMartini = {
    "Lemon Drop Martini",
    3,
    {
        {"Vodka",25,0},
        {"Triple Sec",20,0},
        {"Succo Di Limone",15,0}
    }
};
const PYD_cocktail_t cocktailLondonMule = {
    "London Mule",
    2,
    {
        {"Gin",50,0},
        {"Ginger Beer",125,0}
    }
};
const PYD_cocktail_t cocktailMaiTai = {
    "Mai-tai",
    5,
    {
        {"Rum Bianco",40,0},
        {"Rum Scuro",20,0},
        {"Triple Sec",15.0,0},
        {"Sciroppo Di Zucchero",15.0,0},
        {"Succo Di Lime",10,0}
    }
};
const PYD_cocktail_t cocktailManhattan = {
    "Manhattan",
    2,
    {
        {"Whiskey",50,0},
        {"Vermouth",20,0}
    }
};
const PYD_cocktail_t cocktailMargarita = {
    "Margarita",
    3,
    {
        {"Tequila",35,0},
        {"Triple Sec",20,0},
        {"Succo Di Lime",15,0}
    }
};
const PYD_cocktail_t cocktailMimosa = {
    "Mimosa",
    2,
    {
        {"Champagne",75,0},
        {"Succo D'Arancia",75,0}
    }
};
const PYD_cocktail_t cocktailMojito = {
    "Mojito",
    5,
    {
        {"Rum Bianco",40,0},
        {"Succo Di Limone",30,0},
        {"Soda",10,0}
    }
};
const PYD_cocktail_t cocktailMoscowMule = {
    "Moscow Mule",
    3,
    {
        {"Vodka",50,0},
        {"Ginger Beer",125,0},
        {"Succo Di Lime",5,1}
    }
};
const PYD_cocktail_t cocktailNegroni = {
    "Negroni",
    3,
    {
        {"Gin",25,0},
        {"Vermouth Rosso",25,0},
        {"Bitter",25,0}
    }
};
const PYD_cocktail_t cocktailPinaColada = {
    "Pina Colada",
    3,
    {
        {"Rum Bianco",30,0},
        {"Succo D'Ananas",90,0},
        {"Latte Di Cocco",30,0}
    }
};
const PYD_cocktail_t cocktailSanFrancisco = {
    "San Francisco",
    3,
    {
        {"Succo D'Arancia",50,0},
        {"Succo D'Ananas",50,0},
        {"Soda",50,0},
        {"Granatina",10,0}
    }
};
const PYD_cocktail_t cocktailScrewdriver = {
    "Screwdriver",
    2,
    {
        {"Vodka",50,0},
        {"Succo D'Arancia",100,0}
    }
};
const PYD_cocktail_t cocktailSeaBreeze = {
    "Sea Breeze",
    3,
    {
        {"Vodka",40,0},
        {"Succo Di Mirtilli Rossi",120,0},
        {"Succo Di Pompelmo",30,0}
    }
};
const PYD_cocktail_t cocktailSexOnTheBeach = {
    "Sex On The Beach",
    4,
    {
        {"Vodka",40,0},
        {"Grappa Alla Pesca",20,0},
        {"Succo Di Mirtilli Rossi",40,0},
        {"Succo D'Arancia",40,0},
    }
};
const PYD_cocktail_t cocktailSidecar = {
    "Sidecar",
    3,
    {
        {"Cognac",50,0},
        {"Triple Sec",20,0},
        {"Succo Di Limone",20,0},
    }
};
const PYD_cocktail_t cocktailTequilaSunrise = {
    "Tequila Sunrise",
    3,
    {
        {"Tequila",45,0},
        {"Succo D'Arancia",90,0},
        {"Sciroppo Di Zucchero",15,0},
    }
};
const PYD_cocktail_t cocktailVesper = {
    "Vesper",
    3,
    {
        {"Gin",60,0},
        {"Vodka",15,0},
        {"Lillet Blonde",8,0},
    }
};
const PYD_cocktail_t cocktailVirginPinaColada = {
    "Virgin Pina Colada",
    2,
    {
        {"Succo D'Ananas",75,0},
        {"Latte Di Cocco",75,0}
    }
};
const PYD_cocktail_t cocktailVodkaLemon = {
    "Vodka Lemon",
    2,
    {
        {"Vodka",50,0},
        {"Lemon Soda",100,0}
    }
};
const PYD_cocktail_t cocktailWhiskeySour = {
    "Whiskey Sour",
    3,
    {
        {"Whiskey",45,0},
        {"Succo Di Limone",30,0},
        {"Sciroppo Di Zucchero",15,0},
    }
};
const PYD_cocktail_t cocktailWhiteLady = {
    "White Lady",
    3,
    {
        {"Gin",40,0},
        {"Triple Sec",30,0},
        {"Succo Di Limone",20,0},
    }
};

const PYD_cocktail_t* PYD_cocktails[] =
{
    &cocktailAmericano,
    &cocktailAperolSpritz,
    &cocktailBellini,
    &cocktailBlackRussian,
    &cocktailCampariSpritz,
    &cocktailCosmopolitan,
    &cocktailCubaLibre,
    &cocktailDaiquiri,
    &cocktailDarkNStormy,
    &cocktailFrench75,
    &cocktailFrenchMartini,
    &cocktailGinFizz,
    &cocktailGinLemon,
    &cocktailGinTonic,
    &cocktailJohnCollins,
    &cocktailKamikaze,
    &cocktailLemonDropMartini,
    &cocktailLondonMule,
    &cocktailMaiTai,
    &cocktailManhattan,
    &cocktailMargarita,
    &cocktailMimosa,
    &cocktailMoscowMule,
    &cocktailNegroni,
    &cocktailPinaColada,
    &cocktailScrewdriver,
    &cocktailSeaBreeze,
    &cocktailSexOnTheBeach,
    &cocktailSidecar,
    &cocktailTequilaSunrise,
    &cocktailVesper,
    &cocktailVodkaLemon,
    &cocktailWhiskeySour,
    &cocktailWhiteLady
};

#endif /* COCKTAILS_H */