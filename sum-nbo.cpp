#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <netinet/in.h>

int main(int argc, char* argv[]) {
	if (argc == 1) {
		printf("need more arguments\n");
		return 1;
	}

	uint32_t to_add[3] = { 0x0, 0x0, 0x0};
	uint32_t total = 0x0;
	for (int i = 0; i < argc - 1; i++) {
		FILE* fp = fopen(argv[i + 1], "rb");
		if (fp == nullptr) {
			printf("file open error\n");
			return 1;
		}

		if(fread(&to_add[i], sizeof(to_add[i]), 1, fp) != 1) {
			printf("error\n");
			fclose(fp);
			return 1;
		}
		to_add[i] = ntohl(to_add[i]);
		total = total + to_add[i];
		if (i == 0) printf("%d(0x%x)", to_add[i], to_add[i]);
		else printf(" + %d(0x%x)", to_add[i], to_add[i]);
		fclose(fp);
	}
	
	printf(" = %d(0x%x)\n", total, total);
	return 0;
}
