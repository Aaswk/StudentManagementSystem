#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "file.h"

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
    Student* head = initList();
    loadFromFile(head);
    int choice;

    while (1) {
        showMenu();
        scanf("%d", &choice);

        if (choice == 0) {
            saveToFile(head);
            printf("系统已退出。\n");
            break;
        }

        int id, age;
        float score;
        char name[50];

        switch (choice) {
        case 1:
            printf("输入学号: ");
            scanf("%d", &id);
            printf("输入姓名: ");
            scanf("%s", name);
            printf("输入年龄: ");
            scanf("%d", &age);
            printf("输入成绩: ");
            scanf("%f", &score);

            appendStudent(head, createStudent(id, name, age, score));
            printf("添加成功。\n");
            break;

        case 2:
            printf("输入要删除的学号: ");
            scanf("%d", &id);
            deleteStudent(head, id);
            break;

        case 3:
            printf("输入要修改的学号: ");
            scanf("%d", &id);
            modifyStudent(head, id);
            break;

        case 4:
        {
            printf("输入要查询的学号: ");
            scanf("%d", &id);
            Student* s = findStudentById(head, id);
            if (s != NULL) {
                printf("找到学生: %d %s %d %.2f\n",
                    s->id, s->name, s->age, s->score);
            }
            else {
                printf("未找到该学生。\n");
            }
            break;
        }

        case 5:
            printStudents(head);
            break;
        case 6:
            sortStudents(head, 1);
            printStudents(head);
            break;

        case 7:
            sortStudents(head, 0);
            printStudents(head);
            break;
        case 8:
            statistics(head);
            break;
        default:
            printf("无效输入，请重新选择。\n");
        }
    }

    return 0;
}