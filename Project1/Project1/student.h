#pragma once
#define NAME_LEN 50

// 学生结构体（双向链表）
typedef struct Student {
    int id;
    char name[NAME_LEN];
    int age;
    float score;

    struct Student* prev;
    struct Student* next;
} Student;

// 初始化链表（创建头节点）
Student* initList();

// 创建新节点
Student* createStudent(int id, const char* name, int age, float score);

// 尾插法添加学生
void appendStudent(Student* head, Student* newStudent);

// 遍历打印所有学生
void printStudents(Student* head);

// 按ID查找学生
Student* findStudentById(Student* head, int id);

// 删除学生
void deleteStudent(Student* head, int id);

// 修改学生
void modifyStudent(Student* head, int id);
