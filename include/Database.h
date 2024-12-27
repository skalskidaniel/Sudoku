//
// Created by Wiktor on 27/12/2024.
//

#ifndef DATABASE_H
#define DATABASE_H
#include <vector>
#include <unordered_map>

class database {
public:
    std::unordered_map<int, std::pair<std::string, std::string>> boards;
    int last_id;
    int bestScore;
    database();
    void load_data();
    void add_board(std::string board, std::string solution);
};



#endif //DATABASE_H
