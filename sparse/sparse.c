/*1º Projeto de IAED*/
/*João Lopes - 90732*/

#include <stdio.h>

#define MAX_ELEMENTS 10000

typedef struct{
  unsigned long int x, y;
  double value;
} Matrix;
Matrix myMatrix[MAX_ELEMENTS];

int top = 0; /*top is to keep track of the top index of the structure array*/
double zero = 0.000; /*Current zero of the matrix*/
char fileName[100]; /*File name*/
int prevFilename = 0; /*1 if file was saved before. 0 if not*/

void emptyMatrix();
void addElement();
void printMatrix();
void carMatrix();
void listLine();
void listColumn();
void orderMatrix();
void newZero();
void saveFile();
void loadFile();
void compressMatrix();
/******************************************************************************/
void x(){
  int i;
  double v;
  scanf("%lf", &v);
  getchar();

  if(v != zero){
    for(i = 0; i < top ; i++){
      if(myMatrix[i].value == v){
        printf("[%lu; %lu] ", myMatrix[i].x, myMatrix[i].y);
      }
    }
    printf("\n");
    return;
  }
  printf("zero value\n");
}
/******************************************************************************/
void y(){
  double min = myMatrix[0].value, max = myMatrix[0].value;
  int i, minCount = 1, maxCount = 1;

  for(i = 1; i < top; i++){
    if(myMatrix[i].value == min){
      minCount++;
    }
    if(myMatrix[i].value == max){
      maxCount++;
    }
    if(myMatrix[i].value < min){
      min = myMatrix[i].value;
      minCount = 1;
    }
    else if(myMatrix[i].value > max){
      max = myMatrix[i].value;
      maxCount = 1;
    }
  }
  printf("%lf#%d %lf#%d", max, maxCount, min, minCount);
}
/******************************************************************************/
int main(int argc, char *argv[]){
  char opcao;

  emptyMatrix(myMatrix); /*to make sure every element is 0 in the beggining*/

  /*If user entered a name as argument, process a file with that name*/
  if(argv[1]){
    loadFile(argv[1]);
  }

  while((opcao = getchar()) != EOF){
    switch (opcao) {

      case 'a': addElement();   break;
      case 'p': printMatrix();  break;
      case 'i': carMatrix();    break;
      case 'l': listLine();     break;
      case 'c': listColumn();   break;
      case 'o': orderMatrix();  break;
      case 'z': newZero();      break;
      case 'w': saveFile();     break;
      case 's': compressMatrix(); break;
      case 'x': x();            break;
      case 'y': y();            break;
      case 'q': return 0;       break;
      default:                  break;
    }
  }
  return 0;
}

void emptyMatrix(){
  /*This makes all the elements 0 to make sure nothing stored in memory before corrupts our data*/
  int i;

  for(i = 0 ; i < MAX_ELEMENTS ; i++){
    myMatrix[i].x = 0;
    myMatrix[i].y = 0;
    myMatrix[i].value = 0.0;
  }
}

void addElement(){
  unsigned long int opArgs[2]; double opValue;
  int i, temp = 0;

  scanf("%lu %lu %lf", &opArgs[0], &opArgs[1], &opValue);

  if(opValue != zero){
    for(i = 0 ; i < top ; i++){
      if(myMatrix[i].x == opArgs[0] && myMatrix[i].y == opArgs[1]){
        myMatrix[i].value = opValue;
        temp = 1; /*Switch value if position was already represented*/
        break;
      }
    }

    if(temp != 1 /*if it is not represented yet, create a new representation with x, y and value*/){
      myMatrix[top].x = opArgs[0];
      myMatrix[top].y = opArgs[1];
      myMatrix[top].value = opValue;
      top++;
    }
  }
  else{
    /*if the value is zero then remove it*/
    temp = -1;
    for(i = 0 ; i < top ; i++){
      if(myMatrix[i].x == opArgs[0] && myMatrix[i].y == opArgs[1]){
        temp = i;
      }
    }
    if(temp != -1){
      for(i = temp ; i <= top ; i++){
        myMatrix[i].x = myMatrix[i + 1].x;
        myMatrix[i].y = myMatrix[i + 1].y;
        myMatrix[i].value = myMatrix[i + 1].value;
      }
      top--;
    }
  }
}

void printMatrix(){
  int i;

  /*If matrix isn't empty*/
  if(top > 0){
    for(i = 0 ; i < top ; i++){
      if(myMatrix[i].value != zero){
        printf("[%lu;%lu]=%.3lf\n", myMatrix[i].x, myMatrix[i].y, myMatrix[i].value);
      }
    }
  }
  else{
    printf("empty matrix\n");
  }
}

void carMatrix(){
  unsigned long int i, size, nelem = 0, mini, minj, maxi, maxj;
  double dens;

  /*Count how many elements the matrix has*/
  for(i = 0 ; i < top ; i++){
    if(myMatrix[i].value != zero){
      nelem++;
    }
  }

  /*If matrix isn't empty*/
  if(top > 0){
    mini = myMatrix[0].x, minj = myMatrix[0].y, maxi = myMatrix[0].x, maxj = myMatrix[0].y;

    for(i = 0 ; i < top ; i++){
      if(myMatrix[i].x < mini){
        mini = myMatrix[i].x;
      }
      if(myMatrix[i].x > maxi){
        maxi = myMatrix[i].x;
      }
      if(myMatrix[i].y < minj){
        minj = myMatrix[i].y;
      }
      if(myMatrix[i].y > maxj){
        maxj = myMatrix[i].y;
      }
    }

    size = (maxi - mini + 1) * (maxj - minj + 1);
    dens = ((double)nelem / (double)size) * 100.0;

    printf("[%lu %lu] [%lu %lu] %lu / %lu = %.3lf%%\n", mini, minj, maxi, maxj, nelem, size, dens);
  }
  else{
    printf("empty matrix\n");
  }
}

void listLine(){
  unsigned long int opArg; /*comando: <char int> */
  unsigned long int i, j, sum = 0, count = 0, temp;
  unsigned long int mini, maxi, minj, maxj;

  scanf("%lu", &opArg);

  /*Counts the amount of non-zero elements on the line*/
  for(i = 0 ; i < top ; i++){
    if(myMatrix[i].x == opArg){
      sum += myMatrix[i].value;
      count++;
    }
  }

  /*If the line isn't empty*/
  if(sum != zero*count){
    mini = myMatrix[0].x, maxi = myMatrix[0].x;
    minj = myMatrix[0].y, maxj = myMatrix[0].y;

    for(i = 0 ; i < top ; i++){
      if(myMatrix[i].y < minj){
        minj = myMatrix[i].y;
      }
      if(myMatrix[i].y > maxj){
        maxj = myMatrix[i].y;
      }
      if(myMatrix[i].x < mini){
        mini = myMatrix[i].x;
      }
      if(myMatrix[i].x > maxi){
        maxi = myMatrix[i].x;
      }
    }
  }

  if(sum != zero*count && (opArg >= mini && opArg <= maxi)){
    /*If the element is non-zero print its value otherwise print zero*/
    for(i = minj ; i <= maxj ; i++){
      temp = 0;
      for(j = 0 ; j < top ; j++){
        if(myMatrix[j].x == opArg && myMatrix[j].y == i){
          if(i == maxj){
            printf(" %.3f\n", myMatrix[j].value);
            temp = 1;
          }
          else{
            printf(" %.3f", myMatrix[j].value);
            temp = 1;
          }
        }
      }
      if(temp == 0){
        if(i == maxj){
          printf(" %.3f\n",zero);
        }
        else{
          printf(" %.3f", zero);
        }
      }
    }
  }
  else{
    printf("empty line\n");
  }
}

void listColumn(){
  unsigned long int opArg; /*comando: <char int> */
  unsigned long int i, j, sum = 0, count = 0, temp;
  unsigned long int mini, maxi, minj, maxj;

  scanf("%lu", &opArg);

  /*Counts the amount of non-zero elements on the column*/
  for(i = 0 ; i < top ; i++){
    if(myMatrix[i].y == opArg){
      sum += myMatrix[i].value;
      count++;
    }
  }

  /*If the column isn't empty*/
  if(sum != zero*count){
    mini = myMatrix[0].x, maxi = myMatrix[0].x;
    minj = myMatrix[0].y, maxj = myMatrix[0].y;

    for(i = 0 ; i < top ; i++){
      if(myMatrix[i].y < minj){
        minj = myMatrix[i].y;
      }
      if(myMatrix[i].y > maxj){
        maxj = myMatrix[i].y;
      }
      if(myMatrix[i].x < mini){
        mini = myMatrix[i].x;
      }
      if(myMatrix[i].x > maxi){
        maxi = myMatrix[i].x;
      }
    }
  }

  if(sum != zero*count && (opArg >= minj && opArg <= maxj)){
    for(i = mini ; i <= maxi ; i++){
      temp = 0;
      for(j = 0 ; j < top ; j++){
        if(myMatrix[j].y == opArg && myMatrix[j].x == i){
          printf("[%lu;%lu]=%.3lf\n", myMatrix[j].x, myMatrix[j].y, myMatrix[j].value);
          temp = 1;
        }
      }
      if(temp == 0){
          printf("[%lu;%lu]=%.3lf\n", i, opArg, zero);
      }
    }\


  }
  else{
    printf("empty column\n");
  }
}

void orderMatrix(){
  char opArg[8]; /*comando: <char int> */
  char command[] = " column";
  unsigned long int i = 0, n, j, k, l, nj = 0, tempint;
  double tempdouble;

  while((opArg[i] = getchar()) != '\n'){
    if(i > 6 || opArg[i] != command[i]){
      /*invalid command if string is bigger than 6, do no read any longer*/
      return;
    }
    else{
      i++;
    }
  }

  if(i == 0 && opArg[0] == '\n'){
    /*orders default mode*/
    /*orders by line*/
    for(i = 0; i < top - 1 ; i++){
      n = myMatrix[i].x;
      nj = i;
      for(j = i + 1 ; j < top; j++){
        if(myMatrix[j].x < n){
          n = myMatrix[j].x;
          nj = j;
        }
      }
      /*insertion sort was performed*/
      tempint = myMatrix[i].x;
      myMatrix[i].x = myMatrix[nj].x;
      myMatrix[nj].x = tempint;
      tempint = myMatrix[i].y;
      myMatrix[i].y = myMatrix[nj].y;
      myMatrix[nj].y = tempint;
      tempdouble = myMatrix[i].value;
      myMatrix[i].value = myMatrix[nj].value;
      myMatrix[nj].value = tempdouble;
    }
    /*now, it is ordered by line, and will be ordered by column*/
    i = 0;
    j = 0;
    k = 0;
    l = 0;
    n = 0;
    nj = 0;

    while(i < top){
      j = i;
      while(j < top && myMatrix[i].x == myMatrix[j + 1].x){
        j++;
      }

      for(k = i ; k < j; k++){
        n = myMatrix[k].y;
        nj = k;
        for(l = k + 1 ; l < j + 1; l++){
          if(myMatrix[l].y < n){
            n = myMatrix[l].y;
            nj = l;
          }
        }

        tempint = myMatrix[k].x;
        myMatrix[k].x = myMatrix[nj].x;
        myMatrix[nj].x = tempint;
        tempint = myMatrix[k].y;
        myMatrix[k].y = myMatrix[nj].y;
        myMatrix[nj].y = tempint;
        tempdouble = myMatrix[k].value;
        myMatrix[k].value = myMatrix[nj].value;
        myMatrix[nj].value = tempdouble;
      }
      i = j + 1;;
    }
  }
  else if(i == 7){
    /*orders by column*/
    for(i = 0; i < top - 1 ; i++){
      n = myMatrix[i].y;
      nj = i;
      for(j = i + 1 ; j < top; j++){
        if(myMatrix[j].y < n){
          n = myMatrix[j].y;
          nj = j;
        }
      }
      /*insertion sort performed by column*/
      tempint = myMatrix[i].x;
      myMatrix[i].x = myMatrix[nj].x;
      myMatrix[nj].x = tempint;
      tempint = myMatrix[i].y;
      myMatrix[i].y = myMatrix[nj].y;
      myMatrix[nj].y = tempint;
      tempdouble = myMatrix[i].value;
      myMatrix[i].value = myMatrix[nj].value;
      myMatrix[nj].value = tempdouble;
    }
    /*and after, by line*/
    i = 0;
    j = 0;
    k = 0;
    l = 0;
    n = 0;
    nj = 0;

    while(i < top){
      j = i;
      while(j < top && myMatrix[i].y == myMatrix[j + 1].y){
        j++;
      }

      for(k = i ; k < j; k++){
        n = myMatrix[k].x;
        nj = k;
        for(l = k + 1 ; l < j + 1; l++){
          if(myMatrix[l].x < n){
            n = myMatrix[l].x;
            nj = l;
          }
        }
        /*i troca com o menor j (n)*/
        tempint = myMatrix[k].x;
        myMatrix[k].x = myMatrix[nj].x;
        myMatrix[nj].x = tempint;
        tempint = myMatrix[k].y;
        myMatrix[k].y = myMatrix[nj].y;
        myMatrix[nj].y = tempint;
        tempdouble = myMatrix[k].value;
        myMatrix[k].value = myMatrix[nj].value;
        myMatrix[nj].value = tempdouble;
      }
      i = j + 1;;
    }
  }

}

void newZero(){
  double opArg;
  int temp;
  int k, i;

  scanf("%lf", &opArg);

  zero = opArg; /*Consider zero the input*/

  /*Remove any element that is the new zero*/
  k = 0;
  while(k < top){
    temp = -1;
    if(myMatrix[k].value == opArg){
      temp = k;
    }

    if(temp != -1){
      for(i = temp ; i <= top ; i++){
        myMatrix[i].x = myMatrix[i + 1].x;
        myMatrix[i].y = myMatrix[i + 1].y;
        myMatrix[i].value = myMatrix[i + 1].value;
      }
      top--;
    }
    k++;
  }
}

void saveFile(){
  char tmpName[100];
  int i = 0;
  int a, b;
  double c;

  FILE *fp;

  while((tmpName[i] = getchar()) != '\n'){
    if(tmpName[i] != ' '){
      i++;
    }
  }

  /*if user only entered w*/
  if(i == 0 && tmpName[0] == '\n' && prevFilename == 1){
    if ((fp = fopen(fileName, "w"))) {
  		for (i = 0; i < top; i++){
        a = myMatrix[i].x, b = myMatrix[i].y, c = myMatrix[i].value;
  			fprintf(fp, "%d %d %.3lf\n", a, b, c);
      }
  		fclose(fp);
  	}
    else{
       perror(fileName);
     }
  }
  /*if user entered a file name*/
  else if( prevFilename == 0 && i != 0){
    tmpName[i] = '\0';
    if ((fp = fopen(tmpName, "w"))) {
  		for (i = 0; i < top; i++){
        a = myMatrix[i].x, b = myMatrix[i].y, c = myMatrix[i].value;
  			fprintf(fp, "%d %d %.3lf\n", a, b, c);
      }
      prevFilename = 1;
  		fclose(fp);

  	}
    else{
      perror(tmpName);
    }
    /*if there was no file and user entered one name, keep that filename for future w commands*/
    if(prevFilename == 1){
      for(i = 0 ; i < 100 ; i++){
        fileName[i] = tmpName[i];
      }
    }
  }
  else{
    return;
  }
}

void loadFile(char arg[]){
  int i = 0;
  FILE *fp;

  while(arg[i] != '\0'){
    fileName[i] = arg[i];
    i++;
  }
  fileName[i] = '\0';
  prevFilename = 1;

	if ((fp = fopen(arg, "r"))){
		while (fscanf(fp, "%lu %lu %lf", &myMatrix[top].x, &myMatrix[top].y, &myMatrix[top].value) == 3){
      top++;
    }
		fclose(fp);
	}
  else{
    perror(arg);
  }
}

void compressMatrix(){
  /*unfinished function*/
  int i, size, nelem = 0, mini, minj, maxi, maxj;
  double dens;

  for(i = 0 ; i < top ; i++){
    if(myMatrix[i].value != zero){
      nelem++;
    }
  }

  mini = myMatrix[0].x, minj = myMatrix[0].y, maxi = myMatrix[0].x, maxj = myMatrix[0].y;

  for(i = 0 ; i < top ; i++){
    if(myMatrix[i].x < mini){
      mini = myMatrix[i].x;
    }
    if(myMatrix[i].x > maxi){
      maxi = myMatrix[i].x;
    }
    if(myMatrix[i].y < minj){
      minj = myMatrix[i].y;
    }
    if(myMatrix[i].y > maxj){
      maxj = myMatrix[i].y;
    }
  }

  size = (maxi - mini + 1) * (maxj - minj + 1);
  dens = ((double)nelem / (double)size) * 100.0;


  if (dens > 50.0){
    printf("dense matrix\n");
  }
  else{

  }
}
