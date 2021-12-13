/*************************************************************************
        Copyright © 2021 Konstantinidis Konstantinos

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*************************************************************************/
#include <stdio.h>
#include "genlib.h"
#include "simpio.h"
#include <ctype.h>
#include <string.h>

#define N 20

typedef struct{
    int numberofapartment;
    char fullname[25];
    int squaremeters;
    int radiatorslices;
}tenants;

int numberOfTenants();
void monthData(double *heating_amount, double *rent_amount);
void insertTenantsData(int m, tenants apartmentTenants[]);
void amountCalculation(int m, tenants apartmentTenants[], int *total_slices, int *totalsm, double *heating_amount, double *rent_amount, double heatingAmountPerApart[], double rentAmountPerApart[], double totalPerApart[]);
void print(int m, tenants apartmentTenants[], double heatingAmountPerApart[], double rentAmountPerApart[], double totalPerApart[], int totalsm, int total_slices, double *poso_thermanshs, double *rent_amount);

main(){
    tenants apartmentTenants[N];
    int m;

    m = numberOfTenants();

    double heating_amount, rent_amount;

    monthData(&heating_amount, &rent_amount);

    insertTenantsData(m, apartmentTenants);

    int total_slices=0, totalsm=0;

    double heatingAmountPerApart[20], rentAmountPerApart[20], totalPerApart[20];

    amountCalculation(m, apartmentTenants, &total_slices, &totalsm, &heating_amount, &rent_amount, heatingAmountPerApart, rentAmountPerApart, totalPerApart);

    print(m, apartmentTenants, heatingAmountPerApart, rentAmountPerApart, totalPerApart, totalsm, total_slices, &heating_amount, &rent_amount);

    system("PAUSE");
}

int numberOfTenants(){
    int m;

    printf("Insert the number of tenants: ");
    m = GetInteger();
    while(m<1){
        printf("Number must be > 0\n");
        printf("Insert the number of tenants: ");
        m = GetInteger();
    }

    return m;
}

void monthData(double *heating_amount, double *rent_amount){
    printf("Insert the heating amount: ");
    *heating_amount = GetReal();
    while(*heating_amount<1){
        printf("Number must be > 0\n");
        printf("Insert the heating amount: ");
        *heating_amount = GetReal();
    }

    printf("Insert the rent amount: ");
    *rent_amount = GetReal();
    while(*rent_amount<1){
        printf("Number must be > 0\n");
        printf("Insert the rent amount: ");
        *rent_amount = GetReal();
    }
}

void insertTenantsData(int m, tenants apartmentTenants[]){
    int i;

    for(i=0; i<m; i++){
        printf("Apartment number %d:\n", i+1);

        apartmentTenants[i].numberofapartment = i+1;

        printf("Insert Full Name: ");
        gets(apartmentTenants[i].fullname);

        printf("Insert square meters: ");
        apartmentTenants[i].squaremeters = GetInteger();

        printf("Insert radiatior slices: ");
        apartmentTenants[i].radiatorslices = GetInteger();
    }
}

void amountCalculation(int m, tenants apartmentTenants[], int *total_slices, int *totalsm, double *heating_amount, double *rent_amount, double heatingAmountPerApart[], double rentAmountPerApart[], double totalPerApart[]){
    int i;

    for(i=0; i<m; i++){
        *total_slices += apartmentTenants[i].radiatorslices;
        *totalsm += apartmentTenants[i].squaremeters;
    }

    for(i=0; i<m; i++){
        heatingAmountPerApart[i] = (*heating_amount) * apartmentTenants[i].radiatorslices / (*total_slices);
        rentAmountPerApart[i] = (*rent_amount) * apartmentTenants[i].squaremeters / (*totalsm);
    }

    for(i=0; i<m; i++)
        totalPerApart[i] = heatingAmountPerApart[i] + rentAmountPerApart[i];
}

void print(int m, tenants apartmentTenants[], double heatingAmountPerApart[], double rentAmountPerApart[], double totalPerApart[], int totalsm, int total_slices, double *heating_amount, double *rent_amount){
    int i;

    printf("%3s %26s %5s %6s %12s %12s %12s \n", "A/A", "FULL NAME", "S.M.", "SLICES", "HEAT AMOUNT", "RENT AMOUNT", "TOTAL");

    for(i=0; i<82; i++)
        printf("-");

    printf("\n");

    for(i=0; i<m; i++)
        printf("%3d %26s %5d %6d %12.02f %12.02f %12.02f\n", apartmentTenants[i].numberofapartment, apartmentTenants[i].fullname, apartmentTenants[i].squaremeters, apartmentTenants[i].radiatorslices, heatingAmountPerApart[i], rentAmountPerApart[i], totalPerApart[i]);

    for(i=0; i<82; i++)
        printf("-");

    printf("\n");

    printf("%-30s %5d %6d %12.02f %12.02f %12.02f", "TOTAL:", totalsm, total_slices, *heating_amount, *rent_amount, *heating_amount + *rent_amount);

    printf("\n");
}
