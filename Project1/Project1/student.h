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

// 增（尾插法）
void appendStudent(Student* head, Student* newStudent);

// 遍历
void printStudents(Student* head);

// 查
Student* findStudentById(Student* head, int id);

// 删
void deleteStudent(Student* head, int id);

// 改
void modifyStudent(Student* head, int id);

//排序
void sortStudents(Student* head, int ascending);//升序

//数据统计
void statistics(Student* head);