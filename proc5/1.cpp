#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100

// Structure for storing product information
typedef struct {
    char name[50];
    float price;
    int quantity;
    float profit_margin;
    float gross_price;
    float total_price;
} ProductType;

// Function for reading product data from a file
int read_products(ProductType* products) {
    FILE* file = fopen("products.txt", "r");
    if (file == NULL) {
        printf("Error: could not open file\n");
        return 0;
    }


    int count = 0;

    while (count < MAX_PRODUCTS && !feof(file)) {
        fscanf(file, "%s %f %d %f", products[count].name, &products[count].price, &products[count].quantity, &products[count].profit_margin);
        count++;
    }

    fclose(file);
    return count;
}

//Function to calculate gross prices and total cost of products
void calculate_prices(ProductType* products, int count) {
    for (int i = 0; i < count; i++) {
        products[i].gross_price = products[i].price * (1 + products[i].profit_margin);
        products[i].total_price = products[i].gross_price * products[i].quantity;
    }
}

// Function to sort products by cost
void sort_products(ProductType* products, int count) {
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            if (products[i].total_price < products[j].total_price) {
                ProductType temp = products[i];
                products[i] = products[j];
                products[j] = temp;
            }
        }
    }
}

// Function to write sorted products to a file
void write_products(ProductType* products, int count) {
    FILE* file = fopen("sorted_products.txt", "w");
    if (file == NULL) {
        printf("Error: could not open file\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %.2f %d %.2f %.2f %.2f\n", products[i].name, products[i].price, products[i].quantity, products[i].profit_margin, products[i].gross_price, products[i].total_price);
    }

    fclose(file);
}

int main() {
    // Memory allocation for an array of products
    ProductType* products = (ProductType*)malloc(MAX_PRODUCTS * sizeof(ProductType));

    //Reading product data from a file
    int count = read_products(products);

    // Calculation of gross prices and total cost of products
    calculate_prices(products, count);

    // Sort products by cost
    sort_products(products, count);

    // Writing sorted products to a file
    write_products(products, count);
}