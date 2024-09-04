#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>

int getKey(){
	int key;

	key = getch();  //1바이트 읽음
	if(key == 224){ //if(확장문자이면...)
		key = getch();
	}
	return key;
}

//up.		72
//down.		80
//right.	77
//left.		75

int main(){	
	int size, len, num;
	int key, temp;
	int	pz[100] = {0};
	int i, k;
	int index, moveIndex;


	printf("input size: ");
	scanf("%d", &size);
	system("cls");

	if(size <3 || size > 10) {
		printf("Error\n");
		return 0;
	}

	len = size * size;

	//중복없는 난수생성
	srand(time(NULL));
	for(i=0;i<len;i++){
		pz[i] = rand()%len; //0~len-1 난수생성		
		//중복 처리
		for(k=0;k<i;k++){
			if(pz[k] == pz[i]){
				i--;
				break;
			}
		}		
	}
	
	//pz 프린트
	printf("┌");
	for(i=0;i<size-1;i++) printf("──┬");
	printf("──┐\n");

	num=0;
	for(i=0;i<size;i++) { //줄
		for(k=0;k<size;k++){  //칸
			if(pz[num]>0) printf("│%2d",pz[num++]);
			else{
				printf("│%2c",'*');
				index = num;
				num++;
			}
		}
		printf("│\n");

		//밑줄
		if(i<size-1){
			printf("├");
			for(k=0;k<size-1;k++) printf("──┼");
			printf("──┤\n");
		}
		else{
			printf("└");
			for(k=0;k<size-1;k++) printf("──┴");
			printf("──┘\n");
		}
	}

	while(1){
		key = getKey();
		moveIndex = index;
		
		switch(key){
		case 72:	//up.		72
			if(index>size-1) moveIndex = index-size;
			break;
		case 80: 	//down.		80
			if(index<(size*(size-1))) moveIndex = index+size;
			break;
		case 77:	//right.	77
			if(index%size != size-1) moveIndex = index+1;
			break;
		case 75:	//left.		75
			if(index%size != 0) moveIndex = index-1;
			break;
		default:
			break;
		}

		if(index != moveIndex){
			//치환
			temp			= pz[index];
			pz[index]		= pz[moveIndex];
			pz[moveIndex]	= temp;
			
			index = moveIndex; // 0 위치 변경

			//pz 프린트
			system("cls");
			printf("┌");
			for(i=0;i<size-1;i++) printf("──┬");
			printf("──┐\n");

			num=0;
			for(i=0;i<size;i++) {
				for(k=0;k<size;k++){ 
					if(pz[num]>0) printf("│%2d",pz[num++]);
					else{
						printf("│%2c",'*');
						num++;
					}
				}
				printf("│\n");

				//밑줄
				if(i<size-1){
					printf("├");
					for(k=0;k<size-1;k++) printf("──┼");
					printf("──┤\n");
				}
				else{
					printf("└");
					for(k=0;k<size-1;k++) printf("──┴");
					printf("──┘\n");
				}
			}

			//종료확인
			for(i=0;i<len-1;i++){
				if(pz[i] != (i+1) ) break;
			}
			if(i==len-1){
				printf("Game over !!\n");
				break;
			}
		}

	}

	return 0;
}