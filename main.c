#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

extern int mult(int, int);
extern int sum(int, int);

int main() {
	int x, y;
	void *handle;
	int (*func)(int, int);
	char* error;

	scanf("%d %d", &x, &y);

	printf("Result from static lib: %d * %d = %d\n", x, y, mult(x, y));
	printf("Result from first dynamic lib: %d + %d = %d\n", x, y, sum(x, y));

	handle = dlopen("libdynamic_second.so", RTLD_LAZY);
	if (!handle) {
		fputs(dlerror(), stderr);
		exit(1);
	}
	func = dlsym(handle, "sub");
	printf("Result from second dynamic lib: %d - %d = %d\n", x, y, (*func)(x, y));
	dlclose(handle);
}