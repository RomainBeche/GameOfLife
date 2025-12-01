```mermaid
flowchart LR
    User(["Utilisateur"])

    subgraph System["Système : Jeu de la Vie"]
        LP["Lancer le programme"]
        CG["Charger une grille depuis un fichier"]
        CM["Choisir le mode de fonctionnement"]
        SG["Simuler l'évolution de la grille"]
        AR["Appliquer les règles du Jeu de la Vie"]
        AF["Afficher la grille"]
        EX["Exporter la grille"]
        AS["Arrêter la simulation"]
        QU["Quitter l'application"]
        MC["Mode console"]
        MG["Mode graphique"]
    end

    User --> LP
    User --> CM
    User --> AS
    User --> QU

    LP --> CG
    CM --> MC
    CM --> MG

    MC --> SG
    MC --> EX

    MG --> SG
    MG --> AF

    SG --> AR
    SG --> AS
