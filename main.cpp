#include <SDL_image.h>
#include <SDL.h>

#include <iostream>

#include "include/interface.hpp"
#include "include/grid.hpp"
#include "include/constants.hpp"
#include "include/game.hpp"
#include "include/tetromino.hpp"

int main(int argc, char* argv[]){

    Grid grid(5,7);
    grid.affiche();


    // reel code
    Interface interface;
    interface.inter_init();

// loading all textures
    SDL_Texture* blocktextures[NUM_BLOCK_SPRITES*NUM_LEVELS*NUM_POWERS];
    interface.texture_load_blocks(blocktextures);
    
    Game game(GRID_SIZE_X, GRID_SIZE_Y);

    //ici maelouille !
    
    //end-------------------------------------------------------------------------------------------------------------

    // tests
    bool game_ended = true;
    bool running = true;
    int move_x = 0;
    int move_y = 0;
    int move_rotate = 0;
    int fall_mode = 0;
    
    // Game loop
    while (running) {

        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type==SDL_QUIT){
                running=0;
            }
            if (event.type==SDL_KEYDOWN && not game_ended){
                if (event.key.keysym.sym==SDLK_LEFT){move_x = -1;}
                if (event.key.keysym.sym==SDLK_RIGHT){move_x = 1;}
                if (event.key.keysym.sym==SDLK_UP){move_rotate = -1;}
                if (event.key.keysym.sym==SDLK_DOWN){move_y = 1;}
                if (event.key.keysym.sym==SDLK_SPACE){fall_mode = 1;}
            if (event.type==SDL_KEYUP){
                if ((move_x == -1)&&(event.key.keysym.sym==SDLK_LEFT)){move_x = 0;}
                if ((move_x == 1)&&(event.key.keysym.sym==SDLK_RIGHT)){move_x = 0;}
                if ((move_y == 1)&&(event.key.keysym.sym==SDLK_DOWN)){move_y = 0;}
            }
        }




        interface.inter_update(blocktextures);

    }
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