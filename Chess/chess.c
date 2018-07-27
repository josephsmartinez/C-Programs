//#include <sys/types.h>
//#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int board[8][8];


int not_pawns(int c1, int r1, int c2, int r2)
{
    // knights
    if (abs(board[r1][c1]) == 2) {
        if ((r2 == r1-2 && (c2 == c1-1 || c2 == c1+1)) ||    // top row of valid moves up 2 over 1
            (r2 == r1-1 && (c2 == c1-2 || c2 == c1+2)) ||    // up one over 2
            (r2 == r1+1 && (c2 == c1-2 || c2 == c1+2)) ||    // down one over 2
            (r2 == r1+2 || (c2 == c1-1 || c2 == c1+1)))      // down 2 over 1
            return 1;

    // kings
    } else if (abs(board[r1][c1]) == 6) {
        if (abs(r1-r2) <= 1 && abs(c1-c2) <= 1)   // cover the whole square
            return 1;

    // rooks
    } else if (abs(board[r1][c1]) == 4) {
        if (r1 == r2) {
            if (c2 > c1) {
                for (int i=c1+1; i<c2; ++i) {
                    if (board[r1][i]) {
                        printf("Error, can't move through a piece!\n");
                        return 0;
                    }
                }
            } else {
                for (int i=c1-1; i>c2; --i) {
                    if (board[r1][i]) {
                        printf("Error, can't move through a piece!\n");
                        return 0;
                    }
                }
            }
            return 1;
        } else if (c1 == c2) {
            if (r2 > r1) {
                for (int i=r1+1; i<r2; ++i) {
                    if (board[i][c1]) {
                        printf("Error, can't move through a piece!\n");
                        return 0;
                    }
                }
            } else {
                for (int i=r1-1; i>r2; --i) {
                    if (board[i][c1]) {
                        printf("Error, can't move through a piece!\n");
                        return 0;
                    }
                }
            }
            return 1;
        }

        // didn't move along a perpendicular
        return 0;

    // bishops
    } else if (abs(board[r1][c1]) == 3) {
        if (abs(r1-r2) != abs(c1-c2))  // moved more horizontally than vertically or vice versa
            return 0;

        // check for moving through pieces uggh
        int dr = (r2 > r1) ? 1 : -1;
        int dc = (c2 > c1) ? 1 : -1;
        for (int i=r1+dr, j=c1+dc; i<r2; i+=dr, j+=dc) {
            if (board[i][j]) {
                printf("Error, can't move through a piece!\n");
                return 0;
            }
        }

        // otherwise it was valid
        return 1;

    // queens
    } else if (abs(board[r1][c1]) == 5) {
        if (abs(r1-r2) == abs(c1-c2)) {
            // move like bishop
            // check for moving through pieces uggh
            int dr = (r2 > r1) ? 1 : -1;
            int dc = (c2 > c1) ? 1 : -1;
            for (int i=r1+dr, j=c1+dc; i<r2; i+=dr, j+=dc) {
                if (board[i][j]) {
                    printf("Error, can't move through a piece!\n");
                    return 0;
                }
            }
            return 1;
        } else if (r1 == r2) {    // moving like a rook
            if (c2 > c1) {
                for (int i=c1+1; i<c2; ++i) {
                    if (board[r1][i]) {
                        printf("Error, can't move through a piece!\n");
                        return 0;
                    }
                }
            } else {
                for (int i=c1-1; i>c2; --i) {
                    if (board[r1][i]) {
                        printf("Error, can't move through a piece!\n");
                        return 0;
                    }
                }
            }
            return 1;
        } else if (c1 == c2) {  // moving like a rook along a column
            if (r2 > r1) {
                for (int i=r1+1; i<r2; ++i) {
                    if (board[i][c1]) {
                        printf("Error, can't move through a piece!\n");
                        return 0;
                    }
                }
            } else {
                for (int i=r1-1; i>r2; --i) {
                    if (board[i][c1]) {
                        printf("Error, can't move through a piece!\n");
                        return 0;
                    }
                }
            }
            return 1;
        }

    }

    printf("Error, invalid move!\n");
    return 0;
}

int move(int c1, int r1, int c2, int r2, int is_cap)
{
    if (!board[r1][c1]) {
        printf("Error, no piece in that position!\n");
        return 0;
    }

    if (r1 == r2 && c1 == c2) {
        printf("Error, you can't 'move' to the same position!\n");
        return 0;
    }

    int tmp;

    if (is_cap) {
        if (!board[r2][c2]) {
            printf("Error, no piece to capture there!\n");
            return 0;
        } else if (board[r1][c1] > 0 && board[r2][c2] > 0 || board[r1][c1] < 0 && board[r2][c2] < 0) {
            printf("Error, can't capture one of your own pieces!\n");
            return 0;
        }

        if (board[r1][c1] == 1) {
            if (r2 == r1-1 && abs(c2-c1) == 1)  // whites capture up = down in memory and diagonal
                return 1;
        } else if (board[r1][c1] == -1) {
            if (r2 == r1+1 && abs(c2-c1) == 1)   // black pawns are opposite
                return 1;
        } else {
            return not_pawns(c1, r1, c2, r2);
        }

    } else {

        if (board[r2][c2]) {
            printf("There's already a piece there, use cp command!\n");
            return 0;
        }

        // pawns
        if (board[r1][c1] == 1) {
            if (c1 == c2 && (r2 == r1-1 || (r2 == r1-2 && r1== 6 && !board[r1-1][c1])))   // white moves 1 or possible 2 up
                return 1;
        } else if (board[r1][c1] == -1) {
            if (c1 == c2 && (r2 == r1+1 || (r2 == r1+2 && r1== 1 && !board[r1+1][c1])))   // black moves 1 or possible 2 down
                return 1;
        } else {
            return not_pawns(c1, r1, c2, r2);
        }
    }    // end move

    // might happen in pawn failure
    return 0;
}





int main()
{

    // change the file name to board.csv    
    int fd = open("board.csv", O_RDWR);

    char buf[3] = {0};

    int i, j;

    for (i=0; i<8; ++i) {
        for (j=0; j<8; ++j) {
            read(fd, buf, 3);
            board[i][j] = (buf[0] == '-') ? -(buf[1] - '0') : buf[1] - '0';
            //fscanf("%d,", &board[i][j]);
        }
        //read(fd, buf, 2);
        //board[i][j] = (buf[0] == '-') ? -(buf[1] - '0') : buf[1] - '0';
        //fscanf("%d", &board[i][j]);
    }
    
   // printf("Welcome to the chess game!\n");
   //  printf("Commands are:\nmv (move)\ncp (capture)\nshow (display board)\nexit\n");

    char cmd[50] = {0};
    char c1, c2;
    int r1, r2;
    while (1) {

        scanf("%s", cmd);

        if (!strcmp(cmd, "mv")) {
            scanf(" %c%d %c%d", &c1, &r1, &c2, &r2);

            //printf("%d %d %d %d\n" , c1, r1, c2, r2);
            r1 = 8 - r1;
            r2 = 8 - r2;  // flip so rows go 0 - 7 down not 1 - 8 up
            c1 -= 'a';   // convert 'a'-'h' to 0 - 7
            c2 -= 'a';


            //printf("%d %d %d %d\n" , c1, r1, c2, r2);
            if (move(c1, r1, c2, r2, 0)) {
                lseek(fd, r1*24+c1*3, SEEK_SET);  // each row is 24 characters 2 per field + commas plus newline
                read(fd, buf, 2);  // read the piece characters 
                lseek(fd, r1*24+c1*3, SEEK_SET);  // go back
                write(fd, " 0", 2);    // overwrite where it was with an empty space

                lseek(fd, r2*24+c2*3, SEEK_SET);   // seek to where it's moving too
                write(fd, buf, 2);    // write piece to new location
                
                board[r2][c2] = board[r1][c1];   // update board array, move piece to new location
                board[r1][c1] = 0;    // clear out old position
            }

        } else if (!strcmp(cmd, "cp")) {
            scanf(" %c%d %c%d", &c1, &r1, &c2, &r2);
            r1 = 8 - r1;
            r2 = 8 - r2;  // flip so rows go 0 - 7 down not 1 - 8 up
            c1 -= 'a';
            c2 -= 'a';
            if (move(c1, r1, c2, r2, 1)) {
                lseek(fd, r1*24+c1*3, SEEK_SET);
                read(fd, buf, 2);
                lseek(fd, r1*24+c1*3, SEEK_SET);
                write(fd, " 0", 2);

                lseek(fd, r2*24+c2*3, SEEK_SET);
                write(fd, buf, 2);
                board[r2][c2] = board[r1][c1];
                board[r1][c1] = 0;
            }

        } else if (!strcmp(cmd, "show")) {

            for (i=0; i<8; ++i) {
                for (j=0; j<7; ++j) {
                
                    // to convert to tl5, just change putchar(' ') to printf("    ");
                    if (board[i][j] >= 0)
                        putchar(' ');
                    printf("%d,", board[i][j]);
                }
                if (board[i][j] >= 0)
                    putchar(' ');
                printf("%d\n", board[i][j]);
            }
        } else if (!strcmp(cmd, "exit")) {
            puts("Exiting...");
            break;
        } else {
            puts("Invalid command! only mv, cp, show and exit are valid.");
        }

    }


    close(fd);
    return 0;
}
