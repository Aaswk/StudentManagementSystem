#define _CRT_SECURE_NO_WARNINGS
//初始化链表
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

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

//尾插法
void appendStudent(Student* head, Student* newStudent) {
    Student* temp = head;

    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newStudent;
    newStudent->prev = temp;
}

//打印链表
void printStudents(Student* head) {
    Student* temp = head->next;

    if (temp == NULL) {
        printf("暂无学生数据。\n");
        return;
    }

    printf("ID\t姓名\t年龄\t成绩\n");

    while (temp != NULL) {
        printf("%d\t%s\t%d\t%.2f\n",
            temp->id,
            temp->name,
            temp->age,
            temp->score);

        temp = temp->next;
    }
}

//查找学生
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

//删除学生
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

//修改学生
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
