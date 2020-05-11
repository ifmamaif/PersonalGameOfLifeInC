#include "ExpectedOut.h"

#include <stdio.h>

int get_file_size(FILE* file);

int VerifyOutput(const char* filePath1, const char* filePath2)
{
	FILE* file1 = NULL;
	FILE* file2 = NULL;
		
	errno_t error1 = fopen_s(&file1, filePath1, "r");
	errno_t error2 = fopen_s(&file2, filePath2, "r");
	if (error1 == EOF ||
		error2 == EOF ||
		file1 == NULL ||
		file2 == NULL)
	{
		return 0;
	}

	auto fileSize1 = get_file_size(file1);
	auto fileSize2 = get_file_size(file2);

	if (fileSize1 != fileSize2)
	{
		fclose(file1);
		fclose(file2);
		return 0;
	}

	char c1=0, c2=0;
	do
	{
		error1 = fscanf_s(file1, "%c", &c1, 1);
		error2 = fscanf_s(file2, "%c", &c2, 1);
	} while (c1 == c2 && error1 == error1 && error1 > 0);

	fclose(file1);
	fclose(file2);
	return c1 == c2;
}


int get_file_size(FILE* file) // path to file
{
	if (file == NULL)
	{
		return -1;
	}

	auto currPos = fseek(file, 0, SEEK_CUR);

	fseek(file, 0, SEEK_END);
	auto size = ftell(file);

	fseek(file, size - currPos, SEEK_CUR);

	return size;
}
