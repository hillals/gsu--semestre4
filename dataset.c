#include"dataset.h"
#include<stdio.h>
#include<stdlib.h>
#define SIZE 1360
void read_house_data(char* filename, House houses[]) {
	printf("Reading file %s\n", filename);
	// TODO
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		printf("DOSYA ACÝLAMADÝ\n");
	}
	char str[180];
	fgets(str, sizeof(str), file);
	const char s[2] = ",";
	char *token;

	/* get the first token */
	token = strtok(str, s);

	/* walk through other tokens */
	int j = 0;
	while (str != NULL) {
		int i = 0;
		while (token != NULL) {
			if (i == 0) {
				houses[j].id = atoi(token);
			}
			if (i == 1) {
				houses[j].lotarea = atoi(token);
			}
			if (i == 2) {
				strcpy(houses[j].street, token);
			}
			if (i == 3)
				houses[j].saleprice = atoi(token);
			if (i == 4)
				strcpy(houses[j].neighborhood, token);
			if (i == 5)
				houses[j].yearbuilt = atoi(token);
			if (i == 6)
				houses[j].overallqual = atoi(token);
			if (i == 7)
				houses[j].overallcond = atoi(token);
			if (i == 8)
				strcpy(houses[j].kitchenqual, token);

			token = strtok(NULL, s);
			i++;
		}
		fgets(str, sizeof(str), file);
		j++;
	}
	/*int i;
	 // 1'den baþla
	 for(i=1;i<SIZE;i++){
	 fscanf(file,"%d,%d,%s,%d,%s,%d,%d,%d,%d\n",&houses[i]->id,&houses[i]->lotarea,&houses[i]->street,&houses[i]->saleprice,&houses[i]->neighborhood,&houses[i]->yearbuilt,&houses[i]->overallqual,&houses[i]->overallcond,&houses[i]->kitchenqual);
	 }
	 */
	return;
}

void print_house(House house) {
	printf("Print House dataset\n");
	// TODO
	printf("ID: %d\n", house.id);
	printf("Lot Area: %d\n", house.lotarea);
	printf("Street: %s\n", house.street);
	printf("Sale Price: %d\n", house.saleprice);
	printf("Neighborhood: %s\n", house.neighborhood);
	printf("Year Built: %d\n", house.yearbuilt);
	printf("OverallQual: %d\n", house.overallqual);
	printf("OverallCond: %d\n", house.overallcond);
	printf("KitchenQual: %s\n", house.kitchenqual);
	return;
}

House get_house_byid(int id, House houses[]) {
	printf("Get house with id %d \n", id);
	// TODO
	int i;
	House searched;
	for (i = 0; i < SIZE; i++) {
		if (houses[i].id == id) {
			searched = houses[i];
		}
	}

	return searched;
}

House* get_neighborhoods(House house, House houses[]) {
	printf("Get neighborhoods of house with id %d\n", house.id);
	// TODO
	House *nghbr;
	nghbr=malloc(size_of(house)*1);
	int i;
	int j = 0;
	for (i = 0; i < SIZE; i++) {
		while(strcmp(houses[i].neighborhood, house.neighborhood) == 0) {
			nghbr=realloc(nghbr,sizeof(house)*1);
			nghbr[j] = houses[i];
			j++;

		}
	}
	return nghbr;
}


float mean_sale_prices(House* houses, char* criter_name) {
	printf("Calculate mean sale prices by %s \n", criter_name);
	// TODO
	float toplam = 0;
	if (strcmp(criter_name, "yearbuilt") == 0) {
		int i;
		int size = sizeof(houses) / sizeof(houses[0]);
		for (i = 0; i < size; i++) {
			toplam += houses[i].saleprice;
		}
		toplam = toplam / size;
	}

	return toplam;
}

//--------------------------------------------
void swap(House* a, House* b) {
	House* t = a;
	a = b;
	b = t;
}
int partitionLot(House arr[], int low, int high) {
	int pivot = arr[high].lotarea;
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++) {

		if (arr[j].lotarea <= pivot) {
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}
void quickSortLot(House arr[], int low, int high) {
	if (low < high) {

		int pi = partitionLot(arr, low, high);

		quickSortLot(arr, low, pi - 1);
		quickSortLot(arr, pi + 1, high);
	}
}

//--------------------------------------------------

int partitionYear(House arr[], int low, int high) {
	int pivot = arr[high].yearbuilt;
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++) {

		if (arr[j].yearbuilt <= pivot) {
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}
void quickSortYear(House arr[], int low, int high) {
	if (low < high) {

		int pi = partitionYear(arr, low, high);

		quickSortYear(arr, low, pi - 1);
		quickSortYear(arr, pi + 1, high);
	}
}
//------------------------------------------------------------------------

int partitionPrice(House arr[], int low, int high) {
	int pivot = arr[high].saleprice;
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++) {

		if (arr[j].saleprice <= pivot) {
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}
void quickSortPrice(House arr[], int low, int high) {
	if (low < high) {

		int pi = partitionPrice(arr, low, high);

		quickSortPrice(arr, low, pi - 1);
		quickSortPrice(arr, pi + 1, high);
	}
}

//-----------------------------------------------------------------

void sort_houses(House* houses, char* criter_name) {
	printf("Sort house by %s and save \n", criter_name);
	// TODO
	if (strcmp(criter_name, "lotarea")) {
		int houses_size = sizeof(houses) / sizeof(houses[0]);
		quickSortLot(houses, 0, houses_size);
	}
	if (strcmp(criter_name, "yearbuilt")) {
		int houses_size = sizeof(houses) / sizeof(houses[0]);
		quickSortYear(houses, 0, houses_size);
	}
	if (strcmp(criter_name, "saleprice")) {
		int houses_size = sizeof(houses) / sizeof(houses[0]);
		quickSortPrice(houses, 0, houses_size);
	}

	return;
}
