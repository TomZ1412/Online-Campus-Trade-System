#pragma once

#include <iostream>
#include "sqlite3.h"

int create_product_database();
int create_user_database();
int create_student_database();
void addStudent(const std::string& name, const std::string& id);
int create_discussion_database();
int create_chat_database();
