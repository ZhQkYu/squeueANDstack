/***
 * CMPUT 201 Student Submission License Version 2.0
 * Copyright 2023 student name
 * Unauthorized redistribution is forbidden under all circumstances. Use of this software without explicit authorization from the author and the CMPUT 201 Instructor is prohibited.
 * This software was produced as a solution for an assignment or lab in the course CMPUT 201 - Practical Programming Methodology at the University of Alberta, Canada. This solution is confidential and remains confidential after it is submitted for grading. The course staff has the right to run plagiarism-detection tools on any code developed under this license, even beyond the duration of the course.
 * Copying any part of this solution without including this copyright notice is illegal.
 * If any portion of this software is included in a solution submitted for grading at an educational institution, the submitter will be subject to the plagiarism sanctions at that institution.
 * This software cannot be publicly posted under any circumstances, whether by the original student or by a third party. If this software is found in any public website or public repository, the person finding it is kindly requested to immediately report, including the URL or other repository locating information, to the following email addresses:
 *
 *           hktang@ualberta.ca
 ***/
#include "bucketstack.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main()
{
  //We will have two stacks
  Stack *s1 = NULL;
  Stack *s2 = NULL;
  initStack(5, &s1);
  initStack(3, &s2);
  push("uno", s1);
  push("dos", s1);
  //s1 now has "dos" and "uno" in that order
  assert(strcmp("dos", top(s1)) == 0);
  //s2 is empty at this moment
  assert(isEmpty(s2));
  push("tres", s2);
  //We just added "tres" in s2
  assert(strcmp("tres", top(s2)) == 0);
  assert(size(s1) == 2);
  assert(size(s2) == 1);
  //Time to swap "dos" and "uno"
  swap(s1);
  //s1 now has "uno" and "dos" in that order
  assert(strcmp("uno", top(s1)) == 0);
  //Let's add 3 elements to each stack
  //after this for loop, s1 will have "hola", "hola", "hola", "uno",
  //"dos" in that order
  //after this for loop, s2 will have "mundo!", "mundo!", "mundo!", "tres"
  //in that order
  for(int i = 0; i < 3; i++) {
    push("hola", s1);
    push("mundo!", s2); 
  }
  print(s1);
  print(s2);

  //let's add 97 elements to each stack
  for(int i = 0; i < 97; i++) {
    push("hola", s1);
    push("mundo!", s2);
  }

  assert(size(s1) == 102);
  assert(size(s2) == 101);
  //s1 should have "hola" at the top
  assert(strcmp(top(s1), "hola") == 0);
  //s2 should have "mundo!" at the top
  assert(strcmp(top(s2), "mundo!") == 0);
  
  //at this point, s1 has 100 "hola" at the top so let's pop them
  //at this point, s2 has 100 "mundo!" at the top so let's pop them
  for(int i = 0; i < 100; i++) {
    assert(strcmp(top(s1), "hola") == 0);
    pop(s1);
    assert(strcmp(top(s2), "mundo!") == 0);
    pop(s2);
  }
 
  //s1 still has the uno and dos at the top and s2 still
  //has tres at the top. Let's use clear to clear all remaining
  //elements on each stack
  clear(s1);
  clear(s2);

  //both stacks must be empty after clear
  assert(isEmpty(s1));
  assert(isEmpty(s2));
  
  destroyStack(&s1);
  assert(s1 == NULL);
  
  destroyStack(&s2);
  assert(s2 == NULL);
  return 0;
}
