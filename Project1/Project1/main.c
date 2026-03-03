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
        case 1: {
            int id;
            printf("输入你的学号：");
            scanf("%d", &id);
            Student* s = findStudentById(head, id);
            if (s != NULL) {
                printf("学号：%d 姓名：%s 年龄：%d 成绩：%.2f\n", s->id, s->name, s->age, s->score);
            }
            else{
                printf("未找到该学生信息。\n");
            }
            break;
        }
        case 2:
            statistics(head);
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
        case 1: {
            int option;
            while (1) {
                printf("\n--- 学生管理 ---\n");
                printf("1.添加\n");
                printf("2.删除\n");
                printf("3.修改\n");
                printf("4.查询\n");
                printf("5.显示全部\n");
                printf("0.返回\n");
                printf("请选择：");
                scanf("%d", &option);

                if (option == 0) break;
                switch (option) {
                case 1: {
                    int id, age;
                    float score;
                    char name[50];

                    printf("输入学号：");
                    scanf("%d", &id);
                    printf("输入姓名：");
                    scanf("%s", &name);
                    printf("输入年龄：");
                    scanf("%d", &age);
                    printf("输入成绩：");
                    scanf("%.2f", &score);

                    appendSutdent(head, createStudent(id, name, age, score));
                    printf("添加成功。\n");
                    break;
                }
                case 2: {
                    int id;
                    printf("输入学号：");
                    scanf("%d", &id);
                    deleteStudent(head, id);
                    break;
                }
                case 3: {
                    int id;
                    printf("输入学号：");
                    scanf("%d", &id);
                    modifyStudent(head, id);
                    break;
                }
                case 4: {
                    int id;
                    printf("输入学号：");
                    scanf("%d", &id);
                    Student* s = findStudentById(head, id);
                    if (s) {
                        printf("%d %s %d %.2f\n", s->id, s->name, s->age, s->score);
                    }
                    else {
                        printf("未找到。\n");
                    }
                    break;
                }
                case 5:
                    printStudents(head);
                    break;
                default:
                    printf("无效输入。\n");
                }
            }
        }
        case 2:
            printStudents(head);
            break;
        case 3:
            statistics(head);
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
        case 1: {
            int option;
            while (1) {
                printf("\n--- 账号管理 ---\n");
                printf("1.查看用户\n");
                printf("2.删除用户\n");
                printf("3.修改用户角色\n");
                printf("0.返回\n");
                printf("请选择：");
                scanf("%d", &option);

                if (option == 0) break;
                switch (option) {
                case 1:
                    listUsers();
                    break;
                case 2:
                    deleteUser();
                    break;
                case 3:
                    changeUserRole();
                    break;
                default:
                    printf("无效输入。\n");
                }
            }
            break;
        }
        case 2: {
            int option;
            while (1) {
                printf("\n--- 数据导入导出 ---\n");
                printf("1.导出学生数据\n");
                printf("2.导出用户数据\n");
                printf("0.返回\n");
                printf("请选择：");
                scanf("%d", &option);

                if (option == 0) break;
                switch (option) {
                case 1:
                    exportStudents(head);
                    break;
                case 2:
                    exportUsers();
                    break;
                default:
                    printf("无效输入。\n");
                }
            }
        }   
            break;
        case 3:
            showTodoList(head);
            break;
        case 0:
            return;
        default:
            printf("无效输入。\n");
        }
    }
}
