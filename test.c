#include <stdio.h>
#include<math.h> 
int main(){ 
	float n,j,i,p; 
	
	printf("enter n \n"); 
	scanf("%f",&n);
	n=n+3; 
	p=((4*n-2.5)/5.8); 
	for(j=p;j>=-p;j--){
	   printf("\n");	
		for(i=-n;i<=n;i++){ 
			if(p*p*i*i+n*n*j*j<=n*n*p*p) 
				printf("*"); 
			else
			{
				printf(" ");
			} 
		} 
	} 
	return 0;
} 
/*/
int main()
{
	float   h;
    float   w;
    float   rh;
    float   rw;

    h = 920.0;
    w = 680.0;
    rw = (h/w);
    rh = (w/h);
    printf("\n%f, %f, %f, %f", h, w, rh, rw);
	float age;

	age = 10.5;
	printf("TechOnTheNet.com is over %f years old.\n", age);

	return 0;

}
/*/
