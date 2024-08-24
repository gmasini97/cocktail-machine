#ifndef COCKTAILS_H
#define COCKTAILS_H

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

const PYD_cocktail_t cocktailMoscowMule = {
    "Moscow Mule",
    2,
    {
        {"Vodka",50,0},
        {"Ginger Beer",125,0}
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
const PYD_cocktail_t cocktailKamikaze = {
    "Kamikaze",
    3,
    {
        {"Vodka",25,0},
        {"Triple Sec",25,0},
        {"Succo Di Limone ",25,0}
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
const PYD_cocktail_t cocktailGinLemon = {
    "Gin Lemon",
    2,
    {
        {"Gin",50,0},
        {"Lemon Soda",125,0}
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
const PYD_cocktail_t cocktailCubaLibre = {
    "Cuba Libre",
    3,
    {
        {"Rum",50,0},
        {"Cola",125,0},
        {"Succo Di Lime",10,1}
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

const PYD_cocktail_t* PYD_cocktails[] =
{
    &cocktailMoscowMule,
    &cocktailVodkaLemon,
    &cocktailKamikaze,
    &cocktailGinTonic,
    &cocktailGinLemon,
    &cocktailLondonMule,
    &cocktailCubaLibre,
    &cocktailNegroni
};

#endif /* COCKTAILS_H */