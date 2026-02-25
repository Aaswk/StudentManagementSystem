#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "student.h"

int main() {
    Student* head = initList();

    Student* s1 = createStudent(1, "Alice", 20, 88.5);
    Student* s2 = createStudent(2, "Bob", 21, 92.0);

    appendStudent(head, s1);
    appendStudent(head, s2);

    printStudents(head);

    return 0;
}