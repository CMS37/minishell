#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main() {
	char	*file = "/User/hwang-youngseo";
	if (access(file, F_OK) == 0) {
		printf("File exists\n");
		if (access(file, X_OK) == 0) {
			printf("File is executable\n");
		} else {
			printf("%s: is a directory\n", file);
		}
	} else {
		printf("File does not exist\n");
	}
	return 0;
} // end of main