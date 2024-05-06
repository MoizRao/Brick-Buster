#include <iostream>
#include<fstream>
#include "youregraphics.h"

using namespace std;

int w, h;
int lives = 3;
int score = 0;
int top_score = 0;
int current_score;
int score_arr[6] = { 0,0,0,0,0,0 };
int combo = 0;
bool quit = false;
 

// Struct for rectangles

struct rect {
    int x1;
    int y1;
    int x2;
    int y2;
    int health;
};

//struct for ball

struct circle {
    int x = 0;
    int y = 0;
    int width = 15;
    int height = 15;
    int vil_x = -5;
    int vil_y = 5;
};

// Declarations

rect paddle;
rect right_side, left_side;
circle ball;
rect brick[5][12];


// Reading the saved file

void reading(rect brick[][12], rect& paddle, circle& ball, int& lives, int& score, int& combo) {
    ifstream readFile("saved.txt");
    readFile >> lives >> score >> combo;
    readFile >> ball.x >> ball.y >> ball.width >> ball.height >> ball.vil_x >> ball.vil_y;
    readFile >> paddle.x1 >> paddle.y1 >> paddle.x2 >> paddle.y2;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 12; j++) {
            readFile >> brick[i][j].x1 >> brick[i][j].y1 >> brick[i][j].x2 >> brick[i][j].y2 >> brick[i][j].health;
        }
    }
    readFile.close();
}

// Writing data in file

void writing(rect brick[][12], rect paddle, circle ball, int& lives, int& score, int& combo) {
    ofstream writeFile("saved.txt");
    writeFile << lives << " " << score << " " << combo << " ";
    writeFile << ball.x << " " << ball.y << " " << ball.width << " " << ball.height << " " << ball.vil_x << " " << ball.vil_y << " ";
    writeFile << paddle.x1 << " " << paddle.y1 << " " << paddle.x2 << " " << paddle.y2 << " ";

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 12; j++) {
            writeFile << brick[i][j].x1 << " " << brick[i][j].y1 << " " << brick[i][j].x2 << " " << brick[i][j].y2 << " " << brick[i][j].health << " ";
        }
    }
    writeFile.close();
}

// Checking if ball collides with bricks

void brick_detection() {
    int i, j;
    for (i = 0; i < 5; i++) {

        for (j = 0; j < 12; j++) {

            if (brick[i][j].health > 0) {

                if (ball.x + ball.width + ball.vil_x > brick[i][j].x1 && ball.x + ball.vil_x<brick[i][j].x2 && ball.y + ball.height>brick[i][j].y1 &&
                    ball.y < brick[i][j].y2)
                {
                    brick[i][j].health--;
                    ball.vil_x *= -1;
                    if (brick[i][j].health > 0) {
                        score += 1;
                    }
                    else {
                        score += 5;
                    }
                    
                    if (brick[i][j].health == 4) {

                        drawRectangle(brick[i][j].x1, brick[i][j].y1,
                            brick[i][j].x2, brick[i][j].y2, 122, 125, 125, 253, 72, 72);

                    }

                    else if (brick[i][j].health == 3) {

                        drawRectangle(brick[i][j].x1, brick[i][j].y1,
                            brick[i][j].x2, brick[i][j].y2, 122, 125, 125, 247, 150, 150);

                    }

                    else if (brick[i][j].health == 2) {

                        drawRectangle(brick[i][j].x1, brick[i][j].y1,
                            brick[i][j].x2, brick[i][j].y2, 122, 125,
                            125, 153, 153, 255);

                    }
                    else if (brick[i][j].health == 1) {

                        drawRectangle(brick[i][j].x1, brick[i][j].y1,
                            brick[i][j].x2, brick[i][j].y2, 122, 125,
                            125, 204, 229, 255);

                    }
                    else if (brick[i][j].health == 0) {
                        combo++;
                        drawRectangle(brick[i][j].x1, brick[i][j].y1,
                            brick[i][j].x2, brick[i][j].y2, 122, 125, 125,
                            122, 125, 125);

                    }

                }
                else if (ball.x + ball.width > brick[i][j].x1 &&
                    ball.x  < brick[i][j].x2 && ball.y + ball.height + ball.vil_y >
                    brick[i][j].y1 && ball.y + ball.vil_y < brick[i][j].y2)
                {
                    brick[i][j].health--;
                    ball.vil_y *= -1;

                        if (brick[i][j].health == 4 || brick[i][j].health == 3 || brick[i][j].health == 2 || brick[i][j].health == 1) {
                            score += 1;
                        }
                        else {
                            score += 5;
                        }


                        if (brick[i][j].health == 4) {

                            drawRectangle(brick[i][j].x1, brick[i][j].y1,
                                brick[i][j].x2, brick[i][j].y2, 122, 125, 125, 253, 72, 72);

                        }

                        else if (brick[i][j].health == 3) {

                            drawRectangle(brick[i][j].x1, brick[i][j].y1,
                                brick[i][j].x2, brick[i][j].y2, 122, 125, 125, 247, 150, 150);

                        }

                        else if (brick[i][j].health == 2) {

                            drawRectangle(brick[i][j].x1, brick[i][j].y1,
                                brick[i][j].x2, brick[i][j].y2, 122, 125,
                                125, 153, 153, 255);

                        }
                        else if (brick[i][j].health == 1) {

                            drawRectangle(brick[i][j].x1, brick[i][j].y1,
                                brick[i][j].x2, brick[i][j].y2, 122, 125,
                                125, 204, 229, 255);

                        }
                        else if (brick[i][j].health == 0) {
                            combo++;
                            drawRectangle(brick[i][j].x1, brick[i][j].y1,
                                brick[i][j].x2, brick[i][j].y2, 122, 125, 125,
                                122, 125, 125);

                        }

                     }

            }
        }
    }
}

// Checking if paddle hits the ball

void paddlecollision() {
    
    if (ball.y > h - 100) {
        if (ball.x + ball.width + ball.vil_x > paddle.x1 && ball.x +
            ball.vil_x<paddle.x2 && ball.y + ball.height>paddle.y1 && ball.y <
            paddle.y2)
            ball.vil_x *= -1;

        else if (ball.x + ball.width > paddle.x1 && ball.x  <paddle.x2 &&
            ball.y + ball.height + ball.vil_y > paddle.y1 && ball.y + ball.vil_y <
            paddle.y2)
        {
            if (ball.x + ball.width >= paddle.x1 && ball.x + ball.width <= paddle.x1 + 48) {
                if (ball.vil_x > 0) {
                    ball.vil_y = -5;
                    ball.vil_x = -5;
                }
                else if (ball.vil_x <= 0) {
                    ball.vil_y = -5;
                    ball.vil_x = -5;
                }
            }

            else if (ball.x + ball.width > paddle.x1 + 48 && ball.x + ball.width <= paddle.x1 + 68) {
                ball.vil_x = 0;
                ball.vil_y = -5;
            }

            else if (ball.x + ball.width > paddle.x1 + 68 && ball.x + ball.width <= paddle.x2) {
                if (ball.vil_x >= 0) {
                    ball.vil_y = -5;
                    ball.vil_x = 5;
                }
                else if (ball.vil_x < 0) {
                    ball.vil_y = -5;
                    ball.vil_x = 5;
                }
            }
        }
    }

}

// Sides collision

void sides_collision() {
    if (ball.x <= right_side.x2 + 2 || ball.x + ball.width >= left_side.x1 - 5) {
        ball.vil_x *= -1;
    }
    if (ball.y <= 45) {
        ball.vil_y *= -1;
    }

}

// Check for out

void check_out() {

    if (ball.y > paddle.y2) {
        lives--;
        combo = 0;
        gotoxy(95, 1);
        cout << "     ";
        if (lives == 2) {
            drawEllipse(w - 70, 15, 15 + (w - 70), 15 + 15, 12, 12, 12, 12, 12, 12);
        }
        else if (lives == 1) {
            drawEllipse(w - 90, 15, 15 + (w - 90), 15 + 15, 12, 12, 12, 12, 12, 12);
        }
        else if (lives == 0) {
            drawEllipse(w - 110, 15, 15 + (w - 110), 15 + 15, 12, 12, 12, 12, 12, 12);
        }
        if (lives > 0) {
            drawEllipse(ball.x, ball.y, ball.width + ball.x, ball.height +
                ball.y, 122, 125, 125, 122, 125, 125);

            ball.x = paddle.x1 + 40;
            ball.y = h - 90;
            drawEllipse(ball.x, ball.y, ball.width + ball.x, ball.height +
                ball.y, 0, 0, 0, 0, 0, 0);


            delay(1500);
        }
    }
}

// Paddle movement

void movepaddle(char c) { 
    
        if (c == 'd' || c == 'D') {
            paddle.x1 += 18;
            paddle.x2 += 18;
            drawRectangle(paddle.x1, paddle.y1, paddle.x1 - 18, paddle.y2, 122, 125, 125, 122, 125, 125);

        }
        if (c == 'a' || c == 'A') {
            paddle.x1 -= 18;
            paddle.x2 -= 18;
            drawRectangle(paddle.x2, paddle.y1, paddle.x2 + 18, paddle.y2, 122, 125, 125, 122, 125, 125);
        }

        // Saving game

        if (c == 's' || c == 'S') {
            writing(brick, paddle, ball, lives, score, combo);
            
        }

        // Pause feature

        if (c == 'p' || c == 'P') {
            while (true) {
                drawRectangle(paddle.x1, paddle.y1, paddle.x2, paddle.y2, 0, 0, 0, 0, 0, 0);

                char k;
                k = getKey();
                if (k == 'c' || k == 'C') {
                    break;
                }
            }
        }

        // For quitting game

        if (c == 'q' || c == 'Q') {
            quit = true;
        }
  
    if (paddle.x1 < 10) {
        paddle.x1 = 10;
        paddle.x2 = paddle.x1 + 100;
    }
    else if (paddle.x2 >= (w - 10)) {
        paddle.x2 = w - 10;
        paddle.x1 = paddle.x2 - 100;
    }
    drawRectangle(paddle.x1, paddle.y1, paddle.x2, paddle.y2, 0, 0, 0, 0, 0, 0);
}

// Ball movement and collision checks

void moveball() {
    drawEllipse(ball.x, ball.y, ball.width + ball.x, ball.height +
        ball.y, 122, 125, 125, 122, 125, 125);

    paddlecollision();
    brick_detection();
    sides_collision();
    check_out();
    drawEllipse(ball.x, ball.y, ball.width + ball.x, ball.height +
        ball.y, 122, 125, 125, 122, 125, 125);
    ball.x += ball.vil_x;
    ball.y += ball.vil_y;
    drawEllipse(ball.x, ball.y, ball.width + ball.x, ball.height +
        ball.y, 0, 0, 0, 0, 0, 0);

}


// Main function

int main() {
    SetProcessDPIAware();

    getWindowDimensions(w, h);
    cls();

    int height = 42;
    int width = ((w - 8) - 8);
    brick[0][0].x1 = 13;
    brick[0][0].x2 = brick[0][0].x1 + width / 12;
    brick[0][0].y1 = height;
    brick[0][0].y2 = brick[0][0].y1 + 30;

    paddle.x1 = w / 2;
    paddle.x2 = paddle.x1 + 100;
    paddle.y1 = h - 35;
    paddle.y2 = h - 30;

    ball.x = (w / 2) + 40;
    ball.y = h - 80;

    //Reading high score from the file.

    ifstream readScore("highScore.txt");
    for (int i = 1; i < 6; i++) {
        readScore >> score_arr[i];
    }
    top_score = score_arr[5];

    // Showing info and instructions on console

    cout << "=> Instructions and info :" << endl<<endl;
    cout << "1.  Press A or D t0 move paddle left or right.\n";
    cout << "2.  Press P to pause the game.\n";
    cout << "3.  Press C to continue the game.\n";
    cout << "4.  Press S to save the game.\n";
    cout << "5.  Press Q to quit the game.\n";
    cout << "6.  Every hit gives you 1 score.\n";
    cout << "7.  If your hit destroys brick you'll get 5 score.\n";
    cout << "8.  After destroying the brick combo will increase by 1.\n";
    cout << "9.  Top row of bricks have 5 health and keeps on\n";
    cout << "    decreasing in every preceding row.\n";
    cout << "10. You have total three lives .\n";
    cout << endl;
    cout << "=> Top 5 high scores :\n\n";
    cout << "1.  " << score_arr[5] << "\n";
    cout << "2.  " << score_arr[4] << "\n";
    cout << "3.  " << score_arr[3] << "\n";
    cout << "4.  " << score_arr[2] << "\n";
    cout << "5.  " << score_arr[1] << "\n";
    cout << endl;



    // Asking user wheather he wants to play saved or new game

    char opt;
    cout << "Do you want to play Saved game or New game \"s\" or \"n\" : ";
    cin >> opt;
    while (opt != 's' && opt != 'S' && opt != 'n' && opt != 'N') {
        cout << " S or N? "; cin >> opt;
    }
    gotoxy(0, 0);
    cls();
    if (opt == 's' || opt == 'S') {
        reading(brick, paddle, ball, lives, score, combo);
        delay(1000);
    }
    else if (opt == 'n' || opt == 'N') {

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 12; j++) {

                if (i == 0 ) {
                    brick[i][j].health = 5;
                }
                else if (i == 1) {
                    brick[i][j].health = 4;
                }
                else if (i == 2) {
                    brick[i][j].health = 3;
                }
                else if (i == 3) {
                    brick[i][j].health = 2;
                }
                else if (i == 4) {
                    brick[i][j].health = 1;
                }


                brick[i][j].x1 = brick[0][0].x1 + (j * (width / 12));
                brick[i][j].x2 = brick[i][j].x1 + (width / 12) - 1;
                brick[i][j].y1 = height + (i * 30);
                brick[i][j].y2 = brick[i][j].y1 + 30;
            }
        }
    }


    // Background 

    drawRectangle(0, 0, w, h, 122, 125, 125, 122, 125, 125);
    showConsoleCursor(false);

    // side boundries

    right_side.x1 = 0;
    right_side.x2 = 8;
    left_side.x1 = w - 8;
    left_side.x2 = w;

    drawRectangle(left_side.x1, 0, left_side.x2, h, 122, 125, 125, 122, 125, 125);
    drawRectangle(right_side.x1, 0, right_side.x2, h, 122, 125, 125, 122, 125, 125);

    // lower boundry

    rect lb;
    lb.x1 = 0;
    lb.y1 = h - 5;
    lb.x2 = w;
    lb.y2 = h;

    drawRectangle(lb.x1, lb.y1, lb.x2, lb.y2, 122, 125, 125, 0, 0, 0);



    // Printing bricks


    for (int i = 0; i < 5; i++) {

        for (int j = 0; j < 12; j++) {

            if (brick[i][j].health > 0) {

                if (brick[i][j].health == 5)
                    drawRectangle(brick[i][j].x1, brick[i][j].y1,
                        brick[i][j].x2, brick[i][j].y2, 122, 125, 125, 169, 0, 0);

                else if (brick[i][j].health == 4)
                    drawRectangle(brick[i][j].x1, brick[i][j].y1,
                        brick[i][j].x2, brick[i][j].y2, 122, 125, 125, 253, 72, 72);

                else if (brick[i][j].health == 3)
                    drawRectangle(brick[i][j].x1, brick[i][j].y1,
                        brick[i][j].x2, brick[i][j].y2, 122, 125, 125, 247, 150, 150);

                else if (brick[i][j].health == 2)
                    drawRectangle(brick[i][j].x1, brick[i][j].y1,
                        brick[i][j].x2, brick[i][j].y2, 122, 125, 125, 153, 153, 255);

                else if (brick[i][j].health == 1)
                    drawRectangle(brick[i][j].x1, brick[i][j].y1,
                        brick[i][j].x2, brick[i][j].y2, 122, 125, 125, 204, 229, 255);

            }

        }

    }



    // Printing Paddle

    char key;
    drawRectangle(paddle.x1, paddle.y1, paddle.x2, paddle.y2, 0, 0,
        0, 0, 0, 0);

    // Printing Ball

    drawEllipse(ball.x, ball.y, ball.width + ball.x, ball.height +
        ball.y, 0, 0, 0, 0, 0, 0);

    // Progress information bar

    drawRectangle(0, 0, w, 40, 12, 12, 12, 12, 12, 12);

    gotoxy(100, 1);
    cout << "LIVES";
    if (lives == 3) {
        drawEllipse(w - 110, 15, 15 + (w - 110), 15 + 15, 0, 0, 0, 255, 0, 0);
        drawEllipse(w - 90, 15, 15 + (w - 90), 15 + 15, 0, 0, 0, 255, 0, 0);
        drawEllipse(w - 70, 15, 15 + (w - 70), 15 + 15, 0, 0, 0, 255, 0, 0);
    }
    else if (lives == 2) {
        drawEllipse(w - 110, 15, 15 + (w - 110), 15 + 15, 0, 0, 0, 255, 0, 0);
        drawEllipse(w - 90, 15, 15 + (w - 90), 15 + 15, 0, 0, 0, 255, 0, 0);
    }
    else if (lives == 1) {
        drawEllipse(w - 110, 15, 15 + (w - 110), 15 + 15, 0, 0, 0, 255, 0, 0);
    }

    gotoxy(2, 1);
    cout << "HIGH SCORE";
    gotoxy(22, 1);
    cout << "SCORE";
    gotoxy(88, 1);
    cout << "COMBO";

    // Main event loop

    while (lives > 0) {

        gotoxy(29, 1);
        cout << score;

        if (score > top_score) {
            top_score = score;
        }
        gotoxy(14, 1);
        cout << top_score;

        gotoxy(95, 1);
        cout << combo;
        if (score == 420) {
            break;
        }
        if (quit) {
            break;
        }

        key = getKey();
        movepaddle(key);
        moveball();
        delay(16);

    }

    // Placing the score in a file if it is greater then the smallest 'high score' which 
    // is already saved in the file.

    int currentscore = score;
    score_arr[0] = score;

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 5; j++) {
            if (score_arr[j] > score_arr[j + 1]) {
                int temp = score_arr[j + 1];
                score_arr[j + 1] = score_arr[j];
                score_arr[j] = temp;
            }
        }
    }

    if (score_arr[0] != currentscore)
    {
        ofstream writeScore("highScore.txt");
        for (int i = 1; i < 6; i++) {
            writeScore << score_arr[i] << " ";
        }
    }

    //  If game is quitted

    if (quit) {
        delay(400);
        cls();
        drawRectangle(0, 0, w, h, 12, 12, 12, 12, 12, 12);
        gotoxy(48, 14);
        cout << "YOU'VE QUIT THE GAME";
        delay(100000);
    }

    //  Checking if all bricks have broken

    if (score == 420) {
        delay(2000);
        cls();
        drawRectangle(0, 0, w, h, 12, 12, 12, 12, 12, 12);
        gotoxy(50, 14);
        cout << "MISSION SUCCESSFUL";
        delay(100000);
    }

    // Checking if game is over

    if (lives == 0) {
        delay(2000);
        cls();
        drawRectangle(0, 0, w, h, 12, 12, 12, 12, 12, 12);
        gotoxy(55, 14);
        cout << "GAME OVER!";
        delay(100000);
    }

    return 0;
}
