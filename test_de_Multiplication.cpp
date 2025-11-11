#include <iostream>
#include <limits>
#include <random>
#include <string>

using namespace std;

namespace {

mt19937& rng() {
    static mt19937 gen{random_device{}()};
    return gen;
}

void showMenu() {
    cout << "=============================" << endl;
    cout << "   TABLES DE MULTIPLICATION  " << endl;
    cout << "=============================" << endl;
    cout << "  1 : x * 1" << endl;
    cout << "  2 : x * 2" << endl;
    cout << "  3 : x * 3" << endl;
    cout << "  4 : x * 4" << endl;
    cout << "  5 : x * 5" << endl;
    cout << "  6 : x * 6" << endl;
    cout << "  7 : x * 7" << endl;
    cout << "  8 : x * 8" << endl;
    cout << "  9 : x * 9" << endl;
    cout << "  M : Mode melange" << endl;
    cout << "  ? : Aide" << endl;
    cout << "  Q : Quitter" << endl;
    cout << "=============================" << endl;
    cout << "choix= ";
}

void showHelp() {
    cout << "Evaluation des capacites de calcul" << endl;
    cout << "L'utilisateur doit choisir une table sur laquelle il sera evalue." << endl;
    cout << "A chaque operation, il a droit a 3 essais en cas de mauvaise reponse." << endl;
    cout << "Apres 3 echecs, le programme donne la bonne reponse et passe a l'operation suivante." << endl;
    cout << "Entrer q ou Q pendant un exercice permet de quitter immediatement." << endl;
    cout << "Appuyer sur q/Q pour quitter." << endl;
}

bool readInteger(int &value) {
    if (cin >> value) {
        return true;
    }

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return false;
}

struct Answer {
    bool quit = false;
    bool valid = false;
    int value = 0;
};

Answer readAnswer() {
    string token;
    if (!(cin >> token)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return {};
    }

    if (token == "q" || token == "Q") {
        return {true, false, 0};
    }

    try {
        size_t processed = 0;
        int value = stoi(token, &processed);
        if (processed != token.size()) {
            return {};
        }
        return {false, true, value};
    } catch (...) {
        return {};
    }
}

bool evaluateTable(int multiplier) {
    for (int factor = 1; factor <= 9; ++factor) {
        const int expected = multiplier * factor;
        int attempts = 0;
        bool correct = false;

        while (attempts < 3 && !correct) {
            cout << multiplier << " * " << factor << " = ? ";
            const Answer answer = readAnswer();
            if (answer.quit) {
                return false;
            }
            if (!answer.valid) {
                cout << "Veuillez saisir un entier." << endl;
                continue;
            }

            ++attempts;
            if (answer.value == expected) {
                correct = true;
            } else if (attempts < 3) {
                cout << "Ce n'est pas la bonne reponse, reessayez." << endl;
            }
        }

        if (!correct) {
            cout << "Apres 3 essais, la bonne reponse est : "
                 << multiplier << " * " << factor << " = " << expected << endl;
        }
    }

    cout << endl;

    return true;
}

bool evaluateRandomTables(int count) {
    if (count <= 0) {
        return true;
    }

    uniform_int_distribution<int> dist(1, 9);
    for (int n = 1; n <= count; ++n) {
        const int multiplier = dist(rng());
        cout << "Table aleatoire #" << n << " : " << multiplier << endl;
        if (!evaluateTable(multiplier)) {
            return false;
        }
    }

    return true;
}

int promptRandomCount() {
    while (true) {
        cout << "Combien de tables aleatoires voulez-vous enchainer (0 pour annuler) ? ";
        int value = 0;
        if (!readInteger(value)) {
            cout << "Veuillez saisir un entier." << endl;
            continue;
        }
        if (value < 0) {
            cout << "Merci d'entrer un entier positif ou zero." << endl;
            continue;
        }
        return value;
    }
}

} // namespace

int main() {
    char choice = '\0';

    do {
        showMenu();

        if (!(cin >> choice)) {
            cout << "Entree invalide. Veuillez recommencer." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case '1': case '2': case '3':
            case '4': case '5': case '6':
            case '7': case '8': case '9':
                if (!evaluateTable(choice - '0')) {
                    cout << "Quitter" << endl;
                    return 0;
                }
                break;
            case 'm':
            case 'M': {
                const int total = promptRandomCount();
                if (total == 0) {
                    cout << "Mode melange annule." << endl;
                } else {
                    if (!evaluateRandomTables(total)) {
                        cout << "Quitter" << endl;
                        return 0;
                    }
                }
                break;
            }
            case '?':
                showHelp();
                break;
            case 'q':
            case 'Q':
                cout << "Quitter" << endl;
                break;
            default:
                cout << "Donnee incorrecte." << endl;
                break;
        }
    } while (choice != 'q' && choice != 'Q');

    return 0;
}
