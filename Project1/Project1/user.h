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

//管理员系统完善：查看所有用户，删除用户，修改用户角色
void listUsers();
void deleteUser();
void changeUserRole();

//导出用户数据
void exportUsers();