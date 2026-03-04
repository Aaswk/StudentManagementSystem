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

//查看所有用户
void listUsers() {
    FILE* fp = fopen(USER_FILE, "rb");
    if (fp == NULL) {
        printf("暂无用户。\n");
        return;
    }
    User temp;
    printf("\n===== 用户列表 =====\n");
    while (fread(&temp, sizeof(User), 1, fp) == 1) {
        printf("用户名：%s  角色：%d\n", temp.username, temp.role);
    }
    fclose(fp);
}

//删除用户（学习临时文件覆盖法）
void deleteUser() {
    char username[USERNAME_LEN];
    printf("输入要删除的用户名：");
    scanf("%s", username);

    FILE* fp = fopen(USER_FILE, "rb");
    if (fp == NULL) {
        printf("文件不存在。\n");
        return;
    }

    FILE* tempFile = fopen("data/temp.dat", "wb");
    User temp;
    int found = 0;
    while (fread(&temp, sizeof(User), 1, fp) == 1) {
        if (strcmp(temp.username, username) != 0) {
            fwrite(&temp, sizeof(User), 1, tempFile);
        }
        else {
            found = 1;
        }
    }
    fclose(fp);
    fclose(tempFile);
    remove(USER_FILE);
    rename("temp.dat", USER_FILE);

    if (found) printf("删除成功。\n");
    else printf("未找到该用户。\n");
}

//修改用户角色
void changeUserRole() {
    char username[USERNAME_LEN];
    printf("输入要修改的用户名：");
    scanf("%s", username);

    FILE* fp = fopen(USER_FILE, "rb");
    if (fp == NULL) {
        printf("文件不存在。\n");
        return;
    }

    FILE* tempFile = fopen("data/temp.dat", "wb");
    User temp;
    int found = 0;
    while (fread(&temp, sizeof(User), 1, fp) == 1) {
        if (strcmp(temp.username, username) == 0) {
            printf("当前角色：%d\n", temp.role);
            printf("输入新角色（1=学生 2=老师 3=管理员）：");
            scanf("%d", &temp.role);
            found = 1;
        }
        fwrite(&temp, sizeof(User), 1, tempFile);
    }
    fclose(fp);
    fclose(tempFile);
    remove(USER_FILE);
    rename("temp.dat", USER_FILE);

    if (found) printf("修改成功。\n");
    else printf("未找到该用户。\n");
}

//导出用户数据
void exportUsers() {
    FILE* fp = fopen(USER_FILE, "rb");
    if (fp == NULL) {
        printf("暂无用户数据。\n");
        return;
    }
    FILE* out = fopen("data/users_export.txt", "w");

    User temp;
    while (fread(&temp, sizeof(User), 1, fp) == 1) {
        fprintf(out, "%s %d\n",temp.username, temp.role);
    }
    fclose(fp);
    fclose(out);
    printf("用户数据导出成功。\n");
}
