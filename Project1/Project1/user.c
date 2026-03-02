#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

#define USER_FILE "users.dat"

//密码加密
void encrypt(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = str[i] + 3;
    }
}

//注册功能
void registerUser() {
    //需两次打开文件，第一次只读（检查用户是否重复），第二次追加

    //第一次打开
    FILE* fp = fopen(USER_FILE, "rb");//只读二进制
    User temp;
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    int role;

    printf("输入用户名：");
    scanf("%s",username);

    //检查是否已经存在
    if (fp != NULL) {
        while (fread(&temp, sizeof(User), 1, fp) == 1) {
            if (strcmp(username, temp.username) == 0) {
                printf("用户名已存在，注册失败。\n");
                fclose(fp);
                return;
            }
        }
        fclose(fp);
    }

    printf("输入密码：");
    scanf("%s", password);
    encrypt(password);
    printf("选择角色（1=学生 2=教师 3=管理员）：");
    scanf("%d", &role);

    //第二次打开
    fp = fopen(USER_FILE, "ab");
    if (fp == NULL) {
        printf("无法打开文件。\n");
        return;
    }

    User newUser;
    strcpy(newUser.username, username);
    strcpy(newUser.password, password);
    newUser.role = role;

    fwrite(&newUser, sizeof(User), 1, fp);
    fclose(fp);

    printf("注册成功！\n");
}

//登录功能
int loginUser() {
    FILE* fp = fopen(USER_FILE, "rb");//只读二进制
    if (fp == NULL) {
        printf("暂无用户，请先注册。\n");
        return 0;
    }

    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];

    printf("输入用户名: ");
    scanf("%s", username);

    printf("输入密码: ");
    scanf("%s", password);
    encrypt(password);

    User temp;

    while (fread(&temp, sizeof(User), 1, fp) == 1) {
        if (strcmp(username, temp.username) == 0 && strcmp(password, temp.password) == 0) {
            fclose(fp);
            printf("登录成功！\n");
            return temp.role;
        }
    }

    fclose(fp);
    printf("用户名或密码错误。\n");
    return 0;
}