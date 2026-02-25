#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

#define USER_FILE "users.dat"

//注册功能
void registerUser() {
    FILE* fp = fopen(USER_FILE, "ab");
    if (fp == NULL) {
        printf("无法打开用户文件！\n");
        return;
    }

    User newUser;

    printf("输入用户名: ");
    scanf("%s", newUser.username);

    printf("输入密码: ");
    scanf("%s", newUser.password);

    printf("选择角色 (1=学生 2=教师 3=管理员): ");
    scanf("%d", &newUser.role);

    fwrite(&newUser, sizeof(User), 1, fp);
    fclose(fp);

    printf("注册成功！\n");
}

//登录功能
int loginUser() {
    FILE* fp = fopen(USER_FILE, "rb");
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

    User temp;

    while (fread(&temp, sizeof(User), 1, fp) == 1) {
        if (strcmp(username, temp.username) == 0 &&
            strcmp(password, temp.password) == 0) {

            fclose(fp);
            printf("登录成功！\n");
            return temp.role;
        }
    }

    fclose(fp);
    printf("用户名或密码错误。\n");
    return 0;
}