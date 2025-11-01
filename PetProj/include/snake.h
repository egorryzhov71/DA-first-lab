#include <iostream> 
#include <vector>
#include <utility>


class Snake{
    private:
        std::vector<std::pair<int, int>> body;
        int direction;
        bool alive;
    public:
        Snake(int start_x, int start_y, int initial_length = 3);
        void move();
        void setDirection(int new_direction);
        void grow();

        bool checkSelfCollision() const ;
        bool isAtPosition(int x, int y) const;

        const std::vector<std::pair<int, int>>& getBody() const;
        std::pair<int, int> getHead() const;
        bool isALive() const;
        int getDirection() const;
};

class Food{
    private:
        std::pair<int, int> position;
        bool eaten;

    public:
        Food();

        void spawn(int max_x, int max_y);
        bool isEaten() const;
        void setEaten(bool Status);
        std::pair<int, int> getPosition() const;
};


class GameBoard{
    private:
        std::vector<std::vector<char>> grid;
        int weidht, height;
    public:
        GameBoard(int w, int h);
        void initialize();
        void setCell(int x, int y, char symbol);
        void draw() const;
        void clear();
        int getWeight() const;
        int getHeight() const;
};

class Game{
    private:
        const static char SNAKE_HEAD = '@';
        const static char SNAKE_BODY = 'O';
        const static char FOOD_CHAR = '*';
        const static char EMPTY_CELL = ' ';
        const static char BORDER_CHAR = '#';

        int weidht, height;
        int score;
        bool gameOver;
        Snake snake;
        Food food;
        GameBoard board;

        void UpdateDisplay(){
            system("cls");
            board.draw();
            std::cout << "Счёт: " << score << std::endl;
        }
    public:
        Game(int w = 20, int h = 15);

        void run();
        void handleInput();
        void update();
        void render();
        void UpdateDisplay();

        bool isGameOver() const;
        int getScore() const;
};




