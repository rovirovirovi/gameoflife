#include <ncurses.h>

int main(){
    int ch;
    int generation = 0;

    int scrWidth, scrHeight;

    initscr();
    raw();
    keypad(stdscr, TRUE);
    cbreak();
    noecho();

    getmaxyx(stdscr, scrHeight, scrWidth);

    int map[scrWidth][scrHeight];
    int next[scrWidth][scrHeight];
    for(int x = 0; x < scrWidth; x++){
        for(int y = 0; y < scrHeight; y++){
            map[x][y] = 0;
            next[x][y] = 0;
        }
    }
    map[scrWidth / 2][scrHeight / 2] = 1;
    map[scrWidth / 2][scrHeight / 2+1] = 1;
    map[scrWidth / 2][scrHeight / 2+2] = 1;
    map[scrWidth / 2 - 1 ][scrHeight / 2+2] = 1;
    map[scrWidth / 2-2][scrHeight / 2+1] = 1;

    while(1){ // update
        
        

        for(int x = 1; x < scrWidth - 1; x++){
            for(int y = 1; y < scrHeight - 1; y++){
                int friends = 0;

                for(int nx = -1; nx <= 1; nx++){
                    for(int ny = -1; ny <= 1; ny++){
                        if(map[x + nx][y + ny] == 1)
                            friends++;
                    }
                }

                friends -= map[x][y];

                if(map[x][y] == 1 && friends < 2){
                    next[x][y] = 0;
                }
                else if(map[x][y] == 1 && friends > 3){
                    next[x][y] = 0;
                }
                else if(map[x][y] == 0 && friends == 3){
                    next[x][y] = 1;
                }
                else{
                    next[x][y] = map[x][y];
                }
                
            }
        }

        for(int x = 0; x < scrWidth; x++){
            for(int y = 0; y < scrHeight; y++){
                map[x][y] = next[x][y];
            }
        }

        clear();
        for(int x = 0; x < scrWidth; x++){
            for(int y = 0; y < scrHeight; y++){
                if(map[x][y] != 0)
                    mvaddch(y,x, (char)176);
                
            }
        }
        mvprintw(0,0,"Gen %d", generation);


        refresh();

        ch = getch();
        generation++;

        if(ch == 'q')
            break;

    }

    clrtoeol();
    refresh();
    endwin();

    return 0;
}
