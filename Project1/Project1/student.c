#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

//初始化链表
Student* initList() {
    Student* head = (Student*)malloc(sizeof(Student));
    if (head == NULL) {
        printf("内存分配失败！\n");
        return NULL;
    }

    head->prev = NULL;
    head->next = NULL;

    return head;
}

//创建节点
Student* createStudent(int id, const char* name, int age, float score) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    if (newStudent == NULL) {
        printf("内存分配失败！\n");
        return NULL;
    }

    newStudent->id = id;
    strcpy(newStudent->name, name);
    newStudent->age = age;
    newStudent->score = score;

    newStudent->prev = NULL;
    newStudent->next = NULL;

    return newStudent;
}

//增（尾插法）
void appendStudent(Student* head, Student* newStudent) {
    Student* temp = head;

    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newStudent;
    newStudent->prev = temp;
}

//遍历
void printStudents(Student* head) {
    Student* temp = head->next;

    if (temp == NULL) {
        printf("暂无学生数据。\n");
        return;
    }

    printf("ID\t姓名\t年龄\t成绩\n");

    while (temp != NULL) {
        printf("%d\t%s\t%d\t%.2f\n",temp->id,temp->name,temp->age,temp->score);
        temp = temp->next;
    }
}

//查
Student* findStudentById(Student* head, int id) {
    Student* temp = head->next;

    while (temp != NULL) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->next;
    }

    return NULL;
}

//删
void deleteStudent(Student* head, int id) {
    Student* target = findStudentById(head, id);

    if (target == NULL) {
        printf("未找到该学生。\n");
        return;
    }

    target->prev->next = target->next;

    if (target->next != NULL) {
        target->next->prev = target->prev;
    }

    free(target);

    printf("删除成功。\n");
}

//改
void modifyStudent(Student* head, int id) {
    Student* target = findStudentById(head, id);

    if (target == NULL) {
        printf("未找到该学生。\n");
        return;
    }

    printf("输入新姓名: ");
    scanf("%s", target->name);

    printf("输入新年龄: ");
    scanf("%d", &target->age);

    printf("输入新成绩: ");
    scanf("%f", &target->score);

    printf("修改成功。\n");
}

//排序
void sortStudents(Student* head, int ascending) {
    if (head->next == NULL) {
        printf("没有学生数据可供排序。\n");
        return;
    }

    Student* i;
    Student* j;
    for (i = head->next; i->next != NULL; i = i->next) {
        for (j = head->next; j->next != NULL; j = j->next) {
            int condition;

            if (ascending) condition = j->score > j->next->score;
            else condition = j->score < j->next->score;

            if (condition) {
                // 保存
                int tempId = j->id;
                char tempName[50];
                strcpy(tempName, j->name);
                int tempAge = j->age;
                float tempScore = j->score;

                j->id = j->next->id;
                strcpy(j->name, j->next->name);
                j->age = j->next->age;
                j->score = j->next->score;

                j->next->id = tempId;
                strcpy(j->next->name, tempName);
                j->next->age = tempAge;
                j->next->score = tempScore;
            }
        }
    }

    printf("排序完成。\n");
}

//数据统计
void statistics(Student* head) {
    Student* temp = head->next;

    if (temp == NULL) {
        printf("暂无学生数据。\n");
        return;
    }

    int count = 0;
    float sum = 0;
    float max = temp->score;
    float min = temp->score;

    while (temp != NULL) {
        count++;
        sum += temp->score;

        if (temp->score > max) max = temp->score;
        if (temp->score < min) min = temp->score;

        temp = temp->next;
    }

    printf("学生总数: %d\n", count);
    printf("平均成绩: %.2f\n", sum / count);
    printf("最高成绩: %.2f\n", max);
    printf("最低成绩: %.2f\n", min);
}

//导出学生数据
void exportStudents(Student* head) {
    FILE* fp = fopen("students_export.txt", "w");
    if (fp == NULL) {
        printf("导出失败。\n");
        return;
    }
    Student* p = head->next;
    while (p) {
        fprintf(fp, "%d %s %d %.2f\n", p->id, p->name, p->age, p->score);
        p = p->next;
    }
    fclose(fp);
    printf("学生数据导出成功。\n");
}

//待办
void showTodoList(Student* head) {
    Student* p = head->next;
    int found = 0;

    printf("\n===== 待处理学生 (成绩 < 60) =====\n");
    while (p) {
        if (p->score < 60) {
            printf("%d %s %.2f\n",
                p->id, p->name, p->score);
            found = 1;
        }
        p = p->next;
    }
    if (!found)
        printf("暂无待处理学生。\n");
}
