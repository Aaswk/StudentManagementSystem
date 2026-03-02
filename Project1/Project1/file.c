#include <stdio.h>
#include <stdlib.h>
#include "file.h"

#define DATA_FILE "students.dat"

//保存文件
void saveToFile(Student* head) {
    FILE* fp = fopen(DATA_FILE, "wb");//只写二进制
    if (fp == NULL) {
        printf("文件打开失败！\n");
        return;
    }

    Student* temp = head->next;

    while (temp) {
        fwrite(&(temp->id), sizeof(int), 1, fp);
        fwrite(temp->name, sizeof(char), 50, fp);
        fwrite(&(temp->age), sizeof(int), 1, fp);
        fwrite(&(temp->score), sizeof(float), 1, fp);

        temp = temp->next;
    }

    fclose(fp);
    printf("数据已保存到文件。\n");
}

//加载文件
void loadFromFile(Student* head) {
    FILE* fp = fopen(DATA_FILE, "rb");
    if (fp == NULL) {
        return;  // 第一次运行可能没有文件
    }

    int id, age;
    float score;
    char name[50];

    while (fread(&id, sizeof(int), 1, fp) == 1) {
        fread(name, sizeof(char), 50, fp);
        fread(&age, sizeof(int), 1, fp);
        fread(&score, sizeof(float), 1, fp);

        Student* newStudent = createStudent(id, name, age, score);
        appendStudent(head, newStudent);
    }

    fclose(fp);
}
