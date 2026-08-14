#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

typedef struct Volunteer
{
    int id;
    char name[50];
    char phone[20];
    char area[30];
    int lost;
    struct Volunteer *next;
} Volunteer;

Volunteer *head = NULL;


typedef struct Activity
{
    char text[100];
    struct Activity *next;
} Activity;

Activity *activityHead = NULL;


typedef struct Request
{
    int id;
    char name[50];
    char area[30];
    char problem[100];
    struct Request *next;
} Request;

Request *front = NULL;
Request *rear = NULL;



typedef struct Alert
{
    char text[100];
    struct Alert *next;
} Alert;

Alert *top = NULL;



char areas[MAX][30];
int graph[MAX][MAX];
int areaCount = 0;


typedef struct Tree
{
    char name[30];
    struct Tree *left;
    struct Tree *right;
} Tree;

Tree *root = NULL;



void addVolunteer();
void displayVolunteers();
void searchVolunteer();
void updateLocation();
void markLost();
void showLostVolunteers();

void addActivity(char text[]);
void showActivities();

void addRequest();
void processRequest();
void showRequests();

void pushAlert(char text[]);
void popAlert();
void showAlerts();

void addArea();
void connectAreas();
void showGraph();
void findRoute();

Tree *insertTree(Tree *root, char name[]);
void showTree(Tree *root, int level);
void createTree();

void menu();


void addActivity(char text[])
{
    Activity *newNode;
    Activity *temp;

    newNode = (Activity *)malloc(sizeof(Activity));

    strcpy(newNode->text, text);
    newNode->next = NULL;

    if(activityHead == NULL)
    {
        activityHead = newNode;
    }
    else
    {
        temp = activityHead;

        while(temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }
}


void showActivities()
{
    Activity *temp;

    printf("\n========== ACTIVITY FEED ==========\n");

    if(activityHead == NULL)
    {
        printf("No activity available.\n");
        return;
    }

    temp = activityHead;

    while(temp != NULL)
    {
        printf("- %s\n", temp->text);
        temp = temp->next;
    }
}



void addVolunteer()
{
    Volunteer *newNode;
    char message[100];

    newNode = (Volunteer *)malloc(sizeof(Volunteer));

    printf("\nEnter Volunteer ID: ");
    scanf("%d", &newNode->id);

    printf("Enter Volunteer Name: ");
    scanf(" %[^\n]", newNode->name);

    printf("Enter Phone Number: ");
    scanf(" %[^\n]", newNode->phone);

    printf("Enter Current Area: ");
    scanf(" %[^\n]", newNode->area);

    newNode->lost = 0;
    newNode->next = NULL;

    if(head == NULL)
    {
        head = newNode;
    }
    else
    {
        Volunteer *temp = head;

        while(temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }

    sprintf(message, "Volunteer %d (%s) joined at %s.",
            newNode->id, newNode->name, newNode->area);

    addActivity(message);

    printf("\nVolunteer added successfully.\n");
}


void displayVolunteers()
{
    Volunteer *temp;

    printf("\n========== VOLUNTEER LIST ==========\n");

    if(head == NULL)
    {
        printf("No volunteers found.\n");
        return;
    }

    temp = head;

    while(temp != NULL)
    {
        printf("\nID       : %d", temp->id);
        printf("\nName     : %s", temp->name);
        printf("\nPhone    : %s", temp->phone);
        printf("\nLocation : %s", temp->area);

        if(temp->lost == 1)
            printf("\nStatus   : LOST\n");
        else
            printf("\nStatus   : SAFE\n");

        temp = temp->next;
    }
}


void searchVolunteer()
{
    Volunteer *temp;
    int id;
    int found = 0;

    printf("\nEnter Volunteer ID: ");
    scanf("%d", &id);

    temp = head;

    while(temp != NULL)
    {
        if(temp->id == id)
        {
            printf("\nVolunteer Found\n");
            printf("Name     : %s\n", temp->name);
            printf("Phone    : %s\n", temp->phone);
            printf("Location : %s\n", temp->area);

            if(temp->lost == 1)
                printf("Status   : LOST\n");
            else
                printf("Status   : SAFE\n");

            found = 1;
            break;
        }

        temp = temp->next;
    }

    if(found == 0)
    {
        printf("\nVolunteer not found.\n");
    }
}


void updateLocation()
{
    Volunteer *temp;
    int id;
    char newArea[30];
    char message[100];

    printf("\nEnter Volunteer ID: ");
    scanf("%d", &id);

    temp = head;

    while(temp != NULL)
    {
        if(temp->id == id)
        {
            printf("Current Location: %s\n", temp->area);

            printf("Enter New Location: ");
            scanf(" %[^\n]", newArea);

            strcpy(temp->area, newArea);

            sprintf(message, "%s moved to %s.",
                    temp->name, temp->area);

            addActivity(message);

            printf("\nLocation updated successfully.\n");
            return;
        }

        temp = temp->next;
    }

    printf("\nVolunteer not found.\n");
}


void markLost()
{
    Volunteer *temp;
    int id;
    char message[100];

    printf("\nEnter Volunteer ID: ");
    scanf("%d", &id);

    temp = head;

    while(temp != NULL)
    {
        if(temp->id == id)
        {
            temp->lost = 1;

            sprintf(message, "ALERT: Volunteer %s is reported LOST.",
                    temp->name);

            addActivity(message);
            pushAlert(message);

            printf("\nVolunteer marked as LOST.\n");
            return;
        }

        temp = temp->next;
    }

    printf("\nVolunteer not found.\n");
}


void showLostVolunteers()
{
    Volunteer *temp;
    int found = 0;

    printf("\n========== LOST VOLUNTEERS ==========\n");

    temp = head;

    while(temp != NULL)
    {
        if(temp->lost == 1)
        {
            printf("\nID       : %d", temp->id);
            printf("\nName     : %s", temp->name);
            printf("\nPhone    : %s", temp->phone);
            printf("\nLast Area: %s\n", temp->area);

            found = 1;
        }

        temp = temp->next;
    }

    if(found == 0)
    {
        printf("\nNo lost volunteer found.\n");
    }
}




void addRequest()
{
    Request *newNode;

    newNode = (Request *)malloc(sizeof(Request));

    printf("\nEnter Request ID: ");
    scanf("%d", &newNode->id);

    printf("Enter Person Name: ");
    scanf(" %[^\n]", newNode->name);

    printf("Enter Area: ");
    scanf(" %[^\n]", newNode->area);

    printf("Enter Problem: ");
    scanf(" %[^\n]", newNode->problem);

    newNode->next = NULL;

    if(front == NULL)
    {
        front = newNode;
        rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }

    printf("\nRelief request added to queue.\n");
}


void processRequest()
{
    Request *temp;

    if(front == NULL)
    {
        printf("\nNo pending request.\n");
        return;
    }

    temp = front;

    printf("\n========== PROCESSING REQUEST ==========\n");
    printf("Request ID : %d\n", temp->id);
    printf("Person     : %s\n", temp->name);
    printf("Area       : %s\n", temp->area);
    printf("Problem    : %s\n", temp->problem);

    front = front->next;

    if(front == NULL)
    {
        rear = NULL;
    }

    free(temp);

    printf("\nRequest processed successfully.\n");
}


void showRequests()
{
    Request *temp;

    printf("\n========== PENDING REQUESTS ==========\n");

    if(front == NULL)
    {
        printf("No pending requests.\n");
        return;
    }

    temp = front;

    while(temp != NULL)
    {
        printf("\nRequest ID : %d", temp->id);
        printf("\nPerson     : %s", temp->name);
        printf("\nArea       : %s", temp->area);
        printf("\nProblem    : %s\n", temp->problem);

        temp = temp->next;
    }
}




void pushAlert(char text[])
{
    Alert *newNode;

    newNode = (Alert *)malloc(sizeof(Alert));

    strcpy(newNode->text, text);

    newNode->next = top;
    top = newNode;
}


void popAlert()
{
    Alert *temp;

    if(top == NULL)
    {
        printf("\nNo alert available.\n");
        return;
    }

    temp = top;

    printf("\nLatest Alert: %s\n", temp->text);

    top = top->next;

    free(temp);
}


void showAlerts()
{
    Alert *temp;

    printf("\n========== RECENT ALERTS ==========\n");

    if(top == NULL)
    {
        printf("No alerts available.\n");
        return;
    }

    temp = top;

    while(temp != NULL)
    {
        printf("- %s\n", temp->text);
        temp = temp->next;
    }
}



void addArea()
{
    if(areaCount >= MAX)
    {
        printf("\nMaximum area limit reached.\n");
        return;
    }

    printf("\nEnter Area Name: ");
    scanf(" %[^\n]", areas[areaCount]);

    areaCount++;

    printf("\nArea added successfully.\n");
}


int getAreaNumber(char name[])
{
    int i;

    for(i = 0; i < areaCount; i++)
    {
        if(strcmp(areas[i], name) == 0)
        {
            return i;
        }
    }

    return -1;
}


void connectAreas()
{
    char area1[30];
    char area2[30];

    int a;
    int b;

    printf("\nEnter First Area: ");
    scanf(" %[^\n]", area1);

    printf("Enter Second Area: ");
    scanf(" %[^\n]", area2);

    a = getAreaNumber(area1);
    b = getAreaNumber(area2);

    if(a == -1 || b == -1)
    {
        printf("\nArea not found.\n");
        return;
    }

    graph[a][b] = 1;
    graph[b][a] = 1;

    printf("\nAreas connected successfully.\n");
}


void showGraph()
{
    int i;
    int j;

    printf("\n========== AREA CONNECTIONS ==========\n");

    for(i = 0; i < areaCount; i++)
    {
        printf("\n%s -> ", areas[i]);

        for(j = 0; j < areaCount; j++)
        {
            if(graph[i][j] == 1)
            {
                printf("%s  ", areas[j]);
            }
        }
    }

    printf("\n");
}


void findRoute()
{
    char startName[30];
    char endName[30];

    int start;
    int end;

    int queue[MAX];
    int front2 = 0;
    int rear2 = 0;

    int visited[MAX] = {0};
    int parent[MAX];

    int i;
    int current;

    printf("\nEnter Starting Area: ");
    scanf(" %[^\n]", startName);

    printf("Enter Destination Area: ");
    scanf(" %[^\n]", endName);

    start = getAreaNumber(startName);
    end = getAreaNumber(endName);

    if(start == -1 || end == -1)
    {
        printf("\nArea not found.\n");
        return;
    }

    for(i = 0; i < MAX; i++)
    {
        parent[i] = -1;
    }

    queue[rear2] = start;
    rear2++;

    visited[start] = 1;

    while(front2 < rear2)
    {
        current = queue[front2];
        front2++;

        if(current == end)
        {
            break;
        }

        for(i = 0; i < areaCount; i++)
        {
            if(graph[current][i] == 1 && visited[i] == 0)
            {
                visited[i] = 1;
                parent[i] = current;

                queue[rear2] = i;
                rear2++;
            }
        }
    }

    if(visited[end] == 0)
    {
        printf("\nNo route found between these areas.\n");
        return;
    }

    printf("\nRoute found using BFS:\n");

    int path[MAX];
    int count = 0;

    current = end;

    while(current != -1)
    {
        path[count] = current;
        count++;

        current = parent[current];
    }

    for(i = count - 1; i >= 0; i--)
    {
        printf("%s", areas[path[i]]);

        if(i != 0)
        {
            printf(" -> ");
        }
    }

    printf("\n");
}




Tree *insertTree(Tree *root, char name[])
{
    if(root == NULL)
    {
        Tree *newNode;

        newNode = (Tree *)malloc(sizeof(Tree));

        strcpy(newNode->name, name);

        newNode->left = NULL;
        newNode->right = NULL;

        return newNode;
    }

    if(strcmp(name, root->name) < 0)
    {
        root->left = insertTree(root->left, name);
    }
    else
    {
        root->right = insertTree(root->right, name);
    }

    return root;
}


void showTree(Tree *root, int level)
{
    int i;

    if(root == NULL)
    {
        return;
    }

    showTree(root->right, level + 1);

    for(i = 0; i < level; i++)
    {
        printf("    ");
    }

    printf("|-- %s\n", root->name);

    showTree(root->left, level + 1);
}


void createTree()
{
    root = NULL;

    root = insertTree(root, "Relief Center");
    root = insertTree(root, "Area A");
    root = insertTree(root, "Area B");
    root = insertTree(root, "Area C");
    root = insertTree(root, "Area D");
    root = insertTree(root, "Medical Camp");
    root = insertTree(root, "Food Camp");

    printf("\nRelief area tree created.\n");
}




void menu()
{
    int choice;

    while(1)
    {
        printf("\n\n");
        printf("============================================\n");
        printf("      FLOOD RELIEF VOLUNTEER TRACKER\n");
        printf("============================================\n");

        printf("\n--- Volunteer Management ---\n");
        printf("1. Add Volunteer\n");
        printf("2. Display All Volunteers\n");
        printf("3. Search Volunteer\n");
        printf("4. Update Volunteer Location\n");
        printf("5. Mark Volunteer as Lost\n");
        printf("6. Show Lost Volunteers\n");

        printf("\n--- Relief Request Queue ---\n");
        printf("7. Add Relief Request\n");
        printf("8. Process Relief Request\n");
        printf("9. Show Pending Requests\n");

        printf("\n--- Emergency Alert Stack ---\n");
        printf("10. Show Recent Alerts\n");
        printf("11. Remove Latest Alert\n");

        printf("\n--- Flood Area Graph ---\n");
        printf("12. Add Flood Area\n");
        printf("13. Connect Two Areas\n");
        printf("14. Show Area Connections\n");
        printf("15. Find Route Between Areas\n");

        printf("\n--- Relief Area Tree ---\n");
        printf("16. Create Relief Area Tree\n");
        printf("17. Show Relief Area Tree\n");

        printf("\n--- Activity Feed ---\n");
        printf("18. Show Activity Feed\n");

        printf("\n19. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addVolunteer();
                break;

            case 2:
                displayVolunteers();
                break;

            case 3:
                searchVolunteer();
                break;

            case 4:
                updateLocation();
                break;

            case 5:
                markLost();
                break;

            case 6:
                showLostVolunteers();
                break;

            case 7:
                addRequest();
                break;

            case 8:
                processRequest();
                break;

            case 9:
                showRequests();
                break;

            case 10:
                showAlerts();
                break;

            case 11:
                popAlert();
                break;

            case 12:
                addArea();
                break;

            case 13:
                connectAreas();
                break;

            case 14:
                showGraph();
                break;

            case 15:
                findRoute();
                break;

            case 16:
                createTree();
                break;

            case 17:
                if(root == NULL)
                {
                    printf("\nPlease create the tree first.\n");
                }
                else
                {
                    printf("\n========== RELIEF AREA TREE ==========\n");
                    showTree(root, 0);
                }
                break;

            case 18:
                showActivities();
                break;

            case 19:
                printf("\nThank you.\n");
                exit(0);

            default:
                printf("\nWrong choice.\n");
        }
    }
}


int main()
{
    menu();

    return 0;
}
