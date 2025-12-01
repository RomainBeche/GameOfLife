```mermaid
flowchart TD

    A([Début]) --> B["Lancer le programme"]
    B --> C["Charger la grille depuis un fichier"]
    C --> D["Initialiser les paramètres (mode, itérations, arrêt)"]
    D --> E{"Mode console ou graphique ?"}

    E -- "Console" --> C0["Lire les paramètres du mode console"]

    C0 --> LOOP_C

    subgraph LOOP_C[Cycle console]
        direction TB
        C1{"Condition d'arrêt ?"} 
        C1 -- "Oui" --> C_END["Afficher le résultat final"] --> Z([Fin])
        C1 -- "Non" --> C2["Créer une nouvelle grille vide"]

        C2 --> SUB_C
        subgraph SUB_C[Boucle cellules]
            direction TB
            CC1["Compter les voisins vivants"]
            CC1 --> RULES
            
            subgraph RULES["Règles du jeu de la vie"]
                direction TB
                R1{"Cellule vivante ?"}
                R1 -- "Oui" --> R2{"Voisins = 2 ou 3 ?"}
                R2 -- "Oui" --> R3["Survie"]
                R2 -- "Non" --> R4["Mort"]
                R1 -- "Non" --> R5{"Voisins = 3 ?"}
                R5 -- "Oui" --> R6["Naissance"]
                R5 -- "Non" --> R7["Reste morte"]
            end
            
            RULES --> CC2["Écrire le nouvel état dans la nouvelle grille"]
        end

        SUB_C --> C3["Remplacer l'ancienne grille par la nouvelle"]
        C3 --> C4["Enregistrer la grille"]
        C4 --> C5["Incrémenter l'itération"]
        C5 --> C1
    end

    E -- "Graphique" --> G0["Initialiser la fenêtre graphique"]

    G0 --> LOOP_G

    subgraph LOOP_G[Cycle graphique]
        direction TB
        G1{"Fenêtre ouverte et pas de condition d'arrêt ?"}
        G1 -- "Non" --> Z
        G1 -- "Oui" --> G2["Traiter les interactions utilisateur"]
        G2 --> G3["Attendre la durée choisie"]
        G3 --> G4["Créer une nouvelle grille vide"]

        G4 --> SUB_G
        subgraph SUB_G[Boucle cellules]
            direction TB
            GG1["Compter les voisins vivants"]
            GG1 --> RULES_G
            
            subgraph RULES_G["Règles du jeu de la vie"]
                direction TB
                RG1{"Cellule vivante ?"}
                RG1 -- "Oui" --> RG2{"Voisins = 2 ou 3 ?"}
                RG2 -- "Oui" --> RG3["Survie"]
                RG2 -- "Non" --> RG4["Mort"]
                RG1 -- "Non" --> RG5{"Voisins = 3 ?"}
                RG5 -- "Oui" --> RG6["Naissance"]
                RG5 -- "Non" --> RG7["Reste morte"]
            end

            RULES_G --> GG2["Écrire le nouvel état"]
        end

        SUB_G --> G5["Mettre à jour la grille"]
        G5 --> G6["Redessiner la grille"]
        G6 --> G1
    end
