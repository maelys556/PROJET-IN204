#include <SDL_image.h>
#include <SDL.h>

#include <iostream>
#include "include/interface.hpp"
#include "include/grid.hpp"
#include "include/constants.hpp"

int main(int argc, char* argv[]){

    Grid grid(5,7);
    grid.affiche();


    // reel code
    Interface interface;
    interface.inter_init();

// loading all textures
    SDL_Texture* blocktextures[NUM_BLOCK_SPRITES*NUM_LEVELS*NUM_POWERS];
    interface.texture_load_blocks(blocktextures);
    
    
    
    //end-------------------------------------------------------------------------------------------------------------

    // tests
    int boucle = 350;
    while (boucle>0){
        interface.inter_update(blocktextures);
        boucle-=1;
    }
};

/*    Classe Piece :
        Attributs :
            Forme de la pièce
            Couleur de la pièce
            Position actuelle sur la grille
        Méthodes :
            Déplacer vers le bas
            Déplacer à gauche
            Déplacer à droite
            Rotation

    Classe Grille :
        Attributs :
            Matrice représentant les cases de la grille
        Méthodes :
            Ajouter une pièce à la grille
            Supprimer une ligne complète
            Vérifier les collisions

    Classe Jeu :
        Attributs :
            État du jeu (en cours, en pause, terminé)
            Score actuel
            Niveau actuel
        Méthodes :
            Initialiser le jeu
            Mettre à jour le jeu
            Gérer les entrées utilisateur
            Afficher le jeu

    Classe InterfaceUtilisateur :
        Attributs :
            Fenêtre de l'interface graphique
        Méthodes :
            Afficher la grille et les pièces
            Gérer les entrées utilisateur (clavier pour déplacer et faire pivoter les pièces)

    Classe Score :
        Attributs :
            Score total du joueur
            Meilleur score
        Méthodes :
            Mettre à jour le score
            Enregistrer les meilleurs scores*/