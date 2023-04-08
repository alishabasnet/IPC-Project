/******************************************************************************
Assignment 1 - Milestone 3
Full Name  : Alisha Basnet
Student ID#: 161963210
Email      : abasnet9@myseneca.ca
Section    : NCC

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
******************************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"

//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void) {
  printf("Pat.# Name            Phone#\n"
         "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient *patient, int fmt) {
  if (fmt == FMT_FORM) {
    printf("Name  : %s\n"
           "Number: %05d\n"
           "Phone : ",
           patient->name, patient->patientNumber);
    displayFormattedPhone(patient->phone.number);
    printf(" (%s)\n", patient->phone.description);
  } else {
    printf("%05d %-15s ", patient->patientNumber, patient->name);
    displayFormattedPhone(patient->phone.number);
    printf(" (%s)\n", patient->phone.description);
  }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date *date, int isAllRecords) {
  printf("Clinic Appointments for the Date: ");

  if (isAllRecords) {
    printf("<ALL>\n\n");
    printf("Date       Time  Pat.# Name            Phone#\n"
           "---------- ----- ----- --------------- --------------------\n");
  } else {
    printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
    printf("Time  Pat.# Name            Phone#\n"
           "----- ----- --------------- --------------------\n");
  }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient *patient,
                         const struct Appointment *appoint,
                         int includeDateField) {
  if (includeDateField) {
    printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
           appoint->date.day);
  }
  printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
         patient->patientNumber, patient->name);

  displayFormattedPhone(patient->phone.number);

  printf(" (%s)\n", patient->phone.description);
}

//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData *data) {
  int selection;

  do {
    printf("Veterinary Clinic System\n"
           "=========================\n"
           "1) PATIENT     Management\n"
           "2) APPOINTMENT Management\n"
           "-------------------------\n"
           "0) Exit System\n"
           "-------------------------\n"
           "Selection: ");
    selection = inputIntRange(0, 2);
    putchar('\n');
    switch (selection) {
    case 0:
      printf("Are you sure you want to exit? (y|n): ");
      selection = !(inputCharOption("yn") == 'y');
      putchar('\n');
      if (!selection) {
        printf("Exiting system... Goodbye.\n\n");
      }
      break;
    case 1:
      menuPatient(data->patients, data->maxPatient);
      break;
    case 2:
      menuAppointment(data);
      break;
    }
  } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max) {
  int selection;

  do {
    printf("Patient Management\n"
           "=========================\n"
           "1) VIEW   Patient Data\n"
           "2) SEARCH Patients\n"
           "3) ADD    Patient\n"
           "4) EDIT   Patient\n"
           "5) REMOVE Patient\n"
           "-------------------------\n"
           "0) Previous menu\n"
           "-------------------------\n"
           "Selection: ");
    selection = inputIntRange(0, 5);
    putchar('\n');
    switch (selection) {
    case 1:
      displayAllPatients(patient, max, FMT_TABLE);
      suspend();
      break;
    case 2:
      searchPatientData(patient, max);
      break;
    case 3:
      addPatient(patient, max);
      suspend();
      break;
    case 4:
      editPatient(patient, max);
      break;
    case 5:
      removePatient(patient, max);
      suspend();
      break;
    }
  } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient *patient) {
  int selection;

  do {
    printf("Edit Patient (%05d)\n"
           "=========================\n"
           "1) NAME : %s\n"
           "2) PHONE: ",
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf("\n"
           "-------------------------\n"
           "0) Previous menu\n"
           "-------------------------\n"
           "Selection: ");
    selection = inputIntRange(0, 2);
    putchar('\n');

    if (selection == 1) {
      printf("Name  : ");
      inputCString(patient->name, 1, NAME_LEN);
      putchar('\n');
      printf("Patient record updated!\n\n");
    } else if (selection == 2) {
      inputPhoneData(&patient->phone);
      printf("Patient record updated!\n\n");
    }

  } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData *data) {
  int selection;

  do {
    printf("Appointment Management\n"
           "==============================\n"
           "1) VIEW   ALL Appointments\n"
           "2) VIEW   Appointments by DATE\n"
           "3) ADD    Appointment\n"
           "4) REMOVE Appointment\n"
           "------------------------------\n"
           "0) Previous menu\n"
           "------------------------------\n"
           "Selection: ");
    selection = inputIntRange(0, 4);
    putchar('\n');
    switch (selection) {
    case 1:
      viewAllAppointments(data); // ToDo: You will need to create this function!
      suspend();
      break;
    case 2:
      viewAppointmentSchedule(
          data); // ToDo: You will need to create this function!
      suspend();
      break;
    case 3:
      addAppointment(
          data->appointments, data->maxAppointments, data->patients,
          data->maxPatient); // ToDo: You will need to create this function!
      suspend();
      break;
    case 4:
      removeAppointment(
          data->appointments, data->maxAppointments, data->patients,
          data->maxPatient); // ToDo: You will need to create this function!
      suspend();
      break;
    }
  } while (selection);
}

// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------

// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)
void displayAllPatients(const struct Patient patient[], int max, int fmt) {
  int i;
  displayPatientTableHeader();
  for (i = 0; i < max; i++) {
    if (patient[i].patientNumber != 0) {
      displayPatientData(&patient[i], FMT_TABLE);
    }
  }
  putchar('\n');
}

// Search for a patient record based on patient number or phone number
// (Copy your code from MS#2)
void searchPatientData(const struct Patient patient[], int max) {
  int selection;
  do {
    printf("Search Options\n"
           "==========================\n"
           "1) By patient number\n"
           "2) By phone number\n"
           "..........................\n"
           "0) Previous menu\n"
           "..........................\n"
           "Selection: ");
    selection = inputIntRange(0, 2);
    putchar('\n');

    switch (selection) {
    case 1:
      searchPatientByPatientNumber(patient, max);
      suspend();
      break;
    case 2:
      searchPatientByPhoneNumber(patient, max);
      suspend();
      break;
    }

  } while (selection);
}

// Add a new patient record to the patient array
// (Copy your code from MS#2)
void addPatient(struct Patient patient[], int max) {
  struct Patient p;
  int idx = nextPatientNumber(patient, max);

  if (idx >= max) {
    printf("ERROR: Patient listing is FULL!\n\n");
  } else {
    inputPatient(&p);
    patient[idx] = p;
    printf("\n*** New patient record added ***\n\n");
  }
}

// Edit a patient record from the patient array
// (Copy your code from MS#2)
void editPatient(struct Patient patient[], int max) {
  int index, patientNumber;

  printf("Enter the patient number: ");
  patientNumber = inputInt();
  putchar('\n');

  index = findPatientIndexByPatientNum(patientNumber, patient, max);

  if (index == -1) {
    printf("ERROR: Patient record not found!\n\n");
    suspend();
  } else {
    menuPatientEdit(&patient[index]);
  }
}

// Remove a patient record from the patient array
// (Copy your code from MS#2)
void removePatient(struct Patient patient[], int max) {
  char selection;
  int index, patientNumber;
  struct Patient p = {0};

  printf("Enter the patient number: ");
  patientNumber = inputInt();
  putchar('\n');

  index = findPatientIndexByPatientNum(patientNumber, patient, max);

  if (index == -1) {
    printf("ERROR: Patient record not found!\n\n");
  } else {
    displayPatientData(&patient[index], FMT_FORM);
    printf("\nAre you sure you want to remove this patient record? (y/n): ");
    selection = inputCharOption("yn");

    if (selection == 'y') {
      patient[index] = p;
      printf("Patient record has been removed!\n\n");
    } else {
      printf("Operation aborted.\n\n");
    }
  }
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
void viewAllAppointments(struct ClinicData *data) {
  int i;
  const struct Date date;
  displayScheduleTableHeader(&date, 1);

  for (i = 0; i < data->maxAppointments; i++) {
    if (data->appointments[i].date.year != 0) {
      displayScheduleData(&data->patients[i], &data->appointments[i], 1);
    }
  }
  putchar('\n');
}

// View appointment schedule for the user input date
void viewAppointmentSchedule(struct ClinicData *data) {
  int i;
  struct Date date;
  printf("Year        : ");
  date.year = inputInt();
  printf("Month (1-12): ");
  date.month = inputIntRange(1, 12);
  printf("Day (1-28)  : ");
  date.day = inputIntRange(1, 28);

  putchar('\n');
  displayScheduleTableHeader(&date, 0);

  for (i = 0; i < data->maxAppointments; i++) {
    if (data->appointments[i].date.year == date.year &&
        data->appointments[i].date.month == date.month &&
        data->appointments[i].date.day == date.day) {
      displayScheduleData(&data->patients[i], &data->appointments[i], 1);
    }
  }

  putchar('\n');
}

// Add an appointment record to the appointment array
void addAppointment(struct Appointment *appoint, int maxAppointments,
                    struct Patient *patient, int maxPatients) {

  struct Date date;
  struct Time time;
  struct Appointment newAppointment;
  int patientNumber, index, i, loop=1;

  printf("Patient Number: ");
  patientNumber = inputInt();

  index = findPatientIndexByPatientNum(patientNumber, patient, maxPatients);

  if (index == -1) {
    printf("ERROR: Patient record not found!\n\n");
    return;
  }

  printf("Year        : ");
  date.year = inputInt();
  printf("Month (1-12): ");
  date.month = inputIntRange(1, 12);
  printf("Day (1-28)  : ");
  date.day = inputIntRange(1, 28);

  while (loop) {
    printf("Hour (0-23)   : ");
    time.hour = inputIntRange(0, 23);
    printf("Minute (0-59 ): ");
    time.min = inputIntRange(0, 59);
    putchar('\n');

    if (((float)(time.hour) + (float)(time.min) / 60) <
            APPOINTMENT_START_HOUR ||
        ((float)(time.hour) + (float)(time.min) / 60) > APPOINTMENT_END_HOUR ||
        time.min % APPOINTMENT_INTERVAL != 0) {
      printf("ERROR: Time must be between %d:00 and %d:00 in %d minute "
             "intervals.\n\n",
             APPOINTMENT_START_HOUR, APPOINTMENT_END_HOUR,
             APPOINTMENT_INTERVAL);
      continue;
    }

    for (i = 0; i < maxAppointments; i++) {
      if(appoint[i].patientNumber == 0) {
        loop = 0;
        break;
      }

      if (appoint[i].date.year == date.year &&
              appoint[i].date.month == date.month &&
              appoint[i].date.day == date.day &&
              appoint[i].time.hour == time.hour &&
              appoint[i].time.min == time.min) {
        printf("ERROR: Appointment timeslot is not available!\n\n");
        break;
      }
    }


    if(loop == 0) {
      break;
    }
  }

  appoint[i].date = date;
  appoint[i].time = time;
  appoint[i].patientNumber = patientNumber;

  printf("*** Appointment scheduled! ***\n\n");
}

// Remove an appointment record from the appointment array
void removeAppointment(struct Appointment *appoint, int maxAppointments,
                       struct Patient *patient, int maxPatients) {
  char selection;
  struct Date date;
  struct Appointment a = {0};
  int patientNumber, index, i;
  printf("Patient Number: ");
  patientNumber = inputInt();

  index = findPatientIndexByPatientNum(patientNumber, patient, maxPatients);
  if (index == -1) {
    printf("ERROR: Patient record not found!\n\n");
  } else {
    printf("Year        : ");
    date.year = inputInt();
    printf("Month (1-12): ");
    date.month = inputIntRange(1, 12);
    printf("Day (1-28)  : ");
    date.day = inputIntRange(1, 28);
    putchar('\n');

    for (i = 0; i < maxAppointments; i++) {
      if (appoint[i].date.year == date.year &&
          appoint[i].date.month == date.month &&
          appoint[i].date.day == date.day) {
        displayPatientData(&patient[index], FMT_FORM);
        printf("Are you sure you want to remove this appointment (y,n): ");
        selection = inputCharOption("yn");
        if (selection == 'y') {
          appoint[i] = a;
          printf("\nAppointment record has been removed!\n\n");
        } else {
          printf("Operation aborted.\n\n");
        }
        break;
      }
    }
  }
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)
void searchPatientByPatientNumber(const struct Patient patient[], int max) {
  int index, patientNumber;
  printf("Search by patient number: ");
  patientNumber = inputInt();
  putchar('\n');

  index = findPatientIndexByPatientNum(patientNumber, patient, max);

  if (index == -1) {
    printf("*** No records found ***\n\n");
  } else {
    displayPatientData(&patient[index], FMT_FORM);
    putchar('\n');
  }
}

// Search and display patient records by phone number (tabular)
// (Copy your code from MS#2)
void searchPatientByPhoneNumber(const struct Patient patient[], int max) {
  int i = 0, j = 0, k = 0;
  char phoneNumber[PHONE_LEN];
  printf("Search by phone number: ");
  inputCString(phoneNumber, 1, PHONE_LEN);
  putchar('\n');

  displayPatientTableHeader();
  for (i = 0; i < max; i++) {
    for (j = 0; j < PHONE_LEN; j++) {
      if (patient[i].phone.number[j] != phoneNumber[j]) {
        break;
      }
    }

    if (j == PHONE_LEN) {
      k += 1;
      displayPatientData(&patient[i], FMT_TABLE);
    }
  }

  putchar('\n');
  if (k == 0) {
    printf("*** No records found ***\n\n");
  }
}

// Get the next highest patient number
// (Copy your code from MS#2)
int nextPatientNumber(const struct Patient patient[], int max) {
  int i;
  for (i = 0; i < max; i++) {
    if (patient[i].patientNumber == 0) {
      break;
    }
  }
  return i;
}

// Find the patient array index by patient number (returns -1 if not found)
// (Copy your code from MS#2)
int findPatientIndexByPatientNum(int patientNumber,
                                 const struct Patient patient[], int max) {
  int i = 0, index = -1;
  for (i = 0; i < max; i++) {
    if (patient[i].patientNumber == patientNumber && patientNumber != 0) {
      index = i;
      break;
    }
  }
  return index;
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (Copy your code from MS#2)
void inputPatient(struct Patient *patient) {
  printf("Patient Data Input\n");
  printf("------------------\n");
  printf("Number: ");
  patient->patientNumber = inputInt();
  printf("Name  : ");
  inputCString(patient->name, 1, NAME_LEN);
  putchar('\n');
  inputPhoneData(&patient->phone);
}

// Get user input for phone contact information
// (Copy your code from MS#2)
void inputPhoneData(struct Phone *phone) {
  int selection;
  printf("Phone Information\n");
  printf("-----------------\n");
  printf("How will the patient like to be contacted?\n");
  printf("1. Cell\n");
  printf("2. Home\n");
  printf("3. Work\n");
  printf("4. TBD\n");
  printf("Selection: ");
  selection = inputIntRange(1, 4);

  switch (selection) {
  case 1:
    assignCString(phone->description, "CELL");
    break;
  case 2:
    assignCString(phone->description, "HOME");
    break;
  case 3:
    assignCString(phone->description, "WORK");
    break;
  case 4:
    *phone->number = '\0';
    assignCString(phone->description, "TBD");
    break;
  }

  if (selection != 4) {
    printf("\nContact: %s\n", phone->description);
    printf("Number : ");
    inputCString(phone->number, PHONE_LEN, PHONE_LEN);
  }
}

//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records
// read)
int importPatients(const char *datafile, struct Patient patients[], int max) {
  FILE *fp;
  int count = 0;
  char line[100];

  fp = fopen(datafile, "r");

  if (fp == NULL) {
    printf("Failed to open file.\n");
    return 0;
  }

  while (count < max) {
    if (fscanf(fp, "%d|%[^|]|%[^|]|%[^\n]", &patients[count].patientNumber,
               patients[count].name, patients[count].phone.description,
               patients[count].phone.number) == EOF) {
      break;
    }
    count += 1;
  }

  fclose(fp);
  return count;
}

// Import appointment data from file into an Appointment array (returns # of
// records read)
int importAppointments(const char *datafile, struct Appointment appoints[],
                       int max) {
  FILE *fp;
  int count = 0;
  struct Appointment appoint;

  fp = fopen(datafile, "r");

  if (fp == NULL) {
    printf("Failed to open file.\n");
    return 0;
  }

  while (count < max) {
    if (fscanf(fp, "%d,%d,%d,%d,%d,%d\n", &appoints[count].patientNumber,
               &appoints[count].date.year, &appoints[count].date.month,
               &appoints[count].date.day, &appoints[count].time.hour,
               &appoints[count].time.min) == EOF) {
      break;
    }
    count += 1;
  }

  fclose(fp);
  return count;
}