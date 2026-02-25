#pragma once

#define USERNAME_LEN 50
#define PASSWORD_LEN 50

typedef struct User {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    int role;   // 1=学生 2=教师 3=管理员
} User;

void registerUser();
int loginUser();