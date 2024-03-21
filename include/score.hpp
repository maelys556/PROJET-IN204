#pragma once
#include <vector>

class Score {
    public:
        std::vector<std::pair<int, std::string>> sc_lasts;
        std::vector<std::pair<int, std::string>> sc_bests;
        std::string sc_user_name;

    public:
        Score();
        void loadBestScores();
        /*void updateLastScores();
        
        void saveScore();*/
};