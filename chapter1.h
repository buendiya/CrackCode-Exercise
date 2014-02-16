#ifndef CHAPTER1_H
#define CHPATER1_H

#include <iostream>
#include <string>
#include <map>

#include <cstring>

using namespace std;

bool isUniqueChar(string str)
{
	map<char, bool> char_set;

	for (unsigned i = 0; i < str.size(); i++)
	{
		if (char_set[str[i]]) return false;
		char_set[str[i]] = true;
	}
	return true;
}

/*
 * Implemented in c
 */
bool isUniqueCharsString2(char *str)
{
    unsigned int i;
    bool c[256];
    for(i = 0; i < 256; i++) c[i] = false; //initialize the array
    for(i = 0; i < strlen(str); i++)
    {
        if(c[(int)str[i]])
        	return false;
        c[(int)str[i]] = true;
    }
    return true;
}

void reverseString(char *str)
{
	char *end;
	char *start = str;
	char tmp;

	if (str)
	{
		end = str + (strlen(str) - 1);
		for( ; start < end; start++, end--)
		{
			tmp = *start;
			*start = *end;
			*end = tmp;
		}
	}
}

/*
 * No (Large) Additional Memory.
 * 1. For each character, check if it is a duplicate of already found characters.
 * 2. Skip duplicate characters and update non duplicate characters.
 */
void removeDuplicate(char *str)
{
	if (str == NULL)
		return;
	int len = strlen(str);
	if (len < 2)
		return;
	int tail = 0;	// To indicate the end of the non-duplicate string
	int j = 0;

	for (int i = 0; i < len; i++)
	{
		for (j = 0; j < tail; j++)
		{
			if (str[i] == str[j])	//If str[i] has been in non-duplicate string, break out of loop. And in such a case j != tail.
				break;
		}
		if (j == tail)
		{
			str[tail] = str[i];
			tail++;
		}
	}
	str[tail] = '\0';	//strlen return the length of c string without including the terminating null character
}

/*
 * With Additional Memory of Constant Size
 */
void removeDuplicate2(char *str)
{
	if (str == NULL)
		return;
	int len = strlen(str);
	if (len < 2)
		return;

	int tail = 0;
	bool *hit = new bool[256];
	for (int i = 0; i < 256; i++)
		hit[i] = false;

	for (int i = 0; i < len; i++)
	{
        if(hit[(int)str[i]])
        	continue;
        str[tail] = str[i];
        tail++;
        hit[(int)str[i]] = true;
	}
	str[tail] = '\0';
}

//1.4 Write a method to decide if two strings is anagram or not
/*
 * Solution 1: Sort the strings
 */
void stringSort(char *str);
bool anagram(char *str1, char *str2)
{
	if (str1 == NULL || str2 == NULL || strlen(str1) != strlen(str2))
		return false;

	stringSort(str1);
	stringSort(str2);
	if (!strcmp(str1, str2))
		return true;
	else
		return false;
}

void stringSort(char *str)
{
	char tmp;
	int j;

	for (unsigned i = 1; i < strlen(str); i++)
	{
		tmp = str[i];
		for (j = i; j>0 && str[j-1]>str[j]; j--)
		{
			str[j] = str[j-1];
		}
		str[j] = tmp;
	}
}

/*
 * Solution2: Check if the two stings have identical counts for each unique character.
 */
bool anagram2(char *str1, char*str2)
{
	if (str1 == NULL || str2 == NULL || strlen(str1) != strlen(str2))
		return false;

	int *count = new int[256];
	memset(count, 0, sizeof(int) * 256);

	for (int i = 0; str1[i] && str2[i]; i++)
	{
		count[(int)str1[i]]++;
		count[(int)str2[i]]--;
	}

	for (int i = 0; i < 256; i++)
	{
		if (count[i])
			return false;
	}
	return true;
}

//1.5. Write a method to replace all spaces in a string with '%20'.
/*
 * 1. Count the number of spaces during the first scan of the string.
 * 2. Parse the string again from the end. If a space is encountered, replace it with '%20'.
 */
void ReplaceFun(char *str)
{
	if (str == NULL)
		return;

	int len = strlen(str);
	int newlength = 0;
	int spaceCount = 0;

	for (int i = 0; i < len; i++)
	{
		if (str[i] == ' ')
			spaceCount++;
	}
	newlength = len + spaceCount * 2;

	str[newlength--] = '\0';
	for (int i = len - 1; i >= 0; i--)	//Traverse from the end, so the initial character won't be overridden.
	{
		if (str[i] == ' ')
		{
			str[newlength--] = '0';
			str[newlength--] = '2';
			str[newlength--] = '%';
		}
		else
		{
			str[newlength--] = str[i];
		}
	}
}

//1.6. Rotate a n*n matrix.
void RotateMatrix(int matrix[][4], int n)
{
	if (matrix == NULL)
		return;
	for (int layer = 0; layer < n / 2; layer++)
	{
		int first = layer;
		int last = n - layer -1;
		for (int i = first; i < last; i++)
		{
			int offset = i - first;
			int top = matrix[first][i];		//save top

			// left -> top
			matrix[first][i] = matrix[last-offset][first];

			// bottom -> left
			matrix[last-offset][first] = matrix[last][last - offset];

			// right -> bottom
			matrix[last][last - offset] = matrix[i][last];

			// top -> right
			matrix[i][last] = top; // right <- saved top
		}

	}
}

//1.7. Write an algorithm such that if an element in an M*N matrix is 0, its entire row and column is set to 0.
void SetZero(int matrix[][4])
{
	if (matrix == NULL)
		return;
	bool row[4] = {false};
	bool column[4] = {false};

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			if (matrix[i][j] == 0)
			{
				row[i] = true;
				column[j] = true;
			}
		}

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			if (row[i] == true || column[j] == true)
			{
				matrix[i][j] = 0;
			}
		}
}

//1.8  isRotation
/*
 * Check whether str1 is substring of str2.
 */
bool isSubstring(char *str1, char *str2);

/*
 * Check whether str1 is rotation of str2. isSubstring function can be used only once.
 * Concatenate str2 with itself, then check whether str1 is substring of str2.
 */
bool isRotation(char *str1, char *str2)
{
	if (str1 == NULL || str2 == NULL)
		return false;
	if (strlen(str1) != strlen(str2))
		return false;

	//Concatenate str2 with itself
	int len = strlen(str2);
	int j = len;
	for (int i = 0; i < len; i++, j++)
	{
		cout << str1[i];
		str2[j] = str2[i];
	}

	str2[j] = '\0';

	cout << "str1:" << str1 << " str2: " << str2 << endl;
	return isSubstring(str1, str2);
}

bool isSubstring(char *str1, char *str2)
{
	if (str1 == NULL || str2 == NULL)
		return false;

	unsigned j;
	unsigned str1len = strlen(str1);
	unsigned str2len = strlen(str2);

	for (unsigned i = 0; i < str2len; i++)
	{
		for (j = 0; j < str1len && str1[j] == str2[i+j]; j++)
			;
		if (j == str1len)
			return true;
	}
	return false;
}

#endif
