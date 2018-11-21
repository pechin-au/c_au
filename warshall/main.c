#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

struct relation{
	uint64_t * data;
	size_t size;
	size_t row_l;
};

size_t max(size_t a, size_t b){
	return (a > b) ? a : b;
}

size_t min(size_t a, size_t b){
	return (a < b) ? a : b;
}

void init_relation(struct relation * r, size_t size){
	r->size = size;
	r->row_l = ((r->size) / 64 + 1);
	r->data = (uint64_t*) malloc(r->row_l * sizeof(uint64_t) * size);
	memset((void*) r->data, 0, r->row_l * sizeof(uint64_t) * size);
}

void set_relation(struct relation * r, size_t i, size_t j){
	(*((r->data) + r->row_l * i + (j / 64))) |= ((((uint64_t) 1) << 63) >> (j % 64));
}

uint64_t get_relation(struct relation * r, size_t i, size_t j){
	return ((*((r->data) + r->row_l * i + (j / 64))) & 
			((((uint64_t) 1) << 63) >> (j % 64))) ? 1 : 0;
}

void print_relation(struct relation * r){
	int i, j;
	for (i = r->size-1; i >= 0; i--){
		printf("[ ");
		for (j = 0; j < r->size; j += 1){
			printf("%ld", get_relation(r, i, j));
		}
		printf(" ]\n");
	}
}

void read_relation(struct relation * r, FILE * f){
	size_t size;
	int i, j;
	char c;
	fscanf(f, "%zd", &size);
	init_relation(r, size);
	for (i = size-1; i >= 0; i--){
		fgetc(f);
		for (j = 0; j < size; j++){
			c = fgetc(f);
			if (c == '1'){
				set_relation(r, i, j);
			}
		}
		
	}
}

void warshall(struct relation * r){
	size_t i, j, k;
	for (k = 0; k < r->size; k++){
		for (i = 0; i < r->size; i++){
			for (j = 0; j < r->row_l; j++){
				(*((r->data) + i * r->row_l + j)) |= 
					((~((uint64_t) 0)) * get_relation(r, i, k)) &
					(*((r->data) + k * r->row_l + j));
			}
		}
	}
}

void free_relation(struct relation * r){
	r->size = 0;
	free(r->data);
}


int main(){
	struct relation r;
	FILE * f;
	f = fopen("rel.in", "r");
	read_relation(&r, f);
	fclose(f);
	print_relation(&r);
	warshall(&r);
	printf("\n");
	print_relation(&r);
	free_relation(&r);
	return 0;
}
