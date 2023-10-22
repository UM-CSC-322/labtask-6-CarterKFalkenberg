#include <stdio.h>
#include <stdlib.h>

/*
* Reads in a matrix by prompting the user for their dimensions, 
* dynamically allocating memory from the heap, and reading the values into the memory using 
* row major ordering for the matrix values
*/
double* input_matrix(int* rows, int* columns, char matrix_num[]){
    
    // get num rows
    printf("How many rows is your matrix?\n");
    scanf("%d", rows); 
    while(*rows <= 0){
        printf("Invalid number of rows. Try again\n");
        scanf("%d", rows); 
    }
    
    // get num columns
    printf("How many columns is your matrix?\n");
    scanf("%d", columns);
    while(*columns <= 0){
        printf("Invalid number of columns. Try again\n");
        scanf("%d", columns); 
    }

    // allocate memory for the matrix
    double* matrix = (double*) malloc((*rows) * (*columns) * sizeof(double));
    if (matrix == NULL) return NULL;
    
    // get contents of the matrix in row major order
    printf("Enter all numbers of the matrix in row major order\n");
    for (int i = 0; i < (*rows) * (*columns); i++){
        printf("Enter the next number: ");
        scanf("%lf", matrix+i);
    }
    
    return matrix;
}

/*
* Prints a matrix in row major order
*/
void output_matrix(double* matrix, int rows, int columns){
    double* current = matrix;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            printf("%.2f ", *current);
            current += 1;
        }
        printf("\n");
    }

}

/*
* Multiplies two row major ordered matrices m1 and m2, and sets the result to m3
*/
bool matrix_multiply(double* m1, int m1_rows, int m1_cols, double* m2, int m2_rows, int m2_cols, double* m3){
    
    if (m1_cols != m2_rows) return false;
    for (int row = 0; row < m1_rows; row++){
        for (int col = 0; col < m2_cols; col++){
            // multiply m1[row][:] and m2[:][col]. Both are length m1_cols (== m2_cols)
            int sum = 0; 
            for (int i = 0; i < m1_cols; i++){
                double num_m1 = *(m1 + (row * m1_cols) + i); // m1[row][i]
                double num_m2 = *(m2 + (i * m2_cols) + col); // m2[i][col]
                sum += num_m1 * num_m2;
            }
            *(m3 + (row * m2_cols) + col) = sum;
        }
    }
    
    return true;
}


int main(void) {

    double *m1,*m2,*m3;

    int m1_rows,m1_columns,m2_rows,m2_columns;

    if (((m1 = input_matrix(&m1_rows,&m1_columns,"Matrix 1")) != NULL) &&
((m2 = input_matrix(&m2_rows,&m2_columns,"Matrix 2")) != NULL) &&
((m3 = (double*)malloc(m1_rows*m2_columns*sizeof(double))) != NULL)) {
        printf("Matrix 1\n");
        output_matrix(m1,m1_rows,m1_columns);
        printf("Matrix 2\n");
        output_matrix(m2,m2_rows,m2_columns);
        if (matrix_multiply(m1,m1_rows,m1_columns,m2,m2_rows,m2_columns,m3)) {
            printf("Product\n");
            output_matrix(m3,m1_rows,m2_columns);
            free(m1);
            free(m2);
            free(m3);
            return(0);
        } else {
            printf("Error in dimensions\n");
            free(m1);
            free(m2);
            free(m3);
            return(-1);
        }
    } else {
        free(m1);
        free(m2);
        free(m3);
        printf("Error allocating memory\n");
        return(-2);
    }
}
