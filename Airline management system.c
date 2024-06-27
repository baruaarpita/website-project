#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Flight {
    char flightNumber[10];
    char origin[10];
    char destination[10];
    char departureTime[10];
    struct Flight* next;
} Flight;

//here i used stack//
typedef struct Ticket {
    char flightNumber[10];
    char passengerName[50];
    struct Ticket* next;
} Ticket;
// here  i used queue//

typedef struct QueueNode {
    char passengerName[50];
    struct QueueNode* next;
} QueueNode;

QueueNode* front = NULL;
QueueNode* rear = NULL;


Flight* availableFlights = NULL;
Flight* bookedFlights = NULL;
Ticket* tickets = NULL;

// herei used array list
#define MAX_FLIGHTS 100
Flight* flightArray[MAX_FLIGHTS];
int flightCount = 0;


Flight* createFlight(char* flightNumber, char* origin, char* destination, char* departureTime);
void addFlight(Flight** head, char* flightNumber, char* origin, char* destination, char* departureTime);
void addFlightToArray(char* flightNumber, char* origin, char* destination, char* departureTime);
void displayFlights(Flight* head);
void displayFlightsFromArray();
void bookFlight(char* flightNumber, char* passengerName);
void displayBookedFlights();
void displayTickets();
void enqueue(char* name);
char* dequeue();
int isQueueEmpty();
void searchFlightsByOrigin(char* origin);
void cancelBooking(char* flightNumber, char* passengerName);

int main() {
    int choice;
    char flightNumber[10];
    char origin[10];
    char destination[10];
    char departureTime[10];
    char passengerName[50];


    printf("Welcome to 31~33 Airlines\n");


    addFlight(&availableFlights, "PK-125", "BD", "IND", "10:00");
    addFlight(&availableFlights, "PK-126", "BD", "DUB", "12:00");
    addFlight(&availableFlights, "PK-127", "BD", "USA", "14:00");

    addFlightToArray("PK-125", "BD", "IND", "10:00");
    addFlightToArray("PK-126", "BD", "DUB", "12:00");
    addFlightToArray("PK-127", "BD", "USA", "14:00");

    while (1) {
        printf("1. Book Flight\n");
        printf("2. Generate Ticket\n");
        printf("3. Display Available Flights\n");
        printf("4. Display Booked Flights\n");
        printf("5. Search Flights by Origin\n");
        printf("6. Cancel Booking\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Flight Number: ");
                scanf("%s", flightNumber);
                printf("Enter Passenger Name: ");
                scanf("%s", passengerName);
                bookFlight(flightNumber, passengerName);
                break;
            case 2:
                displayTickets();
                break;
            case 3:
                displayFlightsFromArray();
                break;
            case 4:
                displayBookedFlights();
                break;
            case 5:
                printf("Enter Origin: ");
                scanf("%s", origin);
                searchFlightsByOrigin(origin);
                break;
            case 6:
                printf("Enter Flight Number: ");
                scanf("%s", flightNumber);
                printf("Enter Passenger Name: ");
                scanf("%s", passengerName);
                cancelBooking(flightNumber, passengerName);
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

Flight* createFlight(char* flightNumber, char* origin, char* destination, char* departureTime) {
    Flight* newFlight = (Flight*)malloc(sizeof(Flight));
    strcpy(newFlight->flightNumber, flightNumber);
    strcpy(newFlight->origin, origin);
    strcpy(newFlight->destination, destination);
    strcpy(newFlight->departureTime, departureTime);
    newFlight->next = NULL;
    return newFlight;
}

void addFlight(Flight** head, char* flightNumber, char* origin, char* destination, char* departureTime) {
    Flight* newFlight = createFlight(flightNumber, origin, destination, departureTime);
    newFlight->next = *head;
    *head = newFlight;
}
// again i used array list
void addFlightToArray(char* flightNumber, char* origin, char* destination, char* departureTime) {
    if (flightCount >= MAX_FLIGHTS) {
        printf("Cannot add more flights, array is full\n");
        return;
    }
    flightArray[flightCount] = createFlight(flightNumber, origin, destination, departureTime);
    flightCount++;
}
// here we used linked list
void displayFlights(Flight* head) {
    Flight* current = head;
    while (current != NULL) {
        printf("Flight Number: %s\n", current->flightNumber);
        printf("Origin: %s\n", current->origin);
        printf("Destination: %s\n", current->destination);
        printf("Departure Time: %s\n", current->departureTime);
        printf("-----------------------------\n");
        current = current->next;
    }
}

// again array list
void displayFlightsFromArray() {
    for (int i = 0; i < flightCount; i++) {
        printf("Flight Number: %s\n", flightArray[i]->flightNumber);
        printf("Origin: %s\n", flightArray[i]->origin);
        printf("Destination: %s\n", flightArray[i]->destination);
        printf("Departure Time: %s\n", flightArray[i]->departureTime);
        printf("-----------------------------\n");
    }
}

void bookFlight(char* flightNumber, char* passengerName) {
    Flight* current = availableFlights;
    Flight* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->flightNumber, flightNumber) == 0) {
            if (prev == NULL) {
                availableFlights = current->next;
            } else {
                prev->next = current->next;
            }
            current->next = bookedFlights;
            bookedFlights = current;

            Ticket* newTicket = (Ticket*)malloc(sizeof(Ticket));
            strcpy(newTicket->flightNumber, flightNumber);
            strcpy(newTicket->passengerName, passengerName);
            newTicket->next = tickets;
            tickets = newTicket;

            enqueue(passengerName);

            printf("Flight %s booked successfully for %s.\n", flightNumber, passengerName);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Flight %s not found.\n", flightNumber);
}

void displayBookedFlights() {
    displayFlights(bookedFlights);
}

void displayTickets() {
    Ticket* current = tickets;
    while (current != NULL) {
        printf("Flight Number: %s\n", current->flightNumber);
        printf("Passenger Name: %s\n", current->passengerName);
        printf("-----------------------------\n");
        current = current->next;
    }
}

// Queue
void enqueue(char* name) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    strcpy(newNode->passengerName, name);
    newNode->next = NULL;
    if (rear == NULL) {
        front = rear = newNode;
        return;
    }
    rear->next = newNode;
    rear = newNode;
}

char* dequeue() {
    if (isQueueEmpty()) {
        return NULL;
    }
    QueueNode* temp = front;
    char* name = (char*)malloc(50 * sizeof(char));
    strcpy(name, front->passengerName);
    front = front->next;
    if (front == NULL) {
        rear = NULL;
    }
    free(temp);
    return name;
}

int isQueueEmpty() {
    return front == NULL;
}


void searchFlightsByOrigin(char* origin) {
    Flight* current = availableFlights;
    while (current != NULL) {
        if (strcmp(current->origin, origin) == 0) {
            printf("Flight Number: %s\n", current->flightNumber);
            printf("Origin: %s\n", current->origin);
            printf("Destination: %s\n", current->destination);
            printf("Departure Time: %s\n", current->departureTime);
            printf("-----------------------------\n");
        }
        current = current->next;
    }
}

void cancelBooking(char* flightNumber, char* passengerName) {
    Flight* current = bookedFlights;
    Flight* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->flightNumber, flightNumber) == 0) {
            if (prev == NULL) {
                bookedFlights = current->next;
            } else {
                prev->next = current->next;
            }
            current->next = availableFlights;
            availableFlights = current;

            Ticket* ticketCurrent = tickets;
            Ticket* ticketPrev = NULL;

            while (ticketCurrent != NULL) {
                if (strcmp(ticketCurrent->flightNumber, flightNumber) == 0 && strcmp(ticketCurrent->passengerName, passengerName) == 0) {
                    if (ticketPrev == NULL) {
                        tickets = ticketCurrent->next;
                    } else {
                        ticketPrev->next = ticketCurrent->next;
                    }
                    free(ticketCurrent);
                    printf("Booking for %s on flight %s cancelled successfully.\n", passengerName, flightNumber);
                    return;
                }
                ticketPrev = ticketCurrent;
                ticketCurrent = ticketCurrent->next;
            }
        }
        prev = current;
        current = current->next;
    }
    printf("Booking for %s on flight %s not found.\n", passengerName, flightNumber);
}
