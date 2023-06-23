#include <stdio.h>
void read(int n, int m, char matrix[n][m]){
    int i = 0;
    int j = 0;
    char c;
    while(i<n){
        c=getchar();
        if(c=='\n'){
            continue;
        }
        else{
            matrix[i][j]=(char)c;
            j++;
            if(j==m){
                i++;
                j=0;
            }
        }
    }
}

void ispis(int n,int m,char matrix[n][m]){
    for(int i=0;i<n;i++){
        putchar('\n');
        for(int j=0;j<m;j++){
            putchar(matrix[i][j]);
        }
    }
}

void generateTmp(int n,int m,char matrix[n][m],char temp[n+2][m+2]){
    for(int i=0;i<(m+2);i++){
        temp[0][i]='0';
        temp[n+1][i]='0';
    }

    for(int j=0;j<(n+2);j++){
        temp[j][0]='0';
        temp[j][m+1]='0';
    }

    for(int i=1;i<n+1;i++){
        for(int j=1;j<m+1;j++){
            temp[i][j]=(char)matrix[i-1][j-1];
        }
    }
}

void commitIterr(int n,int m,char matrix[n][m],char temp[n+2][m+2]){
    int X=0;
    int O=0;

    for(int i=1;i<n+1;i++){
        for(int j=1;j<m+1;j++){

            if(temp[i-1][j-1]=='X'){
                X++;
            }
            else if(temp[i-1][j-1]=='O'){
                O++;
            }


            if(temp[i-1][j]=='X'){
                X++;
            }
            else if(temp[i-1][j]=='O'){
                O++;
            }


            if(temp[i-1][j+1]=='X'){
                X++;
            }
            else if(temp[i-1][j+1]=='O'){
                O++;
            }


            if(temp[i][j+1]=='X'){
                X++;
            }
            else if(temp[i][j+1]=='O'){
                O++;
            }


            if(temp[i][j-1]=='X'){
                X++;
            }
            else if(temp[i][j-1]=='O'){
                O++;
            }


            if(temp[i+1][j]=='X'){
                X++;
            }
            else if(temp[i+1][j]=='O'){
                O++;
            }


            if(temp[i+1][j-1]=='X'){
                X++;
            }
            else if(temp[i+1][j-1]=='O'){
                O++;
            }


            if(temp[i+1][j+1]=='X'){
                X++;
            }
            else if(temp[i+1][j+1]=='O'){
                O++;
            }

            if(temp[i][j]=='O'){
                if(O==2||O==3){
                    matrix[i-1][j-1]='O';
                }
                else{
                    matrix[i-1][j-1]='X';
                }
            }

            if(temp[i][j]=='X'){
                if(O==3){
                    matrix[i-1][j-1]='O';
                }
            }

            O=0;
            X=0;
        }
    }
}

void iterate(int iterMax,int n,int m,char matrix[n][m],char temp[n+2][m+2]){
    for(int iterr=0;iterr<iterMax;iterr++){
        printf("\nITERATION%d",iterr);
        commitIterr(n,m,matrix,temp);
        ispis(n,m,matrix);
        generateTmp(n,m,matrix,temp);
    }
}


int main()
{
    int n,m;
    scanf("%d %d",&n,&m);

    if(n<=0||m<=0){
        return 0;
    }


    char *matrix=(char *)malloc(n*m*sizeof(char));
    char *temp=(char *)malloc((n+2)*(m+2)*sizeof(char));

    if(matrix==NULL||temp==NULL){
        printf("MEM_GRESKA");
        return 0;
    }
    read(n,m,matrix);
    generateTmp(n,m,matrix,temp);

    int iterMax;
    scanf("%d",&iterMax);

    printf("INITIAL");
    ispis(n,m,matrix);
    iterate(iterMax,n,m,matrix,temp);

    free(matrix);
    free(temp);
    return 0;
}
