#include "board_tile.h"
#include <queue>
#include <algorithm>
struct Node
{
    int row, column, direction, turns;
    int pr, pc; // Parent row &  column
};

// Generate the Board at the Starting of the Game
void Board::CreateNewBoard()
{
    // Get the area of the board & number of tiles
    int total_area = (col_size - 2) * (row_size - 2);
    int total_pair = total_area / 2;
    // Get all the pair
    vector<int> tiles;
    for (int i = 0; i < total_pair; ++i)
    {
        // each tiles make a pair
        tiles.push_back(i % kinds);
        tiles.push_back(i % kinds);
    }
    // shuffle the pair
    Shuffle(tiles);

    // Put the tiles to the  Board
    // + 2 of empty rows/columns for Connection
    board = vector<vector<Tile *>>(row_size, vector<Tile *>(col_size, nullptr));
    int index = 0;
    for (int r = 1; r < row_size - 1; ++r)
    {
        for (int c = 1; c < col_size - 1; ++c)
        {
            board[r][c] = new Tile(tiles[index++], r, c);
            board[r][c]->visible = 1;
        }
    }
    // fill the Border with Dummy Tile
    for (int r = 0; r < row_size; ++r)
    {
        board[r][0] = new Tile(-1, r, 0);
        board[r][col_size - 1] = new Tile(-1, r, col_size - 1);
    }
    for (int c = 0; c < col_size; ++c)
    {
        board[0][c] = new Tile(-1, 0, c);
        board[row_size - 1][c] = new Tile(-1, row_size - 1, c);
    }
}

// Shuffle all the Tiles until these a move
void Board::Shuffle(vector<int> &list)
{
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> distrib(0, list.size() - 1);
    int index;
    for (int i = 0; i < list.size(); ++i)
    {
        index = distrib(generator);
        swap(list[i], list[index]);
    }
}

// Shuffle the Board when there is no Valid pair to Erase
void Board::Shuffle()
{
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> random_row(1, row_size - 2), random_col(1, col_size - 2);

    for (int r1 = 1; r1 < row_size - 1; ++r1)
    {
        for (int c1 = 1; c1 < col_size - 1; ++c1)
        {
            if (board[r1][c1]->visible)
            {
                int r2 = random_row(generator), c2 = random_col(generator);
                while (!board[r2][c2]->visible)
                {
                    r2 = random_row(generator);
                    c2 = random_col(generator);
                }
                swap(board[r1][c1]->type, board[r2][c2]->type);
            }
        }
    }
}

bool Board::InBoard(int r, int c)
{
    return (r >= 0 && c >= 0 && r < row_size && c < col_size);
}

bool Board::IsEmptyOrTarget(int row_from, int col_from, int row_des, int col_des)
{
    if (!InBoard(row_from, col_from))
        return false;
    return (board[row_from][col_from]->visible == 0 || (row_from == row_des && col_from == col_des));
}

bool Board::canConnect(std::vector<std::pair<int, int>>& path, int r1, int c1, int r2, int c2)
{
    // Checking pre condition
    if (board[r1][c1] == nullptr || board[r2][c2] == nullptr) return false;
    if (!board[r1][c1]->visible || !board[r2][c2]->visible) return false;
    if (board[r1][c1]->type != board[r2][c2]->type) return false;
    if (r1 == r2 && c1 == c2) return false;

    const int dr[4] = {-1, 1, 0, 0}; // Up, Down, Left, Right
    const int dc[4] = {0, 0, -1, 1};

    struct Node {
        int r, c, dir, turns;
        std::vector<std::pair<int, int>> path;
    };

    std::queue<Node> q;
    vector<vector<vector<bool>>> visited(row_size,vector<vector<bool>>(col_size,vector<bool>(4, 0)));

    // Get  the First 4 direction  from starting
    for (int dir = 0; dir < 4; ++dir) {
        int nr = r1 + dr[dir];
        int nc = c1 + dc[dir];
        if (nr >= 0 && nr < row_size && nc >= 0 && nc < col_size && !board[nr][nc]->visible) {
            visited[nr][nc][dir] = true;
            q.push({nr, nc, dir, 0, {{r1, c1}, {nr, nc}}});
        }
        else if  (nr == r2 && nc == c2) {
            path.push_back({r1,c1});
            path.push_back({r2,c2});
            return true;
        }
    }
    //  Travel through the Board
    while (!q.empty()) {
        Node cur = q.front(); q.pop();
        int r = cur.r, c = cur.c;

        // Đến đích
        if (r == r2 && c == c2) {
            path = cur.path;
            return true;
        }

        for (int dir = 0; dir < 4; ++dir) {
            int nr = r + dr[dir];
            int nc = c + dc[dir];
            int newTurns = cur.turns + (dir != cur.dir ? 1 : 0);

            if (newTurns > 2) continue;
            if (nr < 0 || nr >= row_size || nc < 0 || nc >= col_size) continue;
            if (visited[nr][nc][dir]) continue;
            if ((nr != r2 || nc != c2) && board[nr][nc]->visible) continue;

            visited[nr][nc][dir] = true;
            auto newPath = cur.path;
            newPath.push_back({nr, nc});
            q.push({nr, nc, dir, newTurns, newPath});
        }
    }

    return false;
}


bool Board::canConnect(int r1, int c1, int r2, int c2)
{
    // Checking pre condition
    if (board[r1][c1] == nullptr || board[r2][c2] == nullptr) return false;
    if (!board[r1][c1]->visible || !board[r2][c2]->visible) return false;
    if (board[r1][c1]->type != board[r2][c2]->type) return false;
    if (r1 == r2 && c1 == c2) return false;

    const int dr[4] = {-1, 1, 0, 0}; // Up, Down, Left, Right
    const int dc[4] = {0, 0, -1, 1};

    struct Node {
        int r, c, dir, turns;
    };

    std::queue<Node> q;
    vector<vector<vector<bool>>> visited(row_size,vector<vector<bool>>(col_size,vector<bool>(4, 0)));

    // Get  the First 4 direction  from starting
    for (int dir = 0; dir < 4; ++dir) {
        int nr = r1 + dr[dir];
        int nc = c1 + dc[dir];
        if (nr >= 0 && nr < row_size && nc >= 0 && nc < col_size && !board[nr][nc]->visible) {
            visited[nr][nc][dir] = true;
            q.push({nr, nc, dir, 0});
        }
        else if  (nr == r2 && nc == c2) {
            return true;
        }
    }
    //  Travel through the Board
    while (!q.empty()) {
        Node cur = q.front(); q.pop();
        int r = cur.r, c = cur.c;

        // Đến đích
        if (r == r2 && c == c2) {
            return true;
        }

        for (int dir = 0; dir < 4; ++dir) {
            int nr = r + dr[dir];
            int nc = c + dc[dir];
            int newTurns = cur.turns + (dir != cur.dir ? 1 : 0);

            if (newTurns > 2) continue;
            if (nr < 0 || nr >= row_size || nc < 0 || nc >= col_size) continue;
            if (visited[nr][nc][dir]) continue;
            if ((nr != r2 || nc != c2) && board[nr][nc]->visible) continue;

            visited[nr][nc][dir] = true;
            q.push({nr, nc, dir, newTurns});
        }
    }

    return false;
}
void Board::RemoveTile(int r1, int c1, int r2, int c2)
{
    // Romve a pair of tiles
    board[r1][c1]->visible = false;
    board[r2][c2]->visible = false;
    remain -= 2;
}

// Get all the Tiles with  the Same type that still visible
vector<pair<int, int>> Board::getSameType(const int type)
{
    vector<pair<int, int>> pairs;
    for (int r = 1; r < row_size - 1; ++r)
    {
        for (int c = 1; c < col_size - 1; ++c)
        {
            if (board[r][c]->visible && board[r][c]->type == type)
            {
                pairs.emplace_back(r, c);
            }
        }
    }
    return pairs;
}

bool Board::HasAvaibleMove()
{
    vector<vector<bool>> visited(row_size, vector<bool>(col_size, 0));

    for (int r = 1; r < row_size - 1; ++r)
    {
        for (int c = 1; c < col_size - 1; ++c)
        {
            // Check if it  is visited or has been ereased
            if (!board[r][c]->visible || visited[r][c])
                continue;
            // Get all tiles with same Type
            vector<pair<int, int>> pairs = getSameType(board[r][c]->type);
            // Check for a valid  move
            while (!pairs.empty())
            {
                int r1 = pairs.back().first, c1 = pairs.back().second;
                for (pair<int, int> tile : pairs)
                {
                    if (canConnect(r1, c1, tile.first, tile.second))
                        return true;
                }
                visited[r1][c1] = true; // Make Sure the tile won't be Visited Again
                pairs.pop_back();
            }
        }
    }
    return false;
}