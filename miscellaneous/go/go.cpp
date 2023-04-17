// This program is a part of simple implementation of Monte Carlo Tree Search (MCTS) for Go AI.
// It takes a state file of current board and previoud board states as input, also takes a file of previous moves.
// It produces an output file of next move.

#include <math.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <memory>

using std::vector;

#define BOARD_SIZE      5
#define TERMINAL_ROUND  24
#define ITERS           2000

bool is_temp_file_exist()
{
    std::ifstream infile("temp.txt");
    return infile.good();
}

template <typename T>
void clear_matrix(vector<vector<T>>& matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            matrix[i][j] = 0;
        }
    }
}

inline double nornalize_score0(int score) {
    return (score + TERMINAL_ROUND / 2) / (double)TERMINAL_ROUND;
}

inline double nornalize_score(int score) {
    if (score < -5) {
        return 0.0;
    }
    return (score + 5) / (double)16.0;
}

struct GoBoard {
    int self;
    int round;
    std::vector<std::vector<int>> board;
    std::pair<int, int> prev1;
    std::pair<int, int> prev2;

    GoBoard(int s = 1);
    GoBoard(const GoBoard& other);
    GoBoard(int s, std::vector<std::vector<int>>& b);

    void print_board();
    int count();
    std::string serialize();
    int get_score();
    bool count_liberty(vector<vector<bool>>& visited, int x, int y, int self);
    bool count_liberty(int x, int y, int self);
    bool is_move_valid(int x, int y, int self);
    bool has_neighbor(int x, int y);

    std::vector<std::pair<int, int>> get_valid_moves();
    void make_move(int x, int y);
    void removed_captured(int x, int y, int self);

    void set_prev(int x, int y, int pself);
    void set_prev(GoBoard& prev);

    // simulate game until terminal state with random moves
    void simulate();
};

struct MCTS_Node : public std::enable_shared_from_this<MCTS_Node>
{
    int count;
    double score;
    std::shared_ptr<MCTS_Node> parent;
    std::vector<std::shared_ptr<MCTS_Node>> children;
    GoBoard board;

    MCTS_Node();
    MCTS_Node(GoBoard& b);
    MCTS_Node(std::shared_ptr<MCTS_Node> p);
    MCTS_Node(std::shared_ptr<MCTS_Node> p, GoBoard& b);

    double ucb(int n_global);

    int rollout();
    void expand();
    void backpropagate(double score);
};

struct MCTS_Tree
{
    std::shared_ptr<MCTS_Node> head;
    std::unordered_map<std::string, std::shared_ptr<MCTS_Node>> node_map;

    MCTS_Tree();
    MCTS_Tree(GoBoard& rootBoard);

    std::shared_ptr<MCTS_Node> select();
    void inspect_tree();
};

GoBoard::GoBoard(int s)
    : self(s), round(1), board(vector<vector<int>>(BOARD_SIZE, vector<int>(BOARD_SIZE, 0))), prev1(std::make_pair(-1, -1)), prev2(std::make_pair(-1, -1)) {}

GoBoard::GoBoard(const GoBoard& other)
    : self(other.self), round(other.round), board(other.board), prev1(other.prev1), prev2(other.prev2) {}

GoBoard::GoBoard(int s, std::vector<std::vector<int>>& b)
    : self(s), round(1), board(b), prev1(std::make_pair(-1, -1)), prev2(std::make_pair(-1, -1)) {}

MCTS_Node::MCTS_Node()
    : count(0), score(0), parent(nullptr) {}

MCTS_Node::MCTS_Node(GoBoard& b)
    : count(0), score(0), parent(nullptr), board(b) {}

MCTS_Node::MCTS_Node(std::shared_ptr<MCTS_Node> p)
    : count(0), score(0), parent(p) {}

MCTS_Node::MCTS_Node(std::shared_ptr<MCTS_Node> p, GoBoard& b)
    : count(0), score(0), parent(p), board(b) {}

MCTS_Tree::MCTS_Tree()
    : head(nullptr) {}

MCTS_Tree::MCTS_Tree(GoBoard& rootBoard)
    : head(std::make_shared<MCTS_Node>(rootBoard)) {}

double MCTS_Node::ucb(int n_global) {
    return (score / (double)count) + sqrt(2.0) * sqrt(log(n_global) / (double)count);
}

int MCTS_Node::rollout() {
    GoBoard sim_board(board);
    sim_board.simulate();
    return sim_board.get_score();
}

void MCTS_Node::expand() {
    if (board.round > TERMINAL_ROUND) {
        return;
    }
    auto valid_moves = board.get_valid_moves();
    for (auto& move : valid_moves) {
        GoBoard next_board(board);
        next_board.make_move(move.first, move.second);
        children.push_back(std::make_shared<MCTS_Node>(shared_from_this(), next_board));
    }
}

void MCTS_Node::backpropagate(double score) {
    auto ptr = shared_from_this();
    while (ptr) {
        ptr->count++;
        ptr->score += score;
        ptr = ptr->parent;
    }
}

// TODO: test
std::shared_ptr<MCTS_Node> MCTS_Tree::select() {
    auto ptr = head;
    while (ptr && ptr->children.size() > 0) {
        double max_ucb = -10000;
        std::shared_ptr<MCTS_Node> max_ptr = nullptr;
        for (auto& child : ptr->children) {
            if (child->count == 0) {
                max_ptr = child;
                break;
            }
            double ucb = child->ucb(head->count);
            if (ucb > max_ucb) {
                max_ucb = ucb;
                max_ptr = child;
            }
        }
        ptr = max_ptr;
    }
    if (ptr->count > 0) {
        ptr->expand();
        if (ptr->children.size() > 0) {
            return ptr->children[0];
        }
    }
    return ptr;
}

void MCTS_Tree::inspect_tree() {
    auto ptr = head;
    while (ptr && ptr->children.size() > 0) {
        std::cout << ptr->score << " " << ptr->count << " " << (ptr->score / ptr->count) << std::endl;
        ptr->board.print_board();

        double max_ucb = -10000;
        std::shared_ptr<MCTS_Node> max_ptr = nullptr;
        for (auto& child : ptr->children) {
            if (child->count == 0) {
                max_ptr = child;
            }
            double ucb = child->ucb(head->count);
            if (ucb > max_ucb) {
                max_ucb = ucb;
                max_ptr = child;
            }
        }
        ptr = max_ptr;
    }
}

void GoBoard::print_board() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            std::cout << board[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int GoBoard::count() {
    int count = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] != 0) {
                count++;
            }
        }
    }
    return count;
}

std::string GoBoard::serialize() {
    std::string str(25, 0);
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            str[BOARD_SIZE * i + j] = board[i][j] + '0';
        }
        std::cout << std::endl;
    }
    return str;
}

int GoBoard::get_score() {
    int score = 0;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] == 1) {
                score++;
            } else if (board[i][j] == 2) {
                score--;
            }
        }
    }
    return score;
}

bool GoBoard::count_liberty(int x, int y, int self) {
    vector<vector<bool>> visited(BOARD_SIZE, vector<bool>(BOARD_SIZE, false));
    return count_liberty(visited, x, y, self);
}

bool GoBoard::count_liberty(vector<vector<bool>>& visited, int x, int y, int self) {
    if (x < 0 || y < 0 || x >= BOARD_SIZE || y >= BOARD_SIZE || visited[x][y] == true) {
        return false;
    }
    if (board[x][y] == 0) {
        return true;
    } else if (board[x][y] != self) {
        return false;
    }
    visited[x][y] = true;
    return count_liberty(visited, x + 1, y, self) || count_liberty(visited, x - 1, y, self) || count_liberty(visited, x, y + 1, self) || count_liberty(visited, x, y - 1, self);
}

bool GoBoard::is_move_valid(int x, int y, int self) {
    if (x < 0 || y < 0 || x >= BOARD_SIZE || y >= BOARD_SIZE || board[x][y] != 0) {
        return false;
    }
    if ((self == 1 && prev1.first == x && prev1.second == y) || (self == 2 && prev2.first == x && prev2.second == y)) {
        return false;
    }
    vector<vector<bool>> visited(BOARD_SIZE, vector<bool>(BOARD_SIZE, false));
    board[x][y] = self;
    bool has_liberty = count_liberty(visited, x, y, self);
    int opp = 2;
    if (self == 2) {
        opp = 1;
    }
    clear_matrix(visited);

    auto prev = (self == 1) ? prev2 : prev1;
    bool ko = (x - 1 >= 0 && board[x - 1][y] == opp && !(prev.first == x - 1 && prev.second == y) && !count_liberty(x - 1, y, opp)) ||
        (x + 1 < BOARD_SIZE && board[x + 1][y] == opp && !(prev.first == x + 1 && prev.second == y) && !count_liberty(x + 1, y, opp)) ||
        (y - 1 >= 0 && board[x][y - 1] == opp && !(prev.first == x && prev.second == y - 1) && !count_liberty(x, y - 1, opp)) ||
        (y + 1 < BOARD_SIZE && board[x][y + 1] == opp && !(prev.first == x && prev.second == y + 1) && !count_liberty(x, y + 1, opp));
    /*
    bool ko = (x - 1 >= 0 && board[x - 1][y] == opp && !count_liberty(x - 1, y, opp)) ||
        (x + 1 < BOARD_SIZE && board[x + 1][y] == opp && !count_liberty(x + 1, y, opp)) ||
        (y - 1 >= 0 && board[x][y - 1] == opp && !count_liberty(x, y - 1, opp)) ||
        (y + 1 < BOARD_SIZE && board[x][y + 1] == opp && !count_liberty(x, y + 1, opp));
    */
    board[x][y] = 0;
    return has_liberty || ko;
}

bool GoBoard::has_neighbor(int x, int y) {
    if (x - 1 >= 0 && board[x - 1][y] != 0) {
        return true;
    }
    if (x + 1 < BOARD_SIZE && board[x + 1][y] != 0) {
        return true;
    }
    if (y - 1 >= 0 && board[x][y - 1] != 0) {
        return true;
    }
    if (y + 1 < BOARD_SIZE && board[x][y + 1] != 0) {
        return true;
    }
    if (x - 1 >= 0 && y - 1 >= 0 && board[x - 1][y - 1] != 0) {
        return true;
    }
    if (x - 1 >= 0 && y + 1 < BOARD_SIZE && board[x - 1][y + 1] != 0) {
        return true;
    }
    if (x + 1 < BOARD_SIZE && y - 1 >= 0 && board[x + 1][y - 1] != 0) {
        return true;
    }
    if (x + 1 < BOARD_SIZE && y + 1 < BOARD_SIZE && board[x + 1][y + 1] != 0) {
        return true;
    }
    return false;
}

std::vector<std::pair<int, int>> GoBoard::get_valid_moves() {
    std::vector<std::pair<int, int>> result;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (/*has_neighbor(i, j) &&*/ is_move_valid(i, j, self)) {
                result.push_back(std::make_pair(i, j));
            }
        }
    }
    return result;
}

// Need to assume that move on x, y in valid!
// TODO: keep track of prev move of each player
void GoBoard::make_move(int x, int y) {
    if (x < 0 || y < 0 || x >= BOARD_SIZE || y >= BOARD_SIZE || board[x][y] != 0) {
        return;
    }
    board[x][y] = self;
    int opp = 2;
    if (self == 2) {
        opp = 1;
    }
    vector<vector<bool>> visited(BOARD_SIZE, vector<bool>(BOARD_SIZE, false));
    if (x - 1 >= 0 && board[x - 1][y] == opp && !count_liberty(visited, x - 1, y, opp)) {
        removed_captured(x - 1, y, opp);
    }
    clear_matrix(visited);
    if (x + 1 < BOARD_SIZE && board[x + 1][y] == opp && !count_liberty(visited, x + 1, y, opp)) {
        removed_captured(x + 1, y, opp);
    }
    clear_matrix(visited);
    if (y - 1 >= 0 && board[x][y - 1] == opp && !count_liberty(visited, x, y - 1, opp)) {
        removed_captured(x, y - 1, opp);
    }
    clear_matrix(visited);
    if (y + 1 < BOARD_SIZE && board[x][y + 1] == opp && !count_liberty(visited, x, y + 1, opp)) {
        removed_captured(x, y + 1, opp);
    }
    if (self == 1) {
        prev1.first = x;
        prev1.second = y;
    } else {
        prev2.first = x;
        prev2.second = y;
    }
    self = opp;
    round++;
}

void GoBoard::removed_captured(int x, int y, int self) {
    if (x < 0 || y < 0 || x >= BOARD_SIZE || y >= BOARD_SIZE || board[x][y] != self) {
        return;
    }
    board[x][y] = 0;
    removed_captured(x - 1, y, self);
    removed_captured(x + 1, y, self);
    removed_captured(x, y - 1, self);
    removed_captured(x, y + 1, self);
}

void GoBoard::set_prev(int x, int y, int pself) {
    if (pself == 1) {
        prev1.first = x;
        prev1.second = y;
    }
    else {
        prev2.first = x;
        prev2.second = y;
    }
}

void GoBoard::set_prev(GoBoard& prev) {
    int x = -1, y = -1;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == prev.self && prev.board[i][j] == 0) {
                set_prev(i, j, prev.self);
                return;
            }
        }
    }
}

void GoBoard::simulate() {
    for (; round <= TERMINAL_ROUND;) {
        auto valid_moves = get_valid_moves();
        if (valid_moves.size() == 0) {
            return;
        }
        int rand_num = rand() % valid_moves.size();
        make_move(valid_moves[rand_num].first, valid_moves[rand_num].second);
        //std::cout << round << " " << self << std::endl;
        //print_board();
    }
}

void show_valid_moves(GoBoard& board, int self) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            std::cout << (board.has_neighbor(i, j) && board.is_move_valid(i, j, self)) << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

GoBoard simulate(GoBoard& current) {
    GoBoard board = current;
    return board;
}

void read_temp_file(int& round, int& prev_x, int& prev_y) {
    if (!is_temp_file_exist()) {
        return;
    }
    std::ifstream infile("temp.txt");
    infile >> round >> prev_x >> prev_y;
}

void read_input_file(int& turn, GoBoard& prev_state, GoBoard& curr_state) {
    std::ifstream file("input.txt");
    std::string line;
    std::getline(file, line);
    turn = line[0] - '0';
    for (int i = 0; i < 5; i++) {
        std::getline(file, line);
        for (int j = 0; j < 5; j++) {
            prev_state.board[i][j] = line[j] - '0';
        }
    }
    for (int i = 0; i < 5; i++) {
        std::getline(file, line);
        for (int j = 0; j < 5; j++) {
            curr_state.board[i][j] = line[j] - '0';
        }
    }
}

void write_temp_file(int round, int prev_x, int prev_y) {
    std::ofstream ofile;
    ofile.open("temp.txt");
    ofile << round << '\n';
    ofile << prev_x << '\n';
    ofile << prev_y << '\n';
    ofile.close();
}

void write_output_file(const char* str) {
    std::ofstream ofile;
    ofile.open("output.txt");
    ofile << str << '\n';
    ofile.close();
}

void solve_dummy(GoBoard& prev_state, GoBoard& curr_state) {
    if (curr_state.round == 4 || curr_state.round == 3) {
        write_output_file("PASS");
        write_temp_file(curr_state.round + 2, -1, -1);
        return;
    }
    char out_str[] = "2,2";
    if (curr_state.is_move_valid(2, 2, curr_state.self)) {
        write_output_file(out_str);
        write_temp_file(curr_state.round + 2, -1, -1);
        return;
    }
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (curr_state.has_neighbor(i, j) && curr_state.is_move_valid(i, j, curr_state.self)) {
                out_str[0] = i + '0';
                out_str[2] = j + '0';
                write_output_file(out_str);
                write_temp_file(curr_state.round + 2, -1, -1);
                return;
            }
        }
    }
    write_output_file("PASS");
    write_temp_file(curr_state.round + 2, -1, -1);
}

void solve_MCTS(GoBoard& prev_state, GoBoard& curr_state) {
    if ((curr_state.round == 1 || curr_state.round == 2) && curr_state.is_move_valid(2, 2, curr_state.self)) {
        write_output_file("2,2");
        write_temp_file(curr_state.round + 2, 2, 2);
        return;
    }
    if (curr_state.get_valid_moves().size() == 0) {
        write_output_file("PASS");
        write_temp_file(curr_state.round + 2, -1, -1);
        return;
    }
    MCTS_Tree mcts(curr_state);
    mcts.head->expand();
    for (int i = 0; i < ITERS; i++) {
        auto node = mcts.select();
        //double sim_score = node->rollout() - 2.5;
        //std::cout << sim_score << std::endl;
        //int score = 0;
        double score = node->rollout();
        if (curr_state.self == 1) {
            //score = sim_score >= 0 ? 1 : 0;
            //score -= 2.5;
        } else {
            //score = sim_score <= 0 ? 0 : 1;
            score *= -1;
            //score += 2.5;
        }
        node->backpropagate(nornalize_score(score));
    }
    /*
    for (auto& child : mcts.head->children) {
        std::cout << child->score << " " << child->count << " " << (child->score / child->count) << std::endl;
        child->board.print_board();
    }
    std::cout << "-----------inspecting tree------------" << std::endl;
    mcts.inspect_tree();
    */
    std::shared_ptr<MCTS_Node> best_child = nullptr;
    char out_str[] = "2,2";
    double score = -10000;
    for (auto& child : mcts.head->children) {
        if ((child->score / child->count) > score) {
            score = child->score / child->count;
            best_child = child;
        }
    }
    if (best_child) {
        auto move = best_child->board.prev1;
        if (curr_state.self == 2) {
            move = best_child->board.prev2;
        }
        out_str[0] = move.first + '0';
        out_str[2] = move.second + '0';
        write_output_file(out_str);
        write_temp_file(curr_state.round + 2, move.first, move.second);
    } else {
        write_output_file("PASS");
        write_temp_file(curr_state.round + 2, -1, -1);
    }
}

int main() {
    srand(time(NULL));

    int turn = 0;
    GoBoard prev_state;
    GoBoard curr_state;

    read_input_file(turn, prev_state, curr_state);
    if (turn == 1) {
        prev_state.self = 2;
        curr_state.self = 1;
    }
    else {
        prev_state.self = 1;
        curr_state.self = 2;
    }
    int count = curr_state.count();
    if (count <= 1) {
        if (curr_state.self == 1 || curr_state.board[2][2] == 0) {
            write_output_file("2,2");
            write_temp_file(curr_state.self + 2, 2, 2);
        } else {
            write_output_file("2,3");
            write_temp_file(curr_state.self + 2, 2, 3);
        }
        return 0;
    }

    int round = curr_state.self, prev_x = -1, prev_y = -1;
    read_temp_file(round, prev_x, prev_y);

    curr_state.round = round;
    curr_state.set_prev(prev_x, prev_y, curr_state.self);
    curr_state.set_prev(prev_state);
    
    //solve_dummy(prev_state, curr_state);
    solve_MCTS(prev_state, curr_state);

    /*
    std::cout << curr_state.self << std::endl;
    vector<vector<bool>> visited(BOARD_SIZE, vector<bool>(BOARD_SIZE, false));
    curr_state.print_board();
    show_valid_moves(curr_state, 2);
    auto a = curr_state.count_liberty(visited, 4, 2, 1);
    clear_matrix(visited);
    auto b = curr_state.count_liberty(visited, 4, 1, 2);
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    */

    /*
    std::map<int, int> sheet;
    GoBoard board;
    board.self = 1;
    board.round = 1;
    for (int i = 0; i < 10000; i++) {
        GoBoard cpy(board);
        cpy.simulate();
        sheet[cpy.get_score()]++;
        //cpy.print_board();
        //std::cout << cpy.get_score() << std::endl;
    }
    for (auto s : sheet) {
        std::cout << s.first << " " << s.second << std::endl;
    }
    */
    return 0;
}