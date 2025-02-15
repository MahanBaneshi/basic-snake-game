// writed by Mahan Baneshi
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <string.h>

#define map_length 20
#define map_width 30
#define border '@'
#define snake1_head 'O'
#define snake2_head '&'
#define apple '$'
#define snake1_body 'o'
#define snake2_body '8'
#define Bomb 'B'

// For the snake that moves with the arrow keys

typedef enum {
    up = 72,
    down = 80,
    left = 75,
    right = 77
} Direction;
Direction lastDir = right;

int  player1_score, player2_score;
bool gameover;
char player1_name[100];
char player2_name[100];

enum dir1ection {STOP=0, LEFT, RIGHT, UP, DOWN};
enum dir1ection dir1, dir2; 

struct point{
    int x, y;
};

struct point player1, player2, fruit, bomb;
struct point body1[400], body2[400]; // Snakes' bodies

int n_body1=0, n_body2=0; // Body length of snakes

void hidecursor() { // hide mouse cruser
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

// Rules of the game: Every snake that dies adds 4 points to another snake (I have made this rule myself)
void player1_dead() 
{
    printf("\n");
    printf("GAMEOVER!\n");
    player2_score += 4;
    gameover = true;
    printf("final score of %s %d\n", player1_name, player1_score);
    printf("final score of %s %d\n", player2_name, player2_score);
}
void player2_dead()
{
    printf("\n");
    printf("GAMEOVER!\n");
    player1_score += 4;
    gameover = true;
    printf("fianl score of %s %d\n", player1_name, player1_score);
    printf("final score of %s %d\n", player2_name, player2_score);  
}

void setup()
{
    player1.x = map_width/3;
    player1.y = map_length/3;

    player2.x = map_width*2/3;
    player2.y = map_length*2/3;

    fruit.x = rand() % (map_width-2)+1;
    fruit.y = rand() % (map_length-2)+1;

    bomb.x = rand() % (map_width-2)+1;
    bomb.y = rand() % (map_length-2)+1;

    gameover=false;
    player1_score= 0;
    player2_score= 0;

    dir1=STOP;
    dir2=STOP;
    n_body1 = 0;
    n_body2 = 0;
} 

void draw()
{
    system("cls");
    int i,j;
    for(i=0; i<map_width; i++)
    printf("%c", border);
    printf("\n");
    for(i=0; i<map_length; i++){
        for(j=0; j<map_width; j++){
            if(j==0 || j == map_width -1)
                printf("%c", border);
            else if(j == player1.x && i == player1.y)
                printf("%c", snake1_head);
            else if(j == player2.x && i == player2.y) 
                printf("%c", snake2_head);   
            else if(j == fruit.x && i == fruit.y)
                printf("%c", apple);
            else if(j == bomb.x && i == bomb.y)
                printf("%c", Bomb);    
                else {
                    bool z = false;
                    for(int k=0; k<n_body1; k++){
                    if(j==body1[k].x && i== body1[k].y){
                        printf("%c", snake1_body);
                        z = true;
                    }}
                    for(int b=0; b<n_body2; b++){
                    if(j==body2[b].x && i== body2[b].y){
                        printf("%c", snake2_body);
                        z = true;
                    }}
                    if (!z)
                    printf(" ");
                }     
        }
        printf("\n");
    }
    for(i=0; i<map_width; i++)
    printf("%c", border);

    printf("\n");
    printf("score of %s %d\n", player1_name, player1_score);
    printf("score of %s %d\n", player2_name, player2_score);
}

void input()
{
    if(kbhit()){   // left snake
        switch(getche())
        {
            case 'w':
            case 'W':
            if(dir1 != DOWN)
                dir1 = UP;
                break;
            case 's':
            case 'S':
            if(dir1 != UP)
                dir1 = DOWN;
                break;
            case 'a':
            case 'A':
            if(dir1 != RIGHT)
                dir1 = LEFT;
                break;
            case 'd':
            case 'D':
            if(dir1 != LEFT)
                dir1 = RIGHT;
                break;
            default:
            break;    
        }
    }
    if(_kbhit()){ //right snake
        switch(_getche())
        {
            case up:
            if(dir2 != DOWN)
                dir2 = UP;
                break;
            case down:
            if(dir2 != UP)
                dir2 = DOWN;
                break;
            case left:
            if(dir2 != RIGHT)
                dir2 = LEFT;
                break;        
            case right:
            if(dir2 != LEFT)
                dir2 = RIGHT;
                break;
            default:
            break;    
        }
    }
}
void rules()
{
    for(int i=n_body1-1; i>=1; i--){
        body1[i].x= body1[i-1].x;
        body1[i].y= body1[i-1].y;
    }
    for(int j=n_body2-1; j>=1; j--) {   
        body2[j].x= body2[j-1].x;
        body2[j].y= body2[j-1].y;
    }
    body1[0].x = player1.x;
    body1[0].y = player1.y;

    body2[0].x = player2.x;
    body2[0].y = player2.y;
        
    switch(dir1) //left snake
    {
        case LEFT:
            player1.x -= 1;
            break;
        case RIGHT:
            player1.x += 1;
            break;
        case UP:
            player1.y = player1.y-1 ;
            break;
        case DOWN:
            player1.y = player1.y+1 ;
            break; 
        default:
            break;      
    }

    switch(dir2) // right snake
    {
        case LEFT:
            player2.x -= 1;
            break;
        case RIGHT:
            player2.x += 1;
            break;
        case UP:
            player2.y = player2.y-1 ;
            break;
        case DOWN:
            player2.y = player2.y+1 ;
            break; 
        default:
            break;      
    }

    if(player1.x == map_width || player1.x == 0){
        player1_dead();
    }
    else if (player1.y == map_length || player1.y == -1){
        player1_dead();
    }
    if(player2.x == map_width || player2.x == 0){
        player2_dead();
    }
    else if (player2.y == map_length || player2.y == -1){
        player2_dead();
    }
    if(player1.x == bomb.x && player1.y == bomb.y){
        player1_dead();
    }
    if(player2.x == bomb.x && player2.y == bomb.y){
        player2_dead();
    }
    for(int i=n_body1-1; i>=1; i--){
        if(player1.x == body1[i].x && player1.y == body1[i].y){
            player1_dead();
        }
    }

    if(bomb.x == fruit.x && bomb.y == fruit.y){
        fruit.x = rand() % (map_width-2)+1;
        fruit.y = rand() % (map_length-2)+1;  
    }
    
    for(int j=n_body2-1; j>=1; j--)  {
        if(player2.x == body2[j].x && player2.y == body2[j].y){
            player2_dead();
        }
    }
    if(player1.x == fruit.x && player1.y == fruit.y){
        player1_score += 1;
        fruit.x = rand() % (map_width-2)+1;
        fruit.y = rand() % (map_length-2)+1;
        n_body1++;
    }
    if(player2.x == fruit.x && player2.y == fruit.y){
        player2_score += 1;
        fruit.x = rand() % (map_width-2)+1;
        fruit.y = rand() % (map_length-2)+1;
        n_body2++;
    }
    
    //Rule: If the head of one snake touches the body of another snake, it dies.
    for(int i=n_body2-1; i>=1; i--){
        if(player1.x == body2[i].x && player1.y == body2[i].y){
            player1_dead();
        }
    }
    for(int j=n_body1-1; j>=1; j--)  {
        if(player2.x == body1[j].x && player2.y == body1[j].y){
            player2_dead();
        }
    }
    if(player1.x == player2.x && player1.y == player2.y){
        printf("\n");    
        printf("GAMEOVER!\n");
        gameover = true;
        printf("final score of %s %d\n", player1_name, player1_score);
        printf("final score of %s %d\n", player2_name, player2_score);  
    }
}

void slow_snake()
{
    srand(time(NULL));
    setup();

    while(!gameover){
        draw();
        input();
        rules();
        hidecursor();
        Sleep(500);
    }
    if(player1_score > player2_score){
        printf("winner is:%s\n", player1_name);
    }
    else if(player1_score < player2_score){
        printf("winner is:%s\n", player2_name);
    }
    else
        printf("The game equalised\n");
        printf("Enter 1 to play again\n");
        printf("Enter 2 to exit\n");
    int n;
    scanf("%d", &n);
    if (n==1){
        slow_snake();
    }
    else if(n==2){
        exit;
    }

}
void medium_snake()
{
    srand(time(NULL));
    setup();

    while(!gameover){
        draw();
        input();
        rules();
        hidecursor();
        Sleep(300);
    }
    if(player1_score > player2_score){
        printf("winner is:%s\n", player1_name);
    }
    else if(player1_score < player2_score){
        printf("winner is:%s\n", player2_name);
    }
    else
        printf("The game equalised\n");
        printf("Enter 1 to play again\n");
        printf("Enter 2 to exit\n");
    int n;
    scanf("%d", &n);
    if (n==1){
        medium_snake();
    }
    else if(n==2){
        exit;
    }
}
void fast_snake()
{
    srand(time(NULL));
    setup();

    while(!gameover){
        draw();
        input();
        rules();
        hidecursor();
        Sleep(50);
    }
    if(player1_score > player2_score){
        printf("winner is:%s\n", player1_name);
    }
    else if(player1_score < player2_score){
        printf("winner is:%s\n", player2_name);
    }
    else
        printf("The game equalised\n");
        printf("Enter 1 to play again\n");
        printf("Enter 2 to exit\n");
    int n;
    scanf("%d", &n);
    if (n==1){
        fast_snake();
    }
    else if(n==2){
        exit;
    }
}

void start_game()
{
    printf("please enter your names\n");
    fgets(player1_name, sizeof(player1_name), stdin);
    fgets(player2_name, sizeof(player2_name), stdin);
    printf("Hello. Determine the speed of your snake\n");
    printf("1:slow\n");
    printf("2:medium\n");
    printf("3:fast\n");
    int num;
    scanf("%d", &num);
    switch(num)
    {
    case 1: slow_snake();
        break; 
    case 2: medium_snake();
        break;   
    case 3: fast_snake();
        break;        
    }
}
int main()
{
    start_game();
    return 0;
}

