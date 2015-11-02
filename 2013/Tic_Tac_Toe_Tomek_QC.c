//
//  main.c
//  hello_c
//
//  Created by grs on 15/3/12.
//  Copyright (c) 2015年 grs. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

/**
 * 从指定文件中读取 二维字符数组 4*4
 * 将单字符 'X', 'O', 'T', '.' ，分别用 1, -1, 2, 0 代替
 *
 * @return 代替后的 二维数组指针
 */
int** get_file_2arr_int(FILE * fp){
    
    int ** file_2arr;
    file_2arr = ( int** ) malloc( 4 * sizeof( int* ) );
    for(int i = 0 ; i < 4; i++ ){
        file_2arr[i] = ( int* )malloc(4*sizeof(int));
    }
    
    int text_char;
    text_char = fgetc(fp);
    int char_count = 1;
    int row = 0;
    int col = 0;
    while (text_char != EOF && char_count <= 20) {
        if (text_char == '\n') {
            row++;
            col = 0;
        }else{
            
            if (text_char == 'X') {
                file_2arr[row][col] = 1;
                
            }else if (text_char == 'O'){
                file_2arr[row][col] = -1;
                
            }else if (text_char == '.'){
                file_2arr[row][col] = 0;
                
            }else{
                file_2arr[row][col] = 2;
            }
            
            col++;
        }
        
        text_char = fgetc(fp);
        char_count++;
    }
    
    return file_2arr;
}


/**
 * 判断一个二维矩阵的结果
 *
 * 若横、竖、斜，某一个的值为 4，或-4，则其中一方胜；
 *
 */
char* judge_winner(int ** arr_2d){
    
    int res;
    char* xwin = "X won";
    char* Owin = "O won";
    char* no_winner = "";
    
    for (int row = 0; row <= 3; row++) {
        for (int col = 0; col <= 3; col++) {
//            printf("%d", arr_2d[row][col]);
        }
//        printf("\n");
    }
    
    // 横向
    for (int row = 0; row <= 3; row++) {
        res = arr_2d[row][0] + arr_2d[row][1] + arr_2d[row][2] + arr_2d[row][3];
        
//        printf("%d| ", res);
        if (res == 4) {
            return xwin;
        }
        if (res == -4) {
            return Owin;
        }
    }
    
//    printf("\n");
    // 竖向
    for (int col = 0; col <= 3; col++) {
        res = arr_2d[0][col] + arr_2d[1][col] + arr_2d[2][col] + arr_2d[3][col];
        
//        printf("%d| ", res);
        if (res == 4) {
            return xwin;
        }
        if (res == -4) {
            return Owin;
        }
    }
    
//    printf("\n");
    // 斜向
    res = arr_2d[0][0] + arr_2d[1][1] + arr_2d[2][2] + arr_2d[3][3];
//    printf("%d| ", res);
    if (res == 4) {
        return xwin;
    }
    if (res == -4) {
        return Owin;
    }
    
//    printf("\n");
    // 斜向
    res = arr_2d[0][3] + arr_2d[1][2] + arr_2d[2][1] + arr_2d[3][0];
//    printf("%d| ", res);
    if (res == 4) {
        return xwin;
    }
    if (res == -4) {
        return Owin;
    }
    
    return no_winner;
}

/**
 * 在 judge_winner 之后调用，判断游戏未完，还是平局
 *
 * 若有一个为0，则游戏未结束；
 * 否则为平局
 *
 */
char* judge_state(int ** arr_2d){
    char* NotOver = "Game has not completed";
    char* Draw = "Draw";


    // 判断是否游戏未结束
    for (int row = 0; row <= 3; row++) {
        for (int col = 0; col <= 3; col++) {
            if (arr_2d[row][col] == 0) {
                return NotOver;
            }
        }
    }
    
    return Draw;
}


/**
 * 从文件获取内容 4*4 矩阵数据，并输出该矩阵代表的游戏的游戏状态
 */
char* get_file_content_judge_2arr(FILE * fp){
    
    int ** tttt_2arr;
    int ** tttt_1;
    int ** tttt_2;
    char* the_winner;
    
    tttt_1 = ( int** ) malloc( 4 * sizeof( int* ) );
    for(int i = 0 ; i < 4; i++ ){
        tttt_1[i] = ( int* )malloc(4*sizeof(int));
    }
    
    tttt_2 = ( int** ) malloc( 4 * sizeof( int* ) );
    for(int i = 0 ; i < 4; i++ ){
        tttt_2[i] = ( int* )malloc(4*sizeof(int));
    }
    
    tttt_2arr = get_file_2arr_int(fp);
    
    for (int row = 0; row <= 3; row++) {
        for (int col = 0; col <= 3; col++) {
            if (tttt_2arr[row][col] == 2) {
                tttt_1[row][col] = 1;
                tttt_2[row][col] = -1;
            }else{
                tttt_1[row][col] = tttt_2arr[row][col];
                tttt_2[row][col] = tttt_2arr[row][col];
            }
            
        }
    }
    
    
    the_winner = judge_winner(tttt_1);
    if (strlen(the_winner) > 0) {
        return the_winner;
    }
    
//    printf("\n[ another ]\n");
    the_winner = judge_winner(tttt_2);
    if (strlen(the_winner) > 0) {
        return the_winner;
    }
    
    the_winner = judge_state(tttt_2arr);
    return the_winner;
}

/**
 * 主函数
 */
int main(int argc, const char * argv[]) {
    
    
    FILE *fp;
    int num;
    char ch_tmp;
    char* result;
    
    fp = fopen("/Users/grs/Documents/c_program/hello_c/A-large-practice.in", "r");
    if (fp == NULL) {
        exit(1);
    }
    
    fscanf(fp, "%d", &num);
//    printf("%d", num);
    
    ch_tmp = fgetc(fp);
//    printf("%c", ch_tmp);

    for (int cnt = 1; cnt <= num; cnt++) {
        result = get_file_content_judge_2arr(fp);
        printf("Case #%d: %s\n", cnt, result);

    }
    
    fclose(fp);
    
    return 0;
}



