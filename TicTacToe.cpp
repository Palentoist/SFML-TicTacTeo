#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>

const int WINDOW_SIZE = 600;
const int GRID_SIZE = 3;
const int CELL_SIZE = WINDOW_SIZE / GRID_SIZE;
const int LINE_THICKNESS = 5;

enum class Player { None, X, O };

class TicTacToe {
public:
    TicTacToe() {
        for (auto& row : board) {
            row.fill(Player::None);
        }
    }

    void draw(sf::RenderWindow& window) {
        window.clear(sf::Color::White);
        drawGrid(window);
        drawMarks(window);
        window.display();
    }

    void handleClick(int x, int y) {
        int row = y / CELL_SIZE;
        int col = x / CELL_SIZE;

        if (board[row][col] == Player::None) {
            board[row][col] = currentPlayer;
            if (checkWin(currentPlayer)) {
                std::cout << (currentPlayer == Player::X ? "X" : "O") << " wins!\n";
            }
            currentPlayer = (currentPlayer == Player::X) ? Player::O : Player::X;
        }
    }

private:
    std::array<std::array<Player, GRID_SIZE>, GRID_SIZE> board;
    Player currentPlayer = Player::X;

    void drawGrid(sf::RenderWindow& window) {
        sf::RectangleShape line(sf::Vector2f(WINDOW_SIZE, LINE_THICKNESS));
        line.setFillColor(sf::Color::Black);

        for (int i = 1; i < GRID_SIZE; ++i) {
            // Horizontal line
            line.setPosition(0, i * CELL_SIZE - LINE_THICKNESS / 2);
            window.draw(line);
            // Vertical line
            line.setSize(sf::Vector2f(LINE_THICKNESS, WINDOW_SIZE));
            line.setPosition(i * CELL_SIZE - LINE_THICKNESS / 2, 0);
            window.draw(line);
            line.setSize(sf::Vector2f(WINDOW_SIZE, LINE_THICKNESS));
        }
    }

    void drawMarks(sf::RenderWindow& window) {
        for (int row = 0; row < GRID_SIZE; ++row) {
            for (int col = 0; col < GRID_SIZE; ++col) {
                if (board[row][col] == Player::X) {
                    drawX(window, col * CELL_SIZE, row * CELL_SIZE);
                }
                else if (board[row][col] == Player::O) {
                    drawO(window, col * CELL_SIZE, row * CELL_SIZE);
                }
            }
        }
    }

    void drawX(sf::RenderWindow& window, int x, int y) {
        sf::RectangleShape line1(sf::Vector2f(CELL_SIZE, LINE_THICKNESS));
        line1.setFillColor(sf::Color::Black);
        line1.setPosition(x, y);
        line1.rotate(45);
        window.draw(line1);

        sf::RectangleShape line2(sf::Vector2f(CELL_SIZE, LINE_THICKNESS));
        line2.setFillColor(sf::Color::Black);
        line2.setPosition(x + CELL_SIZE, y);
        line2.rotate(135);
        window.draw(line2);
    }

    void drawO(sf::RenderWindow& window, int x, int y) {
        sf::CircleShape circle(CELL_SIZE / 2 - LINE_THICKNESS);
        circle.setFillColor(sf::Color::Transparent);
        circle.setOutlineThickness(LINE_THICKNESS);
        circle.setOutlineColor(sf::Color::Black);
        circle.setPosition(x + LINE_THICKNESS, y + LINE_THICKNESS);
        window.draw(circle);
    }

    bool checkWin(Player player) {
        // Check rows and columns
        for (int i = 0; i < GRID_SIZE; ++i) {
            if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
                (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
                return true;
            }
        }
        // Check diagonals
        if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
            (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
            return true;
        }
        return false;
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Tic Tac Toe");

    TicTacToe game;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    game.handleClick(event.mouseButton.x, event.mouseButton.y);
                }
            }
        }
        game.draw(window);
    }

    return 0;
}
