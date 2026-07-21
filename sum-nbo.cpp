#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <netinet/in.h>

int main(int argc, char* argv[]) {
	if (argc != 4) {
		printf("need 3 arguments\n");
		return 1;
	}

	uint32_t to_add[3] = { 0x0, 0x0, 0x0};
	for (int i = 0; i < 3; i++) {
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
		fclose(fp);
	}
	
	uint32_t sum_hbo = to_add[0] + to_add[1] + to_add[2];
	printf("%d(0x%x) + %d(0x%x) + %d(0x%x) = %d(0x%x)\n", to_add[0], to_add[0], to_add[1], to_add[1], to_add[2], to_add[2], sum_hbo, sum_hbo);
	return 0;
}
