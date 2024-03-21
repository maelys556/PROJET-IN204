#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>


#include "../include/score.hpp"

#include "../include/constants.hpp"

Score::Score(){
    for (int i = 0; i < MAX_NUMBER_SCORE; ++i) {
        sc_lasts.push_back(std::make_pair(0, "..."));
    }
    loadBestScores();
    sc_user_name = "aaa";
    sc_current_score = 0;
}

void Score::updateLastScores() {
    sc_lasts.insert(sc_lasts.begin(), std::make_pair(sc_current_score, sc_user_name));

    if (sc_lasts.size() > MAX_NUMBER_SCORE) {
        sc_lasts.pop_back();
    }
}

void Score::saveScore() {
    std::string filename = SCORE_FILE_PATH;
    // Insert the new score
    sc_bests.emplace_back(sc_current_score, sc_user_name);
    
    // Sort the scores
    std::sort(sc_bests.begin(), sc_bests.end(), std::greater<std::pair<int, std::string>>());

    if (sc_bests.size() > MAX_NUMBER_SCORE) {
        sc_bests.resize(MAX_NUMBER_SCORE);
    }

    // Write the scores to the file
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& entry : sc_bests) {
            file << entry.first << " " << entry.second << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

void Score::loadBestScores() {
    std::ifstream file(SCORE_FILE_PATH);
    if (file.is_open()) {
        // Read best scores from the file and store them in sc_bests
        int score;
        std::string name;
        while (file >> score >> name) {
            sc_bests.push_back(std::make_pair(score, name));
        }
        file.close();
    }
}

void Score::add_current(int points){
    sc_current_score = sc_current_score + points;
}