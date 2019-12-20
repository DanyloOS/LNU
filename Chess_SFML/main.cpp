#include "SFML/Graphics.hpp"

static sf::Sprite sFigures[32]; // фігури
static int size = 56; // розмір квадрата з фігурою в текстурі tPieces
static int indent = 28; // ширина і висотка рамок навколо кліток дошки

// Елемент масиву == клітка на шахматній дошці:
// від'ємне число означає, що фігура чорна;
// додатнє -- що фігура біла;
static int board[8][8] =
    {{-1,-2,-3,-4,-5,-3,-2,-1},
     {-6,-6,-6,-6,-6,-6,-6,-6},
     { 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0},
     { 6, 6, 6, 6, 6, 6, 6, 6},
     { 1, 2, 3, 4, 5, 3, 2, 1}};

void loadPosition()
{
    int k = 0;
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
             {
               int n = board[i][j];
               if (!n) continue; // пропускаємо клікти без фігур
               int x = abs(n) - 1; // визначення типу фігури
               int y = n>0?1:0; // визначення кольору фігури
               // Присвоюємо кожній фігурі її текстуру, шляхом
               // обмеження прямокутною областю для взяття текстури
               // Присвоюємо кожній фігурі її початкову позицію
               // відповідно до даних в масиві board[8][8]
               sFigures[k].setTextureRect(sf::IntRect(size*x , size*y , size, size));
               sFigures[k].setPosition(size*j + indent, size*i + indent);
               k++;
             }

//        for(int i=0;i<position.length();i+=5)
//          move(position.substr(i,4));
}

int main()
{
    sf::RenderWindow window;
    // Створюємо вікно із розширенням 504х504, тобто таким
    // як і розмір дошки
    window.create(sf::VideoMode(504, 504), "CHESS");

    ////////////////////
    //int n = 0;
    ////////////////


    // Створюємо текстури фігур та дошки та загружаємо їх із
    // відповідних файлів
    sf::Texture tPieces, tBoard;
    tPieces.loadFromFile("images/figures.png");
    tBoard.loadFromFile("images/board.png");

    // Створюємо об'єкт sBoard типу sf::Sprite та присвоюємо йому
    // текстуру дошки
    // Присвоюємо кожному елементу масиму sFigures текстуру фігур
    sf::Sprite sBoard(tBoard);
    for (int i = 0; i < 32; i++) sFigures[i].setTexture(tPieces);

    // Присвоїмо фігурам початкові позиції на дошці
    loadPosition();

    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) // головний ігровий цикл
        {
            if (event.type == sf::Event::Closed) // Подія закриття вікна
                window.close();
        }

        window.clear();
        // Малюємо спрайт sBoard
        window.draw(sBoard);
        // Малюємо кожну фігуру
        for(int i = 0; i < 32; i++) window.draw(sFigures[i]); //window.draw(sFigures[n]);
        window.display();
    }


    return 0;
}
