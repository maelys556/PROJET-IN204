#include <SDL2/SDL.h>
#include <iostream>
#include "game.cpp"
//#include "grid.cpp"
//#include "tetromino.cpp"

int main() {
    /*
    std::cout << "current_id:" << std::endl;
    Grid grid(10, 20);
    grid.Print_Grid();
    Tetromino aBlock = Tetromino(0, 0);
    std::cout << "current_id:" << std::endl;
    std::cout << "RowOffset de aBlock:" << aBlock.RowOffset << std::endl;
    std::cout << "ColumnOffset de aBlock:" << aBlock.ColumnOffset << std::endl;
    aBlock.printTetromino();
    TBlock anOtherBlock = TBlock(0, 0);
    anOtherBlock.printTetromino();
    std::cout << "RowOffset de anotherBlock:" << anOtherBlock.RowOffset << std::endl;
    std::cout << "ColumnOffset de anotherBlock:" << anOtherBlock.ColumnOffset << std::endl;
    anOtherBlock.rotate();
    anOtherBlock.printTetromino();
    */

    Game game(0);
    
    game.currentBlock.printTetromino();
    game.currentBlock.rotate();
    game.currentBlock.printTetromino();

    game.currentBlock = game.getNewBlock(4);

    game.currentBlock.printTetromino();
    game.currentBlock.rotate();
    game.currentBlock.printTetromino();
    game.moveDown();
    game.moveDown();
    game.moveDown();
    game.moveDown();
    game.moveDown();
    game.lockBlock();
    game.moveDown();
    game.moveDown();
    game.moveDown();
    game.moveDown();
    game.moveDown();
    game.grid.Print_Grid();
    /*for (int i=0; i<10; i++) {
        game.moveDown();
        std::cout << game.currentBlock.id << "row offset:" << game.currentBlock.RowOffset << std::endl;
        std::cout << "column offset:" << game.currentBlock.ColumnOffset << std::endl;
        game.grid.Print_Grid();
    }
    game.lockBlock();
    game.currentBlock = game.getNewBlock(5);
    for (int i=0; i<10; i++) {
        game.moveDown();
        std::cout << "row offset:" << game.currentBlock.RowOffset << std::endl;
        std::cout << "column offset:" << game.currentBlock.ColumnOffset << std::endl;
    }*/

    
    return 0;
}

/*
const int width = 10; // Largeur de l'image
const int height = 20; // Hauteur de l'image

// Tableau d'entiers représentant les pixels de l'image
int tableauPixels[LARGEUR_IMAGE * HAUTEUR_IMAGE];

 {
    for (int i=0; i<LARGEUR_IMAGE; i++) {
        for (int j=0; j<HAUTEUR_IMAGE; j++) {
            tableauPixels[i,j] = 5;
        }
    }

    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Erreur lors de l'initialisation de SDL : " << SDL_GetError() << std::endl;
        return 1;
    }

    // Création de la fenêtre
    SDL_Window* fenetre = SDL_CreateWindow("Affichage d'une image", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (fenetre == nullptr) {
        std::cerr << "Erreur lors de la création de la fenêtre : " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Création d'une surface SDL à partir du tableau de pixels
    SDL_Surface* surfaceImage = SDL_CreateRGBSurfaceFrom((void*)tableauPixels, LARGEUR_IMAGE, HAUTEUR_IMAGE, 32, LARGEUR_IMAGE * 4, 0xFF0000, 0x00FF00, 0x0000FF, 0);

    // Vérification de la création de la surface
    if (surfaceImage == nullptr) {
        std::cerr << "Erreur lors de la création de la surface SDL : " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(fenetre);
        SDL_Quit();
        return 1;
    }

    // Récupération du rendu
    SDL_Renderer* rendu = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (rendu == nullptr) {
        std::cerr << "Erreur lors de la création du rendu SDL : " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surfaceImage);
        SDL_DestroyWindow(fenetre);
        SDL_Quit();
        return 1;
    }

    // Nettoyage de la fenêtre
    SDL_SetRenderDrawColor(rendu, 255, 0, 0, 255);
    SDL_RenderClear(rendu);

    // Blitter l'image sur la fenêtre
    SDL_Rect destination = {100, 100, LARGEUR_IMAGE, HAUTEUR_IMAGE}; // Position de l'image
    SDL_BlitSurface(surfaceImage, NULL, SDL_GetWindowSurface(fenetre), &destination);

    // Mettre à jour l'affichage
    SDL_UpdateWindowSurface(fenetre);

    // Attendre quelques secondes avant de fermer
    SDL_Delay(5000);

    // Libération des ressources
    SDL_FreeSurface(surfaceImage);
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();

    return 0;
}
*/