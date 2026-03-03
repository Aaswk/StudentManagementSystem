#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "file.h"
#include "user.h"

void studentMenu(Student* head);
void teacherMenu(Student* head);
void adminMenu(Student* head);

void showMenu() {
    printf("\n===== 学生管理系统 =====\n");
    printf("1. 添加学生\n");
    printf("2. 删除学生\n");
    printf("3. 修改学生\n");
    printf("4. 查询学生\n");
    printf("5. 显示全部学生\n");
    printf("6. 成绩升序排序\n");
    printf("7. 成绩降序排序\n");
    printf("8. 数据统计\n");
    printf("0. 退出系统\n");
    printf("请选择功能: ");
}

int main() {

    int choice;
    int role = 0;

    //第一阶段：登录注册界面
    while (1) {
        printf("\n===== 欢迎使用学生管理系统 =====\n");
        printf("1. 登录\n");
        printf("2. 注册\n");
        printf("0. 退出\n");
        printf("请选择: ");
        scanf("%d", &choice);

        if (choice == 0) {
            printf("系统退出。\n");
            return 0;
        }

        if (choice == 2) {
            registerUser();
        }

        if (choice == 1) {
            role = loginUser();
            if (role != 0) {
                break;
            }
        }
    }

    //第二阶段：初始化学生数据
    Student* head = initList();
    loadFromFile(head);

    //第三阶段：三端架构、角色控制
    if (role == 1) {
        studentMenu(head);
    }
    else if (role == 2) {
        teacherMenu(head);
    }
    else if (role == 3) {
        adminMenu(head);
    }

    saveToFile(head);
    return 0;
}

//学生端
void studentMenu(Student* head) {
    int choice;
    while (1) {
        printf("\n===== 学生端 =====\n");
        printf("1.成绩查询\n");
        printf("2.成绩分析\n");
        printf("0.返回上一级\n");
        printf("请选择：");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("进入成绩查询功能\n");
            break;
        case 2:
            printf("进入成绩分析功能\n");
            break;
        case 0:
            return;
        default:
            printf("无效输入。\n");
        }
    }
}

//教师端
void teacherMenu(Student* head) {
    int choice;
    while (1) {
        printf("\n===== 教师端 =====\n");
        printf("1.增删改查学生信息\n");
        printf("2.查看班内成绩\n");
        printf("3.成绩分析\n");
        printf("0.返回上一层\n");
        printf("请选择：");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("进入学生管理系统\n");
            break;
        case 2:
            printf("进入班内成绩查看\n");
            break;
        case 3:
            printf("进入成绩分析\n");
            break;
        case 0:
            return;
        default:
            printf("无效输入。\n");
        }
    }
}

//管理员端
void adminMenu(Student* head) {
    int choice;
    while (1) {
        printf("\n===== 管理员端 =====\n");
        printf("1.账号管理\n");
        printf("2.数据导入导出\n");
        printf("3.查看待办\n");
        printf("0.返回上一级\n");
        printf("请选择：");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("进入账号管理\n");
            break;
        case 2:
            printf("进入数据导入导出\n");
            break;
        case 3:
            printf("查看待办\n");
            break;
        case 0:
            return;
        default:
            printf("无效输入。\n");
        }
    }
}
