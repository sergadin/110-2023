#include <stdlib.h>
#include <math.h>
#include <stdio.h>
int check_tail(int user, int *pos, int **play_lists, int *lenghts, int n_users);
void find_order (int **play_lists, int *lenghts, int n_playlists);

int check_tail(int user, int *pos, int **play_lists, int *lenghts, int n_users){
    int value = play_lists[user][pos[user]];
    int u = 0;
    while (u < n_users){
        if (u != user){
            for (int i = pos[u] + 1; i < lenghts[u]; i++){
                if (play_lists[u][i] == value){
                    return 0;
                }
            }
        }
        u++;
    }
    return 1;
}

void find_order (int **play_lists, int *lenghts, int n_playlists){
    int *pos = (int *)malloc(n_playlists*sizeof(int));
    int curr = 0, if_print = 0;
    for (int k = 0; k < n_playlists; k++){
        pos[k] = 0;
    }
    do {
        if_print = 0;
    for (int user = 0; user < n_playlists; user++){
        if (pos[user] >= lenghts[user]){
            continue;
        }
        if(check_tail(user, pos, play_lists, lenghts, n_playlists)){
            if_print = 1;
            printf("%d",play_lists[user][pos[user]]);
            curr = play_lists[user][pos[user]];
            for (int n = 0; n < n_playlists; n++){
                if (play_lists[n][pos[n]] == curr){
                    pos[n]++;
                }
                
            }
        }
        
    } 
 
}while(if_print == 1);
printf("\n");
    
}

int main(void){
    int n_playlists = 3;
    int lenghts[] = {4,3,3};
    int p1[] = {1,3,7,6};
    int p2[] = {2,7,4};
    int p3[] = {5,1,6};
    
    int *play_lists[] = {p1, p2, p3};
    find_order(play_lists, lenghts, n_playlists);
    return 1;
}
