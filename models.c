#include"models.h"
#include"dataset.h"
#include<stdio.h>
#include<math.h>

int model_by_similarity(House* houses, House new_house) {
	printf("Find price for house %d\n", new_house.id);
	int price;
	//TODO

	// 1 - Oncelikle ayni komsuluktaki evleri bulun
	House *near= get_neighborhoods(new_house, houses);

	// 2 - Bu evleri lotArea ya gore siralayin
	sort_houses(near, "lotarea");
	// 3 - new_house degiskenin lotarea parametresine en
	//  yakin evleri alin, bu evlerin alanlari
	//  (new_house.lotarea+2000) ve (new_house.lotarea-2000) metrekare arasinda
	//   olabilir.
	House lotclose[10];
	int i = 0;
	int j = 0;
	for (i = 0; i < (sizeof(near) / sizeof(near[0])); i++) {
		if (near[i].lotarea < new_house.lotarea + 2000
				|| near[i].lotarea > new_house.lotarea - 2000) {
			for (j = 0; j < 10; j++) {
				lotclose[j] = near[i];
			}
		}
	}

	// 4 - Kalan evleri yillarina gore siralayin
	sort_houses(lotclose, "yearbuilt");

	// 5 - new_house degiskenin yearbuilt parametresine en yakin
	// evleri secin, bu evlerin yapim tarihleri
	//  (new_house.yearbuilt+5) ve (new_house-5) arasinda olabilir.
	House yearclose[5];
	for (i = 0; i < (sizeof(lotclose) / sizeof(lotclose[0])); i++) {
		if (lotclose[i].yearbuilt < new_house.yearbuilt + 5
				|| lotclose[i].yearbuilt > new_house.yearbuilt - 5) {
			for (j = 0; j < 10; j++) {
				yearclose[j] = lotclose[i];
			}
		}

		// 6 - Ek olarak kaliteye gore secim yapabilirsiniz.

		// 7 - Son elemeden sonra elinizde kalan evlerin fiyat ortalamasini alin
		price = mean_sale_prices(yearclose, "yearbuilt");
		// 8 - Yeni gelen ev icin fiyat degeri bu ortalama olmalidir.


	}
	return price;
}
	void create_data_matrices(House* houses, int** X, int* y) {
		printf("Create data matrices from dataset\n");
		// TODO


		  int i,j;
		  for(i=0;i<100;i++){
		  	X[i][1]=1;
		  	X[i][2]=houses[i].lotarea;

		  }
		  for(j=0;j<100;j++){

		  	y[j]=houses[i].saleprice;
		  }

		return;
	}
//-------------------------------------
	int calcul_determinant(int **A,int n)
	{
	  int det=0,p,h,k,i,j;
	  int **temp;
	  if(n==1)
	  {
	      return A[0][0];
	  }
	  else if(n==2)
	  {
	      det=(A[0][0]*A[1][1]-A[0][1]*A[1][0]);
	      return det;
	  }
	  else
	  {
	    for(p=0;p<n;p++)
	    {
	       h = 0;
	       k = 0;
	       for(i=1;i<n;i++)
	       {
	         for( j=0;j<n;j++)
	         {
	            if(j==p)
	                {
	                    continue;
	                }
	                temp[h][k] = A[i][j];
	            k++;
	                if(k==n-1)
	                {
	                      h++;
	                      k = 0;
	            }
	             }
	       }
	       det=det+A[0][p]*pow(-1,p)*calcul_determinant(temp,n-1);

	    }
	    return det;
	  }
	}
//-------------------------------------
	int** get_transpose(int** A) {
		int ** Atranspose;
		printf("Get Transpose\n");
		// TODO
		 int i,j;
		  for(i=0;i<100;i++){
		  	for(j=0;j<2;j++){

		  		Atranspose[j][i]=A[i][j];

			}
		  }
		return Atranspose;
	}

	int** get_inverse(int** A) {
		int** Ainverse;

		// TODO
		 float p,k;
		  int i,j,x;
		  printf("Get inverse\n");
		  // TODO
		  if(calcul_determinant(A,100)==0){
		  	 return 0;
		  }
		  else{

		  for(i=0;i<100;i++){
		  	for(j=0;j<100;j++){
		  		if(i==j) Ainverse[i][j]=1;
		  		else Ainverse[i][j]=0;
			  }
		  }
		  for(i=0;i<100;i++){
		  	p=A[i][i];
		  	for(j=0;j<100;j++){
		  		A[i][j]=A[i][j]/p;
		  		Ainverse[i][j]=Ainverse[i][j]/p;
			  }
		  }
		  for( x=0;x<100;x++){
		  	if(x!=i){
		  		k=A[x][i];
		  		for(j=0;j<100;j++){
		  			A[x][j]=A[x][j]-(A[i][j]*k);
		  			Ainverse[x][j]=Ainverse[x][j]-(Ainverse[i][j]*k);
				  }
			  }
		  }
		}
		return Ainverse;
	}

	int** get_multiplication(int** A, int** B) {
		int ** C;
		printf("Multiplication\n");
		// TODO
		  int i,j,k;
		  for(i=0;i<100;i++){
		  	for(j=0;j<100;j++){
		  		for(k=0;k<100;k++){
		  			C[i][j]+=A[i][k]*B[k][j];
				  }
			  }
		  }
		return C;
	}

	int** calculate_parameter(int** X,int** y) {
		int** W;
		printf("Calculate parameters for dataset\n");
		// TODO



		int** A= get_transpose(X);
		int** B= get_multiplication(A,X);
		int** C= get_inverse(B);
		int** D= get_multiplication(C,X);
		W = get_multiplication(D,y);
		return W;

	}

int** make_prediction(char* filename, int** W) {
		int** predicted_prices;
		printf("Make prediction\n");
		// TODO
		// 1 - filename olarak verilen test verisini oku,
		//   yeni houses dizisi olustur
		int size = 100;
		House houses[size];
		read_house_data(filename, houses);
		// 2 - create_data_matrices kullanarak X ve y matrislerini olustur
		int** X;
		int* y;
		create_data_matrices(houses,X,y);
		// 3 - Daha onceden hesaplanan W parametresini kullanarak
		//  fiyat tahmini yap, burda yapilmasi gereken
		//  X ve W matrislerinin carpimini bulmak

		// 4 - Sonuclari bir dosyaya yaz
		predicted_prices=get_multiplication(X,W);
		return predicted_prices;
}

