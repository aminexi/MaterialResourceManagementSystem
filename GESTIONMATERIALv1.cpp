#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib> // Pour utiliser la fonction system()

using namespace std;

class Material {
protected:
    string nom;
    string reference;
    string type;
    int quantite;

public:
    Material(const string& _nom, const string& _reference, const string& _type, int _quantite)
        : nom(_nom), reference(_reference), type(_type), quantite(_quantite) {}

    void afficher() const {
        cout << "Nom: " << nom << ", Reference: " << reference << ", Type: " << type << ", Quantite: " << quantite << endl;
    }

    const string& getNom() const { return nom; }
    const string& getReference() const { return reference; }
    int getQuantite() const { return quantite; }

    void modifierQuantite(int nouvelleQuantite) {
        quantite = nouvelleQuantite;
    }
};

class Departement {
private:
    string nom;
    vector<Material> materiaux;

public:
    Departement(const string& _nom) : nom(_nom) {}

    const string& getNom() const { return nom; }

    void ajouterMaterial(const Material& material) {
        materiaux.push_back(material);
    }

    void modifierMaterial(const string& ref, int nouvelleQuantite) {
        for (auto& material : materiaux) {
            if (material.getReference() == ref) {
                material.modifierQuantite(nouvelleQuantite);
                break;
            }
        }
    }

    void supprimerMaterial(const string& ref) {
        materiaux.erase(remove_if(materiaux.begin(), materiaux.end(),
            [ref](const Material& material) { return material.getReference() == ref; }), materiaux.end());
    }

    void rechercherMaterial(const string& nom, const string& ref) const {
        for (const auto& material : materiaux) {
            if (material.getNom() == nom || material.getReference() == ref) {
                material.afficher();
            }
        }
    }

    int nombreMaterial() const {
        return materiaux.size();
    }

    void afficherMateriaux() const {
        cout << "---- Liste des materiaux du departement " << getNom() << " ----" << endl;
        for (const auto& material : materiaux) {
            material.afficher();
        }
    }

    vector<Material> getMateriaux() const {
        return materiaux;
    }
};

class Utilisateur {
private:
    string nom;
    string identifiant;
    Departement* departement;
    bool peutModifier; // droit d'accès

public:
    Utilisateur(const string& _nom, const string& _identifiant)
        : nom(_nom), identifiant(_identifiant), departement(nullptr), peutModifier(false) {}

    void affecterDepartement(Departement* _departement) {
        departement = _departement;
    }

    void attribuerDroitsAcces(bool droit) {
        peutModifier = droit;
    }

    bool aLeDroit() const {
        return peutModifier;
    }

    void afficher() const {
        cout << "Nom: " << nom << ", Identifiant: " << identifiant << ", Departement: ";
        if (departement)
            cout << departement->getNom();
        else
            cout << "Aucun";
        cout << ", Acces: ";
        if (peutModifier)
            cout << "Peut modifier" << endl;
        else
            cout << "Lecture seule" << endl;
    }

    const string& getIdentifiant() const {
        return identifiant;
    }
};

class Demande {
private:
    string nom;
    string description;
    int priorite;

public:
    Demande(const string& _nom, const string& _description, int _priorite)
        : nom(_nom), description(_description), priorite(_priorite) {}

    void afficher() const {
        cout << "Demande de: " << nom << ", Description: " << description << ", Priorite: " << priorite << endl;
    }

    int getPriorite() const {
        return priorite;
    }
};

class Maintenance {
private:
    string description;
    string date;

public:
    Maintenance(const string& _description, const string& _date)
        : description(_description), date(_date) {}

    void afficher() const {
        cout << "Description: " << description << ", Date: " << date << endl;
    }
};

class Stock {
private:
    string type;
    int quantite;
    int seuilCritique;

public:
    Stock(const string& _type, int _quantite, int _seuilCritique)
        : type(_type), quantite(_quantite), seuilCritique(_seuilCritique) {}

    void afficher() const {
        cout << "Type: " << type << ", Quantite: " << quantite << ", Seuil Critique: " << seuilCritique << endl;
    }

    bool estCritique() const {
        return quantite <= seuilCritique;
    }
};

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void afficherSeparateur() {
    cout << "\n------------------------------------------------------------\n\n";
}

void afficherMenu() {
    cout << "Menu Principal:\n";
    cout << "1. Gestion des Materiaux\n";
    cout << "2. Gestion des Utilisateurs\n";
    cout << "3. Gestion des Inventaires\n"; // Ajout de l'option pour la gestion des inventaires
    cout << "4. Gestion des Demandes de Materiel\n"; // Ajout de l'option pour la gestion des demandes de matériel
    cout << "5. Gestion des Reparations et Maintenance\n"; // Ajout de l'option pour la gestion des réparations et maintenance
    cout << "6. Gestion des Stocks\n"; // Ajout de l'option pour la gestion des stocks
    cout << "0. Quitter\n";
    cout << "Choix: ";
}

void afficherUtilisateurs(const vector<Utilisateur>& utilisateurs) {
    cout << "---- Liste des utilisateurs ----" << endl;
    for (const auto& user : utilisateurs) {
        user.afficher();
    }
}

void afficherInventaireComplet(const vector<Departement*>& departements) {
    cout << "Inventaire complet :\n";
    for (const auto& dep : departements) {
        cout << "---- Departement : " << dep->getNom() << " ----" << endl;
        dep->afficherMateriaux();
        cout << endl;
    }
}

void afficherInventaireDepartement(const vector<Departement*>& departements) {
    cout << "Choisir un departement :\n";
    for (size_t i = 0; i < departements.size(); ++i) {
        cout << i + 1 << ". " << departements[i]->getNom() << endl;
    }
    int choix;
    cout << "Choix : ";
    cin >> choix;
    if (choix >= 1 && choix <= departements.size()) {
        cout << "---- Departement : " << departements[choix - 1]->getNom() << " ----" << endl;
        departements[choix - 1]->afficherMateriaux();
        cout << endl;
    } else {
        cout << "Choix invalide." << endl;
    }
}

void afficherDemandes(const vector<Demande>& demandes) {
    cout << "---- Liste des demandes de materiel ----" << endl;
    for (const auto& demande : demandes) {
        demande.afficher();
    }
}

void afficherReparations(const vector<Maintenance>& maintenances) {
    cout << "---- Liste des interventions de maintenance ----" << endl;
    for (const auto& maintenance : maintenances) {
        maintenance.afficher();
    }
}

void afficherStocks(const vector<Stock>& stocks) {
    cout << "---- Liste des stocks ----" << endl;
    for (const auto& stock : stocks) {
        stock.afficher();
    }
}

int main() {
    int choix;
    Departement* dep1 = new Departement("Ordinateurs");
    Departement* dep2 = new Departement("Réseau");
    Departement* dep3 = new Departement("Logistique");
    Departement* dep4 = new Departement("Marketing");

    vector<Departement*> departements = {dep1, dep2, dep3, dep4};

    dep1->ajouterMaterial(Material("Ordinateur portable", "REF001", "Portable", 10));
    dep1->ajouterMaterial(Material("Ordinateur de bureau", "REF002", "Fixe", 20));
    dep2->ajouterMaterial(Material("Routeur", "REF003", "Sans fil", 5));
    dep2->ajouterMaterial(Material("Switch", "REF004", "Ethernet", 8));
    dep3->ajouterMaterial(Material("Cartons", "REF005", "Emballage", 1000));
    dep4->ajouterMaterial(Material("Brochures", "REF006", "Marketing", 500));

    vector<Utilisateur> utilisateurs;
    utilisateurs.emplace_back("Amine", "A123");
    utilisateurs.emplace_back("saad", "B456");

    vector<Demande> demandes;
    demandes.emplace_back("Amine", "Remplacement de moniteur", 2);
    demandes.emplace_back("saad", "Ajout de RAM", 1);

    vector<Maintenance> maintenances;
    maintenances.emplace_back("Nettoyage", "01/04/2024");
    maintenances.emplace_back("Remplacement disque dur", "05/04/2024");

    vector<Stock> stocks;
    stocks.emplace_back("Carte mère", 20, 5);
    stocks.emplace_back("Clavier", 50, 10);
    stocks.emplace_back("Moniteur", 30, 8);

    do {
        clearScreen();
        afficherMenu();
        cin >> choix;

        switch (choix) {
            case 1: {
                string identifiant;
                clearScreen();
                cout << "Veuillez vous identifier: ";
                cin >> identifiant;

                Utilisateur* utilisateur = nullptr;
                for (auto& user : utilisateurs) {
                    if (user.getIdentifiant() == identifiant) {
                        utilisateur = &user;
                        break;
                    }
                }

                if (utilisateur == nullptr) {
                    cout << "Utilisateur non trouvé." << endl;
                    break;
                }

                clearScreen();
                cout << "Menu Gestion des Materiaux:\n";
                cout << "1. Ajouter un materiel\n";
                cout << "2. Modifier un materiel\n";
                cout << "3. Supprimer un materiel\n";
                cout << "4. Rechercher un materiel\n";
                cout << "5. Afficher les materiaux\n";
                cout << "0. Retour\n";
                cout << "Choix: ";
                int choixMaterial;
                cin >> choixMaterial;

                switch (choixMaterial) {
                    case 1: {
                        if (!utilisateur->aLeDroit()) {
                            cout << "Vous n'avez pas les droits suffisants pour effectuer cette action." << endl;
                            break;
                        }

                        string nom, ref, type;
                        int quantite;
                        int choixDepartement;
                        clearScreen();
                        cout << "Nom: ";
                        cin >> nom;
                        cout << "Reference: ";
                        cin >> ref;
                        cout << "Type: ";
                        cin >> type;
                        cout << "Quantite: ";
                        cin >> quantite;
                        cout << "Choisir le departement (1. " << dep1->getNom() << ", 2. " << dep2->getNom() << ", 3. " << dep3->getNom() << ", 4. " << dep4->getNom() << "): ";
                        cin >> choixDepartement;
                        if (choixDepartement >= 1 && choixDepartement <= departements.size()) {
                            departements[choixDepartement - 1]->ajouterMaterial(Material(nom, ref, type, quantite));
                        } else {
                            cout << "Choix invalide." << endl;
                        }
                        break;
                    }
                    case 2: {
                        if (!utilisateur->aLeDroit()) {
                            cout << "Vous n'avez pas les droits suffisants pour effectuer cette action." << endl;
                            break;
                        }

                        string ref;
                        int nouvelleQuantite;
                        int choixDepartement;
                        clearScreen();
                        cout << "Reference du materiel a modifier: ";
                        cin >> ref;
                        cout << "Nouvelle quantite: ";
                        cin >> nouvelleQuantite;
                        cout << "Choisir le departement (1. " << dep1->getNom() << ", 2. " << dep2->getNom() << ", 3. " << dep3->getNom() << ", 4. " << dep4->getNom() << "): ";
                        cin >> choixDepartement;
                        if (choixDepartement >= 1 && choixDepartement <= departements.size()) {
                            departements[choixDepartement - 1]->modifierMaterial(ref, nouvelleQuantite);
                        } else {
                            cout << "Choix invalide." << endl;
                        }
                        break;
                    }
                    case 3: {
                        if (!utilisateur->aLeDroit()) {
                            cout << "Vous n'avez pas les droits suffisants pour effectuer cette action." << endl;
                            break;
                        }

                        string ref;
                        int choixDepartement;
                        clearScreen();
                        cout << "Reference du materiel a supprimer: ";
                        cin >> ref;
                        cout << "Choisir le departement (1. " << dep1->getNom() << ", 2. " << dep2->getNom() << ", 3. " << dep3->getNom() << ", 4. " << dep4->getNom() << "): ";
                        cin >> choixDepartement;
                        if (choixDepartement >= 1 && choixDepartement <= departements.size()) {
                            departements[choixDepartement - 1]->supprimerMaterial(ref);
                        } else {
                            cout << "Choix invalide." << endl;
                        }
                        break;
                    }
                    case 4: {
                        string nom, ref;
                        int choixDepartement;
                        clearScreen();
                        cout << "Nom du materiel a rechercher: ";
                        cin >> nom;
                        cout << "Reference du materiel a rechercher: ";
                        cin >> ref;
                        cout << "Choisir le departement (1. " << dep1->getNom() << ", 2. " << dep2->getNom() << ", 3. " << dep3->getNom() << ", 4. " << dep4->getNom() << "): ";
                        cin >> choixDepartement;
                        if (choixDepartement >= 1 && choixDepartement <= departements.size()) {
                            departements[choixDepartement - 1]->rechercherMaterial(nom, ref);
                        } else {
                            cout << "Choix invalide." << endl;
                        }
                        break;
                    }
                    case 5:
                        clearScreen();
                        for (auto dep : departements) {
                            dep->afficherMateriaux();
                        }
                        afficherSeparateur();
                        break;
                }
                cout << "\nAppuyez sur Entrer pour continuer...";
                cin.ignore();
                cin.get();
                break;
            }
            case 2: {
                int choixUtilisateur;
                do {
                    clearScreen();
                    cout << "\nMenu Gestion des Utilisateurs:\n";
                    cout << "1. Creer un utilisateur\n";
                    cout << "2. Affecter un utilisateur a un departement\n";
                    cout << "3. Donner l'acces d'un utilisateur a un departement\n";
                    cout << "4. Retirer l'acces d'un utilisateur a un departement\n";
                    cout << "5. Afficher les utilisateurs\n";
                    cout << "0. Retour\n";
                    cout << "Choix: ";
                    cin >> choixUtilisateur;

                    switch (choixUtilisateur) {
                        case 1: {
                            string nom, identifiant;
                            clearScreen();
                            cout << "Nom de l'utilisateur: ";
                            cin >> nom;
                            cout << "Identifiant: ";
                            cin >> identifiant;
                            utilisateurs.emplace_back(nom, identifiant); // Ajout de l'utilisateur créé au vector
                            break;
                        }
                        case 2: {
                            int choixDepartement;
                            clearScreen();
                            afficherUtilisateurs(utilisateurs);
                            cout << "Choisir l'utilisateur:\n";
                            cout << "0. Retour\n";
                            cout << "Choix: ";
                            cin >> choixUtilisateur;
                            if (choixUtilisateur == 0) break;
                            cout << "Choisir le departement (1. " << dep1->getNom() << ", 2. " << dep2->getNom() << ", 3. " << dep3->getNom() << ", 4. " << dep4->getNom() << "): ";
                            cin >> choixDepartement;
                            if (choixDepartement >= 1 && choixDepartement <= departements.size()) {
                                utilisateurs[choixUtilisateur - 1].affecterDepartement(departements[choixDepartement - 1]);
                            } else {
                                cout << "Choix invalide." << endl;
                            }
                            break;
                        }
                        case 3: {
                            int choixDepartement;
                            bool acces;
                            clearScreen();
                            afficherUtilisateurs(utilisateurs);
                            cout << "Choisir l'utilisateur:\n";
                            cout << "0. Retour\n";
                            cout << "Choix: ";
                            cin >> choixUtilisateur;
                            if (choixUtilisateur == 0) break;
                            cout << "Donner l'acces (1. Oui, 0. Non): ";
                            cin >> acces;
                            utilisateurs[choixUtilisateur - 1].attribuerDroitsAcces(acces);
                            cout << "Choisir le departement (1. " << dep1->getNom() << ", 2. " << dep2->getNom() << ", 3. " << dep3->getNom() << ", 4. " << dep4->getNom() << "): ";
                            cin >> choixDepartement;
                            if (choixDepartement >= 1 && choixDepartement <= departements.size()) {
                                utilisateurs[choixUtilisateur - 1].affecterDepartement(departements[choixDepartement - 1]);
                            } else {
                                cout << "Choix invalide." << endl;
                            }
                            break;
                        }
                        case 4: {
                            int choixDepartement;
                            clearScreen();
                            afficherUtilisateurs(utilisateurs);
                            cout << "Choisir l'utilisateur:\n";
                            cout << "0. Retour\n";
                            cout << "Choix: ";
                            cin >> choixUtilisateur;
                            if (choixUtilisateur == 0) break;
                            utilisateurs[choixUtilisateur - 1].affecterDepartement(nullptr);
                            cout << "Choisir le departement (1. " << dep1->getNom() << ", 2. " << dep2->getNom() << ", 3. " << dep3->getNom() << ", 4. " << dep4->getNom() << "): ";
                            cin >> choixDepartement;
                            if (choixDepartement >= 1 && choixDepartement <= departements.size()) {
                                utilisateurs[choixUtilisateur - 1].affecterDepartement(departements[choixDepartement - 1]);
                            } else {
                                cout << "Choix invalide." << endl;
                            }
                            break;
                        }
                        case 5:
                            clearScreen();
                            afficherUtilisateurs(utilisateurs);
                            afficherSeparateur();
                            break;
                    }
                    cout << "\nAppuyez sur Entrer pour continuer...";
                    cin.ignore();
                    cin.get();
                } while (choixUtilisateur != 0);
                break;
            }
            case 3: {
                clearScreen();
                int choixInventaire;
                cout << "Menu Gestion des Inventaires:\n";
                cout << "1. Afficher l'inventaire complet\n";
                cout << "2. Afficher l'inventaire d'un departement\n";
                cout << "0. Retour\n";
                cout << "Choix: ";
                cin >> choixInventaire;
                switch (choixInventaire) {
                    case 1:
                        clearScreen();
                        afficherInventaireComplet(departements);
                        afficherSeparateur();
                        break;
                    case 2:
                        clearScreen();
                        afficherInventaireDepartement(departements);
                        afficherSeparateur();
                        break;
                    case 0:
                        break;
                    default:
                        cout << "Choix invalide." << endl;
                        break;
                }
                cout << "\nAppuyez sur Entrer pour continuer...";
                cin.ignore();
                cin.get();
                break;
            }
            case 4: {
                clearScreen();
                afficherDemandes(demandes);
                afficherSeparateur();
                cout << "\nAppuyez sur Entrer pour continuer...";
                cin.ignore();
                cin.get();
                break;
            }
		           case 5: {
		    clearScreen();
		    cout << "Menu Gestion des Reparations et Maintenance:\n";
		    cout << "1. Afficher les interventions de maintenance\n";
		    cout << "2. Ajouter une intervention de maintenance\n"; // Nouvelle option pour ajouter une réparation
		    cout << "0. Retour\n";
		    cout << "Choix: ";
		    int choixReparation;
		    cin >> choixReparation;
		
		    switch (choixReparation) {
		        case 1:
		            clearScreen();
		            afficherReparations(maintenances);
		            afficherSeparateur();
		            break;
		        case 2: {
		            clearScreen();
		            string description, date;
		            cout << "Ajouter une intervention de maintenance:\n";
		            cout << "Description: ";
		            cin >> description;
		            cout << "Date (format JJ/MM/AAAA): ";
		            cin >> date;
		            maintenances.emplace_back(description, date); // Ajouter une nouvelle réparation
		            cout << "Intervention ajoutée avec succes.\n";
		            break;
		        }
		        case 0:
		            break;
		        default:
		            cout << "Choix invalide." << endl;
		            break;
		    }
		    cout << "\nAppuyez sur Entrer pour continuer...";
		    cin.ignore();
		    cin.get();
		    break;
}
            case 6: {
                clearScreen();
                afficherStocks(stocks);
                afficherSeparateur();
                cout << "\nAppuyez sur Entrer pour continuer...";
                cin.ignore();
                cin.get();
                break;
            }
            case 0:
                cout << "Au revoir!" << endl;
                break;
            default:
                cout << "Choix invalide." << endl;
                break;
        }
    } while (choix != 0);

    // Nettoyage de la mémoire
    for (auto dep : departements) {
        delete dep;
    }

    return 0;
}

