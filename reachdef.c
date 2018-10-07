#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#define set(_x,_y) (_x&(1<<(_y-1)))
int set_num(int x, int y){
    return (x | (1 << (y - 1)));
}

int test_num(int x, int y){
    return (x & (1 << (y-1)));
}

void binary(int a, char* b){
    int start = 0;
    char buffer[100];
    while(a != 0 & start < 100){
        int temp = a & 1;
        if (temp == 1){
            buffer[start++] = '1';
        }else{
            buffer[start++] = '0';
        }
        a = a >> 1;
    }
    for(int i = 1; i <= start; i++){
        b[i - 1] = buffer[start - i];
    }
    b[start] = '\0';
}
//char buf[100];
int GEN[100];
int KILL[100];
int SUC[100];
int PRE[100];
int IN[100];
int OUT[100];
int main(){
    freopen("temp.txt","r",stdin);
    int block_num = 0; // The number of basic block
    int def_num = 0; // The number of Definition
    //Read Def and Kill set
    scanf("%d%d", &block_num,  &def_num);
    for(int i = 1; i <= block_num; i++){
        int gen_num = 0;
        int kill_num = 0;
        int gen = 0;
        int kill = 0;
        scanf("%d%d",&gen_num, &kill_num);
        for(int j = 0; j < gen_num; j++){
            int temp;
            scanf("%d", &temp);
            gen = set_num(gen, temp);
        }
        for(int j = 0; j < kill_num; j++){
            int temp;
            scanf("%d",&temp);
            kill = set_num(kill, temp);
        }
        GEN[i] = gen;
        KILL[i] = kill;
    }
    
    //Read Precessor of Basic Block
    for(int i = 1; i <= block_num; i++){
        int num = 0;
        int ans = 0;
        scanf("%d", &num);
        for(int j = 0; j < num; j++){
            int temp = 0;
            scanf("%d", &temp);
            ans = set_num(ans, temp);
        }
        //printf("%d\n", ans);
        PRE[i] = ans;
    }

    //Print Def and Kill set, and PRE
    for(int i = 1; i <= block_num; i++){
       char gen_buffer[50];
       char kill_buffer[50];
       char pre_buffer[50];
       memset(gen_buffer, 0, sizeof(gen_buffer));
       memset(kill_buffer, 0, sizeof(kill_buffer));
       memset(pre_buffer, 0, sizeof(pre_buffer));
       binary(GEN[i],gen_buffer);
       binary(KILL[i],kill_buffer);
       printf("Block(%d), Gen: %s, Kill: %s PRE: ", i, gen_buffer, kill_buffer);
       for(int j = 1; j <= block_num; j++){
           //printf("%d",i);
           //printf("%d, %d\n",PRE[i],j);
           if (test_num(PRE[i], j) != 0){
               printf("Block(%d), ", j);
           }
       }
       printf("\n");
    }
    //Calculate IN and OUT
    int change = 1;
    while(change == 1){
        change = 0;
        for(int i = 1; i <= block_num; i++){
            //Calculate IN
            int temp_in = 0;
            for(int j = 1; j <= block_num; j++){
                if (test_num(PRE[i],j)){
                    temp_in |= OUT[j];
                }
            }
            IN[i] = temp_in;

            //Calculate OUT
            int temp_out = 0;
            temp_out = GEN[i] | (IN[i] & (~KILL[i]));
            if (temp_out != OUT[i]){
                change = 1;
                OUT[i] = temp_out;
            }
        }
    }
    
    //Print IN OUT
    printf("\nResult: \n");
    for(int i = 1; i <= block_num; i++){
       char in_buffer[50];
       char out_buffer[50];
       printf("Block(%d): \n",i);
       //Print IN
       printf("IN: ");
       for(int j = 1; j <= def_num; j++){
           if (test_num(IN[i],j) != 0){
               printf("d%d, ",j);
           }
       }
       printf("\n");

       //Print OUT
       printf("OUT: ");
       for(int j = 1; j <= def_num; j++){
           if (test_num(OUT[i],j) != 0){
               printf("d%d, ",j);
           }
       }
       printf("\n");
       printf("\n");
    }

    return 0;
}