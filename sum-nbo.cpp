#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <netinet/in.h>

int main(int argc, char* argv[]) {
	if (argc == 1) {
		printf("need more arguments\n");
		return 1;
	}

	uint32_t to_add;
	uint32_t total = 0x0;
	for (int i = 0; i < argc - 1; i++) {
		FILE* fp = fopen(argv[i + 1], "rb");
		if (fp == nullptr) {
			printf("file open error\n");
			return 1;
		}

		if(fread(&to_add, sizeof(to_add), 1, fp) != 1) {
			printf("error\n");
			fclose(fp);
			return 1;
		}
		to_add = ntohl(to_add);
		total = total + to_add;
		if (i == 0) printf("%d(0x%x)", to_add, to_add);
		else printf(" + %d(0x%x)", to_add, to_add);
		fclose(fp);
	}
	
	printf(" = %d(0x%x)\n", total, total);
	return 0;
}
