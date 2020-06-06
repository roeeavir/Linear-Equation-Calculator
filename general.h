/*
 * general.h
 *
 *  Created on: Dec 13, 2019
 *      Author: roee
 */

#ifndef GENERAL_H_
#define GENERAL_H_

int eqSize();
char* initStr(int index);
int checkStr(char* str, int size);
void removeSpaces(char* str);
float setFloat(char* str, int* index, float num, int posOrNeg);
void printMat(float** mat, int size);
void printVecB(const float* arr, int size);
float getDet(float** mat, int size);
float cramMat(float** mat2, float** mat1, float* arr, int coef, int size);
void printVecX(const float* arr, int size);

#endif /* GENERAL_H_ */
