

#ifndef SETCOLORFUN_H_INCLUDED
#define SETCOLORFUN_H_INCLUDED
#include <windows.h>
#include <iostream>
using namespace std;
 void SetColor(int ForgC);

void setColor(int ForgC);
class ColoredBox
{
    private:
    int Length, Width, Color;
    char** Box = new char* [Length];
    char boxChar;
    static int MaxArea,Area ;

    void setBox(int len, int wid, char boxChar)
    {
        for (int i = 0; i < Length; i++) {
            Box[i] = new char[Width];
        }

        for (int i = 0; i < len; i++) {
            for (int k = 0; k < wid; k++) {
                Box[i][k] = boxChar;
            }
        }
    }



    public:

    ColoredBox(int len, int wid)
    {
        Length = len;
        Width = wid;
        boxChar = '#';
        Color = 15;
        SetColor(Color);
        setBox(len, wid,boxChar);
    }



    ColoredBox(int len, int wid, int col, char CharofTheBox)
    {
        Length = len;
        Width = wid;
        Color = col;
        boxChar = CharofTheBox;
        setBox(Length,Width,boxChar);
    }




    void display()
     {
        SetColor(Color);
        for (int i = 0; i < Length; i++) {
            for (int k = 0; k < Width; k++) {

                cout << Box[i][k];
            }
            cout << endl;
        }
        SetColor(7);
    }

    void displayTransposed()
    {
        SetColor(Color);
        for (int i = 0; i < Width; i++)
        {
            for (int k = 0; k < Length; k++) {

                cout << boxChar;
            }
            cout << endl;
        }
        SetColor(7);
    }



    void displayWider()
    {
        SetColor(Color);
        for (int i = 0; i < Length; i++) {
            for (int k = 0; k < Width; k++) {
                cout << Box[i][k] << "  ";
            }
            cout << endl;
        }
        SetColor(7);
    }


    void displayChess(int col2)
    {
        for (int i = 0; i < Length; i++)
            {
            for (int k = 0; k < Width; k++)
             {
                if ((i + k) % 2 == 0)
                {
                    SetColor(col2);
                    cout << Box[i][k];
                }
                else {
                    SetColor(Color);
                    cout << Box[i][k];
                }
            }
            cout << endl;
        }
        SetColor(7);
    }



    void setColor(int col)
    {
        Color=col;
        SetColor(col);
    }



    int getArea()
    {
        Area=(Length * Width);
        return Area;
    }

    static int getMaxArea()
     {
        if (MaxArea < Area ){
            MaxArea = Area;
        }
            return MaxArea;
    }

    ~ColoredBox()
    {
        for (int i = 0; i < Length; i++) {
            delete[] Box[i];
        }
        delete[] Box;
    }


};




    int ColoredBox:: MaxArea = 0;
    int ColoredBox:: Area = 0;



int main()
{
    int len,wid,col,col2;
    char boxChar;
    cout<<"Enter length and width of the box separated by a space: ";
    cin>>len>>wid;
    ColoredBox* cb1;
    cb1 = new ColoredBox(len,wid);
    cb1->display();
    cout<<"Set the box to another color: ";
    cin>>col;
    cout<<"Displaying Transposed: "<<endl;
    cb1->setColor(col);
    cb1->displayTransposed();
    cout<<"Displaying Wider: "<<endl;
    cb1->displayWider();
    cout<<"Displaying Chess, enter the other color: "<<endl;
    cin>>col2;
    cb1->displayChess(col2);
    cout<<endl<<"Area="<<cb1->getArea();
    cout<<endl<<"Max Area="<<cb1->getMaxArea();
    delete cb1;
    cout<<endl<<"Enter length,width,color,character of the box separated by spaces: ";
    cin>>len>>wid>>col>>boxChar;
    ColoredBox* cb2;
    cb2 = new ColoredBox(len,wid,col,boxChar);
    cb2->display();
    cout<<"Displaying Transposed: "<<endl;
    cb2->displayTransposed();
    cout<<"Displaying Wider: "<<endl;
    cb2->displayWider();
    cout<<"Displaying Chess, enter the other color: "<<endl;
    cin>>col2;
    cb2->displayChess(col2);
    cout<<"Displaying original again:"<<endl;
    cb2->display();
    cout<<endl<<"Area="<<cb2->getArea();
    cout<<endl<<"Max Area="<<cb2->getMaxArea();
    delete cb2;
    return 0;
}
    void SetColor(int ForgC)
    {
        WORD wColor;

        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;

                       //We use csbi for the wAttributes word.
        if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
        {
                 //Mask out all but the background attribute, and add in the forgournd color
            wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
            SetConsoleTextAttribute(hStdOut, wColor);
        }
        return;
    }
    #endif


