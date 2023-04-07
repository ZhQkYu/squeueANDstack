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
#include "squeue.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>


int main()
{
  Squeue *s1 = NULL;
  initSqueue(&s1);
  //Squeue should be empty
  assert(isEmpty(s1));
  addFront(s1, "aaaaaaaaaaaaaaaaaaaaaaa");
  //We just added "aaaaaaaaaaaaaaaaaaaaaaa", so it shouldn't be empty
  assert(!isEmpty(s1));
  addBack(s1, "bbbbbbbbbbbbbbbbbbbb!");
  //We should have "aaaaaaaaaaaaaaaaaaaaaaa", "bbbbbbbbbbbbbbbbbbbb!" in the Squeue in that order.
  assert(strcmp(peekFront(s1), "aaaaaaaaaaaaaaaaaaaaaaa") == 0);
  assert(strcmp(peekBack(s1), "bbbbbbbbbbbbbbbbbbbb!") == 0);
  //We are going to merge "aaaaaaaaaaaaaaaaaaaaaaa" with "bbbbbbbbbbbbbbbbbbbb!"
  mergeFront(s1, 'f');
  assert(strcmp(peekFront(s1), "aaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbb!") == 0);
  //We have only one element so the front and back of the squeue should be equal
  assert(strcmp(peekFront(s1), peekBack(s1)) == 0);
  addFront(s1, "Hola");
  addBack(s1, "Mundo!");
  // this print call should print
    //squeue is:
    //  Hola
    //  aaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbb
    //  Mundo!
  print(s1, 'f');
  reverse(s1);//we now reversed the elements in the stack
  assert(strcmp(peekFront(s1), "Mundo!") == 0);
  assert(strcmp(peekBack(s1), "Hola") == 0);
  // We are printing the stack in reverse order so we should get:
    //squeue is:
    //  Hola
    //  aaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbb
    //  Mundo!
  print(s1, 'r');
  leaveFront(s1);
  assert(strcmp(peekFront(s1), "aaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbb!") == 0);
  nuke(s1);
  //We just nuked our Squeue, so it should be empty
  assert(isEmpty(s1));
  destroySqueue(&s1);
  //After destroying the stack, s1 must be NULL
  assert(s1 == NULL);
  return 0;
}
