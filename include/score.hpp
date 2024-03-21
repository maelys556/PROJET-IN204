#pragma once
#include <vector>

class Score {
    private:
        std::vector<std::pair<int, std::string>> sc_lasts;
        std::vector<std::pair<int, std::string>> sc_bests;
        std::string sc_user_name;
        int sc_current_score;

    public:
        Score();
        void updateLastScores();
        void loadBestScores();
        void saveScore();
        void add_current(int points);
};