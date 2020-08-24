#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cstddef>
#include <cstdio>
#include <cstdlib>

using namespace std;
using namespace sf;

#define displayLength 128
#define displayHeight 32
#define rectangleY 8.f
#define rectangleX 6.f

class Pixel
{
public:
    int x;
    int y;
    int sizeX;
    int sizeY;
    Color color;
    Pixel()
    {
        x = 0;
        y = 0;
        sizeX = 10;
        sizeY = 10;
    }
    Pixel(int x, int y, Color color)
    {
        this->x = x;
        this->y = y;
        this->color = color;
        this->sizeX = 10;
        this->sizeY = 10;
    }
    Pixel(int x, int y, int sizeX, int sizeY, Color color)
    {
        this->x = x;
        this->y = y;
        this->sizeX = sizeX;
        this->sizeY = sizeY;
        this->color = color;
    }
    void draw(sf::RenderWindow& window)
    {
        RectangleShape rectangle(Vector2f(sizeX, sizeY));
        rectangle.move(x, y);
        rectangle.setFillColor(color);
        window.draw(rectangle);
    }
};

class Display
{
public:
    bool matrix[displayHeight][displayLength];
    Display()
    {
        for (int i = 0; i < displayHeight; i++)
            for (int j = 0; j < displayLength; j++)
                matrix[i][j] = false;
    }
    Pixel** draw(sf::RenderWindow& window)
    {
        Pixel** display = new Pixel*[displayHeight];
        int Y = 0;
        for (int i = 0; i < displayHeight; i++)
        {
            display[i] = new Pixel[displayLength];
            int X = 0;
            for (int j = 0; j < displayLength; j++)
            {
                if (matrix[i][j])
                    display[i][j] = Pixel(X, Y, Color(48, 60, 26));
                else
                    display[i][j] = Pixel(X, Y, Color(154, 205, 50));
                display[i][j].draw(window);
                X += 10;
            }
            Y += 10;
        }
        return display;
    }
};

Display loadData(const char* filename)
{
    Display display;
    cout << "Loading file:" << endl;

    FILE* file = NULL;
    if ((file = fopen(filename, "rb")) == NULL)
    {
        cout << "Failed open file" << endl;
        exit(-1);
    }
    else
    {
        cout << "Ok" << endl;

    }
    int byte;
    vector<int> data;
    while ((byte = fgetc(file)) != EOF)
    {
        data.push_back(byte);
    }
    fclose(file);
    //Default output
    /*
    for (int i = 0; i < data.size(); i++)
        cout << data[i] << " ";
    cout << endl;
    */

    //Output HEX
    for (int i = 1; i < data.size()+1; i++)
    {
        cout << hex << data[i-1];

        if (i % 2 == 0)
            cout << " ";
        if (i % 12== 0)
            cout << endl;
    }

    //Matrix creator
    int x = 0;
    int y = 0;
    for (int i = 0; i < data.size(); i++)
    {
        if (y == displayLength)
        {
            y = 0;
            x++;
        }
        if (data[i] == 0)
            display.matrix[x][y] = true;
        y++;
    }
    cout << endl;
    cout << endl;
    cout << endl;
    for (int i = 0; i < displayHeight; i++)
    {
        for (int j = 0; j < displayLength; j++)
        {
            if (display.matrix[i][j])
                cout << "1";
            else
                cout << "0";
        }
        cout << endl;
    }

    return display;
}



int main()
{
    Display display = loadData("/home/andrey/Документы/Projects/LoadingIdicatorDisplay/ImitatorDisplay/res");
    RenderWindow window(VideoMode(displayLength*10, displayHeight*10), "Display");
    while (window.isOpen())
    {

        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        display.draw(window);
        window.display();
    }

    return 0;
}
