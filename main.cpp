#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL.h>
//sudo apt-get install libsdl2-ttf-dev

#include <iostream>

#include "include/interface.hpp"
#include "include/grid.hpp"
#include "include/constants.hpp"
#include "include/game.hpp"
#include "include/tetromino.hpp"
#include "include/score.hpp"

int main(int argc, char* argv[]){

    
    TTF_Init();

    // reel code
    int tick = 0;
    //std::cout<< "X ";
    Interface interface;
    //std::cout<< "X ";
    interface.inter_init();

    //std::cout<< "X ";
    Game current_game(GRID_SIZE_X, GRID_SIZE_Y);
    //std::cout<< "X ";
    current_game.getNewBlock();
    //std::cout<< "X ";
    
    Score score;
    

// loading all textures
    SDL_Texture* blocktextures[NUM_BLOCK_SPRITES*NUM_LEVELS*NUM_POWERS + 1];
    SDL_Texture* scoretextures;
    SDL_Rect scoreRenderRect;
    //std::cout<< "X ";
    interface.texture_load_blocks(blocktextures);
    //interface.load_score(scoretextures,scoreRenderRect,score);
    //std::cout<< "X ";

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
        //std::cout<< "X ";
        if (tick % 25 == 0) {
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
        //std::cout<< "X ";
        if (tick % 10 == 0) {
            if (move_rotate == 1) {
                current_game.rotate();
                move_rotate = false;
            }
        //std::cout<< "X ";
        }
        if ((tick + 25) % 50 == 0) {
            current_game.moveDown();
        }
        //std::cout<< "X ";
        if (current_game.fast_mode){
            current_game.moveDown();
        }

        //std::cout<< "X ";
        std::vector<int> comp_rows = current_game.grid.completedRows();
        if (comp_rows.size()!=0){
            
            //int offset = 0;
            current_game.grid.updateScore(comp_rows, score);
            //interface.load_score(scoretextures,scoreRenderRect,score);
            for (int i=0; i<comp_rows.size(); i++){
                current_game.grid.deleteRow(comp_rows[i]);
                //offset+=1;
            }
        }
        //std::cout<< "X ";
        if (current_game.grid.isGameOver()){

            running=false;
        }

        //std::cout<< "X ";

        interface.inter_update(current_game, score, blocktextures, scoretextures, scoreRenderRect);
        //std::cout<< std::endl;
        //std::cout << "f" << std::endl;
    }
};
