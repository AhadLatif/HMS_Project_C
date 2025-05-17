#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Person
{
    int id;
    char name[30];
    float salary;
};

int main()
{
    FILE *fp;
    struct Person people[2] = {
        {1, "Alice", 55000.50},
        {2, "Bob", 60000.00}};

    // Start timing
    clock_t start_time = clock();

    // 🔹 Write binary data to file
    fp = fopen("data.bin", "wb");
    if (fp == NULL)
    {
        perror("Error opening file for writing");
        return 1;
    }

    fwrite(people, sizeof(struct Person), 2, fp);
    fclose(fp);

    // Clear array to simulate fresh read
    memset(people, 0, sizeof(people));

    // 🔹 Read binary data from file
    fp = fopen("data.bin", "rb");
    if (fp == NULL)
    {
        perror("Error opening file for reading");
        return 1;
    }

    fread(people, sizeof(struct Person), 2, fp);
    fclose(fp);

    // End timing
    clock_t end_time = clock();

    // Output the time taken for the I/O operations
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Time taken for file I/O operations: %.5f seconds\n", time_taken);

    // Output the data
    for (int i = 0; i < 2; i++)
    {
        printf("ID: %d, Name: %s, Salary: %.2f\n",
               people[i].id, people[i].name, people[i].salary);
    }

    return 0;
}
