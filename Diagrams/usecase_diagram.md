```mermaid
flowchart LR
User(["Utilisateur"])

    subgraph System["Système : Jeu de la Vie"]
        LP["Lancer le programme"]
        CG["Charger une grille depuis un fichier"]
        CM["Choisir le mode de fonctionnement"]
    end

    User --> LP
    User --> CG
    User --> CM
