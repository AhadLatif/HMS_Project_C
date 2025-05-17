#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "common.h"
#include "id_manager.h"

#include "patient.h"

Patient patients[MAX_PATIENTS];
int patient_counter = 0;
void loadPatientFromFile(void)

{

    FILE *fp = fopen("./data/patient.dat", "rb");

    fileCheck(fp);

    while (fread(&patients[patient_counter], sizeof(Patient), 1, fp) != 0)
    {
        patient_counter++;
    }

    fclose(fp);
}

// ------------  Add Patient ----------------
void addPatient()
{
    char choice[10];
    do
    {
        /* code */

        if (patient_counter > MAX_PATIENTS)
        {
            printf("List is full\n");
            return;
        }

        Patient new_patient;

        new_patient.p_id = id_manager.next_patient_id;

        for (int i = 0; i < patient_counter; i++)
        {

            if (patients[i].p_id == new_patient.p_id)
            {
                printf("ID %d already exists", new_patient.p_id);
            }
        }

        getchar();

        printf("Enter name: ");
        inputString(new_patient.p_name, sizeof(new_patient.p_name));

        new_patient.p_age = inputInt("Enter your age: ");

        printf("Enter gender: ");
        inputString(new_patient.p_gender, sizeof(new_patient.p_gender));

        printf("Enter disease: ");
        inputString(new_patient.p_disease, sizeof(new_patient.p_disease));

        printf("Enter contact number: ");
        inputString(new_patient.p_contact_num, sizeof(new_patient.p_contact_num));

        patients[patient_counter++] = new_patient;
        savePatientsToFile();
        id_manager.next_patient_id++;
        saveIDManager();
        printf("Patient Entered Successfully !\n");

        printf("Do you want to add another patient : \n");
        inputString(choice, sizeof(choice));

    } while (strcmp(choice, "N0") != 0 &&
             strcmp(choice, "No") != 0 &&
             strcmp(choice, "N") != 0 &&
             strcmp(choice, "n") != 0);
}

// --------------------------------------------Display Patients
void displayPatient()
{

    FILE *file = fopen("./data/patient.dat", "rb");

    fileCheck(file);

    printf("\n List of All Patients:\n");
    printf("-----------------------------------------------------------------------------------\n");
    printf("| %-5s | %-20s | %-3s | %-6s | %-15s | %-15s |\n", "ID", "Name", "Age", "Gender", "Disease", "Contact");
    printf("-----------------------------------------------------------------------------------\n");
    for (int i = 0; i < patient_counter; i++)
    {
        printf("| %-5d | %-20s | %-3d | %-6s | %-15s | %-15s |\n", patients[i].p_id, patients[i].p_name, patients[i].p_age, patients[i].p_gender, patients[i].p_disease, patients[i].p_contact_num);
    }

    printf("-----------------------------------------------------------------------------------\n");
    if (patient_counter == 0)
        printf("No patient records found.\n");
}

//----------------------------------savePatientsToFile

void savePatientsToFile()
{

    FILE *file = fopen("./data/patient.dat", "wb");
    fileCheck(file);

    for (int i = 0; i < patient_counter; i++)
    {
        fwrite(&patients[i], sizeof(Patient), 1, file);
    }

    fclose(file);
}

//  ---------------------------------------Search Functions
void searchPatientById()
{
    while ((getchar()) != '\n')
        ;
    int id;
    printf("Enter Id : \n");
    scanf("%d", &id);

    for (int i = 0; i < patient_counter; i++)
    {
        if (patients[i].p_id == id)
        {
            printf("-----------------------------------------------------------------------------------\n");
            printf("| %-5s | %-20s | %-3s | %-6s | %-15s | %-15s |\n", "ID", "Name", "Age", "Gender", "Disease", "Contact");
            printf("-----------------------------------------------------------------------------------\n");

            printf("| %-5d | %-20s | %-3d | %-6s | %-15s | %-15s |\n", patients[i].p_id, patients[i].p_name, patients[i].p_age, patients[i].p_gender, patients[i].p_disease, patients[i].p_contact_num);
            return;
        }
    }
    printf("Patient with ID %d not found.\n", id);
}
void searchPatientByName()
{
    while ((getchar()) != '\n')
        ;

    char name[50];
    printf("Enter Name : ");

    inputString(name, sizeof(name));

    for (int i = 0; i < patient_counter; i++)
    {
        if (strcasecmp(patients[i].p_name, name) == 0)
        {

            printf("-----------------------------------------------------------------------------------\n");
            printf("| %-5s | %-20s | %-3s | %-6s | %-15s | %-15s |\n", "ID", "Name", "Age", "Gender", "Disease", "Contact");
            printf("-----------------------------------------------------------------------------------\n");

            printf("| %-5d | %-20s | %-3d | %-6s | %-15s | %-15s |\n", patients[i].p_id, patients[i].p_name, patients[i].p_age, patients[i].p_gender, patients[i].p_disease, patients[i].p_contact_num);

            return;
        }
    }
    printf("Patient with name : %s not found.\n", name);
}

//-----------------------------------Delete

void deletePatient()
{

    int id, index = -1;

    // while ((getchar()) != '\n')
    id = inputInt("Enter ID:");
    // while ((getchar()) != '\n');

        
    for (int i = 0; i < patient_counter; i++)
    {
        if (patients[i].p_id == id)
        {
            index = i;
        }
    }

    if (index == -1)
    {
        printf("Patient with ID %d not found.\n", id);
        return;
    }

    for (int j = index; j < patient_counter; j++)
    {
        patients[j] = patients[j + 1];
    }

    patient_counter--;
    printf("Patient with ID %d  deleted successfully.\n", id);
    savePatientsToFile();
}
