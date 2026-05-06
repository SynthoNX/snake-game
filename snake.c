#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <conio.h>
#include <winsock2.h>
#include <windows.h> // for changing terminal settings


// debugging part

// ends here

#define HEIGHT 20
#define WIDTH 80

enum Direction {
    UP,
    DOWN,
    RIGHT,
    LEFT,
    STOP
};

int score;
int food_x, food_y; // food co-ordinates
int head_x, head_y; // snake head's co-ordinates
int tail_length;
int tail_x[100];
int tail_y[100];
enum Direction current_direction;

HANDLE keyboard_handle;
DWORD old_settings; // hold terminal old settings

void hide_cursor();
void clear_screen();
void welcome_text();
void set_terminal_attributes();
void reset_terminal_attributes();
void game_screen();
void setup();
void game_play();
void food();
void input();
void move_cursor_top_left();
void move_cursor_to_top();


int main() {
    clear_screen();
    srand(time(NULL)); 
    set_terminal_attributes(); // change the terminal settings for game
    hide_cursor();
    setup(); // set the game first time
    while(1) {
        move_cursor_to_top();
        game_screen(); // print game screen
        input();
        game_play();
        float sleep_time = 4000 / (score != 0 ? score : 10);
        Sleep(sleep_time);
    }


    exit(0); // this will help to reset the terminal settings
    return 0;
}

void game_play() {
    // update the head position
    for(int i = tail_length - 1; i > 0; i--) {
        tail_x[i] = tail_x[i - 1];
        tail_y[i] = tail_y[i - 1]; 
    }
    tail_x[0] = head_x;
    tail_y[0] = head_y;

    switch(current_direction) {
        case UP:
            head_y--;
            break;
        
        case DOWN:
            head_y++;
            break;

        case RIGHT:
            head_x++;
            break;

        case LEFT:
            head_x--;
            break;

        case STOP:
            // do nothing
            break;
    }

    // keep the snake in screen
    if(head_x < 0) {
        head_x = WIDTH - 1;
    } else if(head_x == WIDTH) {
        head_x = 0;
    }

    if(head_y <= 0) {
        head_y = HEIGHT;
    } else if(head_y > HEIGHT) {
        head_y = 1;
    }

    for(int i = 0; i < tail_length; i++) {
        if(tail_x[i] == head_x && tail_y[i] == head_y) {
            sleep(1);
            clear_screen();
            printf("Game over\nYour score is: %d\n", score);
            exit(0);
        }
    }
    // check if snake ate that food
    if(head_x == food_x && head_y == food_y) {
        score += 10;
        tail_length++;
        food(); // give a new position for food
    }

}

void game_screen() {
    // clear_screen();
    move_cursor_top_left();
    welcome_text();
    
    for(int y = 0; y < HEIGHT + 2; y++) { // print row wise
        if(y == 0 || y == HEIGHT + 1) {
            for(int i = 0; i < WIDTH + 2; i++) {
                printf("#");
            }
            printf("\n");
            continue;
        }
        printf("#");
        for(int x = 0; x < WIDTH; x++) {
            // print the main screen
            if(x == head_x && y == head_y) {
                printf("O");
            } else if(x == food_x && y == food_y) {
                printf("F");
            } else {
                int tail_found = 0;
                for(int k = 0; k < tail_length; k++) {
                    if(tail_x[k] == x && tail_y[k] == y) {
                        printf("o");
                        tail_found = 1;
                        break;
                    }
                }
                if(!tail_found) {
                    printf(" ");
                }
            }
        }
        printf("#\n");
    }
    printf("\nScore: %d\n", score);
    printf("\nFood: %d %d\n", food_x, food_y);
}

void set_terminal_attributes() {
    keyboard_handle = GetStdHandle(STD_INPUT_HANDLE);
    DWORD new_settings;
    GetConsoleMode(keyboard_handle, &old_settings);
    atexit(reset_terminal_attributes);
    new_settings = old_settings;
    new_settings &= ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);
    SetConsoleMode(keyboard_handle, new_settings);
}

void reset_terminal_attributes() {
    SetConsoleMode(keyboard_handle, old_settings);
}

void food() {
    // food will positioned randomly
    food_x = rand() % (WIDTH - 1) + 1;
    food_y = rand() % HEIGHT + 1;
}

void setup() {
    // snake will start from center of the screen
    head_x = WIDTH / 2;
    head_y = HEIGHT / 2;
    score = 0;
    tail_length = 0;

    food();

    current_direction = STOP;
}

// int input_available() {
//     struct timeval tv = { 0L, 0L };
//     fd_set fds;
//     FD_SET(0, &fds);
//     return select(1, &fds, NULL, NULL, &tv);
// }

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void welcome_text() {
    char text[] = "Welcome to The Snake Game!!!";
    int len = strlen(text);
    int start_point = (WIDTH + 2 - len) / 2;

    printf("\n");
    for(int x = 0; x < WIDTH + 2; x++) {
        if(x == start_point) {
            printf("%s", text);
            x += len;
        } else {
            printf(" ");
        }
    }
    printf("\n\n");
}

void input() {
    if(kbhit()) {
        char ch = _getch();

        switch(ch) {
            case 'u':
                current_direction = UP;
                break;
            
            case 'd':
                current_direction = DOWN;
                break;

            case 'l':
                current_direction = LEFT;
                break;

            case 'r':
                current_direction = RIGHT;
                break;

            case 'x':
                exit(0);
            default:
                // do nothing
                break;
        }
    }
}


void hide_cursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 1;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void move_cursor_top_left() {
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}

void move_cursor_to_top() {
    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
