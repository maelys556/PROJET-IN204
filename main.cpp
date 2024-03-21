#include <SDL_image.h>
#include <SDL.h>

#include <iostream>

#include "include/interface.hpp"
#include "include/grid.hpp"
#include "include/constants.hpp"
#include "include/game.hpp"
#include "include/tetromino.hpp"

int main(int argc, char* argv[]){

    // reel code
    int tick = 0;
    Interface interface;
    interface.inter_init();

    Game current_game(GRID_SIZE_X, GRID_SIZE_Y);
    current_game.getNewBlock();

// loading all textures
    SDL_Texture* blocktextures[NUM_BLOCK_SPRITES*NUM_LEVELS*NUM_POWERS + 1];
    interface.texture_load_blocks(blocktextures);
    
    Game game(GRID_SIZE_X, GRID_SIZE_Y);

    //ici maelouille ! -------------------------------------------------------------------------------------------------
    
    /* Au début, on prend un nb aléatoire et on créer un nouveau block (le block construit par défaut dans Game est 
    un Tetromino mais nous on veut un tetromino plus spécifique comme IBlock etc)
    Ensuite les nouveaux tetrominos sont directement créés qd un bloc est verouillé. */

    //game.currentBlock = game.getNewBlock(); // getNewBlock() renvoie un tetromino aléatoire parmi les 7 formes

    //////////// Dans la boucle : /////////////////////////
    /* - Vérifier les inputs : utiliser game.moveLeft(), game.moveRight(), game.moveDown(), game.rotate() et 
    game.undoRotation() si une rotation inverse est possible dans Tetris (jsp), bloquer le tetromino si l'utilisateur
    veut le faire descendre rapidement avec game.moveDownFast()
    - Faire descendre le bloc avec moveDown() à chaque période de temps
    - Afficher la grille + tetromino à chaque période de temps
    - vérifier à chaque période de temps si une ligne est complète avec game.grid.completedRows()
    - si une/des ligne est complète actualiser le score avec updateScore() dans classe Grid
        et supprimer les lignes complètes avec deleteRow(row) dans classe Grid
        std::vector<int> completed_rows = grid.completedRows();
        for (int i=0; i<completed_rows.size(); i++) {
            deleteRow(completed_rows[i]); avec completed_rows[i] qui est l'indice de la ligne à supprimer
        }
    - créer un nouveau tetromino avec game.currentBlock = game.getNewBlock() (au final je fais une fonction séparée, je l'enlève de la
    fonction lockBlock() car sinon je pense qu'on va avoir des problèmes de timing).
    */
    

    //end-------------------------------------------------------------------------------------------------------------

    // tests
    bool game_ended = false;
    bool running = true;
    int move_x(0) , move_y(0) , move_rotate(0);
    
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
                if (event.key.keysym.sym==SDLK_UP){move_rotate = 1;}
                if (event.key.keysym.sym==SDLK_DOWN){move_y = 1;}
                if (event.key.keysym.sym==SDLK_SPACE){current_game.fast_mode = true;}
            }
        }
        tick += 1;
        if (tick % 50 == 0) {
            if (move_x == -1) {
                current_game.moveLeft();
                move_x = 0;
            }
            if (move_x == 1) {
                current_game.moveRight();
                move_x = 0;
            }
            if (move_y == 1) {
                current_game.moveDown();
                move_y = 0;
            }
        }
        if (tick % 10 == 0) {
            if (move_rotate == 1) {
                current_game.rotate();
                move_rotate = false;
            }
        }
        if ((tick + 25) % 50 == 0) {
            current_game.moveDown();
        }

        if (current_game.fast_mode){
            current_game.moveDown();
        }

        if (current_game.grid.isGameOver()){
            running=false;
        }

        

        interface.inter_update(current_game, blocktextures);
        
        //std::cout << "f" << std::endl;
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