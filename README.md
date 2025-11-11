# Multiplication Coach

Petit quiz C++ pour réviser les tables de multiplication : neuf tables classiques, trois essais par calcul, mode mélange pour enchaîner des tables aléatoires et possibilité de quitter à tout moment en tapant `q` ou `Q`.

## Fonctionnalités

- Menu interactif pour choisir une table précise (`1` à `9`) ou le mode mélange (`M`).
- Chaque opération offre trois tentatives avant d’afficher la bonne réponse.
- Saisie robuste : les entrées non numériques sont ignorées et l’utilisateur peut terminer une session en entrant `q/Q` même pendant un exercice.
- Mode mélange configurable : choisissez combien de tables aléatoires enchaîner.

## Compilation

Assure-toi de disposer d’un compilateur C++11 (ou plus récent) :

```bash
g++ test_de_Multiplication.cpp -o test_de_Multiplication
```

Windows (MSVC) :

```cmd
cl /EHsc test_de_Multiplication.cpp
```

## Exécution

```bash
./test_de_Multiplication                # Linux/macOS
test_de_Multiplication.exe              # Windows
```

Suis ensuite les instructions à l’écran pour choisir une table ou lancer le mode mélange.
