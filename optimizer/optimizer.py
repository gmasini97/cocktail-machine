import json
import numpy as np

def ingredientsAvailable(recipe, ingredients):
    for x in recipe['ingredients']:
        if 'ingredient' not in x:
            continue
        if x['ingredient'] not in ingredients:
            return False
    return True

with open('recipes.json', encoding='utf8') as f:
    recipes = json.load(f)
    ingredients_raw = [x['ingredient'] for recipe in recipes for x in recipe['ingredients'] if 'ingredient' in x]
    ingredients = list(set(ingredients_raw))
    ingredients.sort()
    counts = [ingredients_raw.count(ingredient) for ingredient in ingredients]

    ingredients = np.array(ingredients)
    probs = counts/np.sum(counts)

    bestCombination = []
    bestCombinationCount = 0

    try:
        while True:
            // TODO: implement genetic algorithm to find the best combination
            // https://pygad.readthedocs.io/en/latest/
            combination = np.random.choice(ingredients, size=8, replace=False, p=probs)
            combination.sort()
            count = [ingredientsAvailable(recipe, combination) for recipe in recipes].count(True)
            if count > bestCombinationCount:
                bestCombination = combination
                bestCombinationCount = count
                print(bestCombination, bestCombinationCount)
                if bestCombinationCount == len(recipes):
                    break
    except KeyboardInterrupt:
        print("Cocktails available:")
        for recipe in recipes:
            if ingredientsAvailable(recipe, bestCombination):
                print(recipe['name'])