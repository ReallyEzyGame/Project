#include "board_tile.h"
#include "player.h"
#include <SFML/Graphics.hpp>
#include <iostream>

#define POKEMON_NUMBER 12
// Row and Column has been increase by 2 including the dummy rows and columns for connection
#define ROW 11
#define COLUMN 14

#define Alata_font "./Asserts/Fonts/Alata-Regular.ttf"

#define Pikachu "./Asserts/Images/Pokemon1.png"
#define Balbasaur "./Asserts/Images/Pokemon2.png"
#define Charizard "./Asserts/Images/Pokemon3.png"
#define Wartortle "./Asserts/Images/Pokemon4.png"
#define Mewtwo "./Asserts/Images/Pokemon5.png"
#define Mew "./Asserts/Images/Pokemon6.png"
#define Tyranitar "./Asserts/Images/Pokemon7.png"
#define Lugia "./Asserts/Images/Pokemon8.png"
#define Ho_oh "./Asserts/Images/Pokemon9.png"
#define Sceptile "./Asserts/Images/Pokemon10.png"
#define Arceus "./Asserts/Images/Pokemon11.png"
#define Butterfree "./Asserts/Images/Pokemon12.png"

#define Line_Horizion "./Asserts/Images/Line_Erase_Horizion.png"
#define Line_Vertical "./Asserts/Images/Line_Erase_Vertical.png"

using namespace sf;

int main()
{

    Clock drawPathClock;
    vector<pair<int, int>> currentPath;
    const Color theme = Color(160, 224, 197);

    Board *board = new Board(ROW, COLUMN, POKEMON_NUMBER);
    board->CreateNewBoard();
    for (vector<Tile *> tiles : board->board)
    {
        for (Tile *tile : tiles)
            cout << tile->type << "   ";
        cout << endl;
    }
    std::cout << "Creating window..." << std::endl;
    RenderWindow window(VideoMode(1200, 800), "Pikachu Connect Game");
    // Get the Font Style
    Font font;
    font.loadFromFile(Alata_font);

    // Text
    Text textScore("Score: 0", font, 24);
    textScore.setPosition(20, 520);
    textScore.setFillColor(Color::Red.Blue);
    // Button
    // Reset Game Button
    RectangleShape btnReset(Vector2f(120, 30));
    btnReset.setPosition(500, 520);
    btnReset.setFillColor(Color::Blue);

    // Reset Game Text
    Text txtReset("Reset", font, 20);
    txtReset.setPosition(515, 525);
    txtReset.setFillColor(Color(232, 241, 244));
    // Highlight Connection
    // Trong main hoặc phần render
    VertexArray line(sf::LinesStrip);

    // Texture Tiles
    const int NumPokemon = POKEMON_NUMBER;
    vector<Texture> textures(NumPokemon);
    textures[0].loadFromFile(Pikachu);
    textures[1].loadFromFile(Balbasaur);
    textures[2].loadFromFile(Charizard);
    textures[3].loadFromFile(Wartortle);
    textures[4].loadFromFile(Mewtwo);
    textures[5].loadFromFile(Mew);
    textures[6].loadFromFile(Tyranitar);
    textures[7].loadFromFile(Lugia);
    textures[8].loadFromFile(Ho_oh);
    textures[9].loadFromFile(Sceptile);
    textures[10].loadFromFile(Arceus);
    textures[11].loadFromFile(Butterfree);

    vector<Texture> lines(2);
    lines[0].loadFromFile(Line_Horizion);
    lines[1].loadFromFile(Line_Vertical);

    // Grid Contains the Tiles
    RectangleShape Grid_Boxes[ROW][COLUMN];
    Sprite Grid_Sprite[ROW][COLUMN];
    //  Color the Border and the Grid
    for (int r = 0; r < ROW; ++r)
    {
        for (int c = 0; c < COLUMN; ++c)
        {
            // Get the Outline
            Grid_Boxes[r][c].setSize(Vector2f(40, 40));
            Grid_Boxes[r][c].setPosition(50 * c + 50, 50 * r + 30);
            Grid_Boxes[r][c].setFillColor(Color::Transparent);
            Grid_Boxes[r][c].setOutlineThickness(2);
            Grid_Boxes[r][c].setOutlineColor(Color::Transparent);
        }
    }
    for (int r = 1; r < ROW - 1; ++r)
    {
        for (int c = 1; c < COLUMN - 1; ++c)
        {
            int idx = board->board[r][c]->type;
            // Get the Texture of the Pokemon
            Grid_Sprite[r][c].setTexture(textures[idx]);
            Grid_Sprite[r][c].setScale(50.f / textures[idx].getSize().x, 50.f / textures[idx].getSize().y);
            Grid_Sprite[r][c].setPosition(50 * c + 50, 50 * r + 30);
            // Get the Outline
            Grid_Boxes[r][c].setSize(Vector2f(50, 50));
            Grid_Boxes[r][c].setPosition(50 * c + 50, 50 * r + 30);
            Grid_Boxes[r][c].setFillColor(Color(255, 211, 238));
            Grid_Boxes[r][c].setOutlineThickness(2);
            Grid_Boxes[r][c].setOutlineColor(Color(136, 44, 83));
        }
    }
    std::pair<int, int> selectedCell = {-1, -1};
    // The Main Loop
    while (window.isOpen())
    {
        // Events Occurs while playing
        Event event;
        while (window.pollEvent(event))
        {
            // End the Program
            if (event.type == Event::Closed)
                window.close();
            // Erase a pair
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                Vector2i mousePos = Mouse::getPosition(window);
                if (!board->HasAvaibleMove())
                    board->Shuffle();

                for (int r = 0; r < ROW; ++r)
                {
                    for (int c = 0; c < COLUMN; ++c)
                    {
                        if (Grid_Boxes[r][c].getGlobalBounds().contains((Vector2f)mousePos) && board->board[r][c]->visible)
                        {

                            // Choose the first Tile
                            if (selectedCell.first == -1)
                            {
                                selectedCell = {r, c};
                                Grid_Boxes[r][c].setOutlineColor(Color(129, 198, 242));
                                Grid_Boxes[r][c].setFillColor(Color(219, 63, 128));
                            }
                            // Choose the Second tile
                            else
                            {
                                vector<pair<int, int>> path;
                                int r1 = selectedCell.first, c1 = selectedCell.second;
                                // Match the Pair
                                if (board->canConnect(path, r1, c1, r, c) || board->canConnect(r, c, r1, c1))
                                {
                                    currentPath = path;
                                    drawPathClock.restart();

                                    //  Erase the Matched pair
                                    Grid_Sprite[r1][c1].setColor(Color::Transparent);
                                    Grid_Sprite[r][c].setColor(Color::Transparent);

                                    Grid_Boxes[r1][c1].setOutlineColor(theme);
                                    Grid_Boxes[r1][c1].setFillColor(theme);
                                    Grid_Boxes[r][c].setOutlineColor(theme);
                                    Grid_Boxes[r][c].setFillColor(theme);

                                    board->RemoveTile(r1, c1, r, c);
                                    if (board->remain == 0)
                                    {
                                        window.close();
                                        return 0;
                                    }
                                }
                                // MisMatch ==> Reset
                                else
                                {
                                    Grid_Boxes[r1][c1].setFillColor(Color(255, 211, 238));
                                    Grid_Boxes[r1][c1].setOutlineColor(Color(136, 44, 83));
                                    Grid_Boxes[r][c].setFillColor(Color(255, 211, 238));
                                    Grid_Boxes[r][c].setOutlineColor(Color(136, 44, 83));
                                }
                                selectedCell = {-1, -1};
                            }
                        }
                    }
                }
            }
        }

        window.clear(theme);
        window.draw(textScore);
        window.draw(btnReset);
        window.draw(txtReset);

        if (drawPathClock.getElapsedTime().asSeconds() < 0.5f)
        {
            sf::VertexArray line(sf::LinesStrip);
            for (auto &p : currentPath)
            {
                float x = p.second * 50 + 75;
                float y = p.first * 50 + 55;
                line.append(sf::Vertex(sf::Vector2f(x, y), sf::Color::Red));
            }
            window.draw(line);
        }

        for (int r = 0; r < ROW; ++r)
        {
            for (int c = 0; c < COLUMN; ++c)
            {
                if (board->board[r][c]->visible)
                {
                    window.draw(Grid_Boxes[r][c]);
                    window.draw(Grid_Sprite[r][c]);
                }
            }
        }

        window.display();
    }
    std::cout << "Exited!" << std::endl;
    return 0;
}