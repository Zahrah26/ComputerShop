//Shreya Doorgachurn 2312862

#ifndef USER_MANAGEMENT_H
#define USER_MANAGEMENT_H

typedef struct {
    int id;
    char name[50];
    char email[50];
    char phone[15];
} User;

void addUser();
void viewUsers();
void updateUser();
void deleteUser();
void UserMenu();

#endif // USER_MANAGEMENT_H
