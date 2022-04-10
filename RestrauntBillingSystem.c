/* Restraunt Billing System by 
Sumant Reddy, Roll no: 71, Gr No: 11910283
Class: IcB-B3
Data Structure Course Project */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//defining a node

struct node
{
    char foodname[25];
    int quantity;
    float price;
    int data;
    struct node *next;
};

// global pointers declaration

struct node *headc = NULL,*newnode,*tailc = NULL;
struct node *heada = NULL, *taila = NULL;
struct node *head_s;


// Creates node for admin Linked List

struct node* createadmin(struct node *head,int data, char foodname[25], float price)
{
    newnode = (struct node*)malloc(sizeof(struct node));  //Memory allocation for the node

    newnode->data = data;
    newnode->price = price;
    newnode-> quantity = 0;
    strcpy(newnode->foodname,foodname);
    newnode->next = NULL;

    // checks whether a linked list is empty or not

    struct node *temp = head;

    if(temp==NULL)
        heada = taila = newnode;
    else
    {
        while(temp->next!=NULL)
            temp=temp->next;

        temp->next=newnode;
        taila = newnode;
    }

    return heada;
}

// Creates node for user linked list

struct node* createcustomer(struct node *head,int data,int quantity)
{
    newnode = (struct node*)malloc(sizeof(struct node));

    // Checks whether food is present in menu list or not

    struct node *temp1 = heada;
    int flag = 0;

    while(temp1!=NULL)
    {
        if(temp1->data==data)
        {
            flag = 1;
            break;
        }
        temp1 = temp1->next;
    }

    if(flag==1)
    {
        newnode->data = data;
        newnode->price = quantity*(temp1->price);
        newnode-> quantity = quantity;
        strcpy(newnode->foodname,temp1->foodname);
        newnode->next = NULL;

        struct node *temp = head;

        if(temp==NULL)
            headc = tailc = newnode;
        else
        {
            while(temp->next!=NULL)
                temp=temp->next;

            temp->next=newnode;
            tailc = newnode;
        }


    }
    else
    {
        printf("\n\t\t\t\t\t\t\tSorry !! This item is not present in the menu!\n");
    }
    return headc;
}

// Displays a linked list who's head pointer is passed

void displayList(struct node *head)
{
    struct node *temp1 = head;
    // Checks Whether linked list is empty or not

    if(temp1==NULL)
    {
        printf("\n\t\t\t\t\t\t\t\tList is empty!!\n\n");
    }
    else
    {
        printf("\n");
        while(temp1!=NULL)
        {
            if(temp1->quantity==0) // For Admin 
                printf("\t\t\t\t\t\t\t%d\t%s\t%0.2f\n",temp1->data,temp1->foodname,temp1->price);
            else
            {
                printf("\t\t\t\t\t\t\t%d\t%s\t%d\t%0.2f\n",temp1->data,temp1->foodname,temp1->quantity,temp1->price);
            }

            temp1 = temp1->next;
        }
        printf("\n");
    }

}

// For Calculating Total Sales 

struct node* totalsales(int data,int quantity)
{
    newnode = (struct node*)malloc(sizeof(struct node));
    int flag = 0;

    struct node *temp1 = heada;
    while(temp1->data!=data)   //Admin Linked List Traversal
    {
        temp1 = temp1->next;
    }

    newnode->data = data;
    newnode->price = quantity*(temp1->price);
    newnode-> quantity = quantity;
    strcpy(newnode->foodname,temp1->foodname);
    newnode->next = NULL;

    struct node *temp = head_s;

    // Sales Linked List Traversal 

    if(temp==NULL)
        head_s = newnode;
    else
    {
        while(temp->next!=NULL)
        {
            if(temp->data==data)
            {
                flag = 1;
                break;
            }
            temp=temp->next;
        }

        if(flag==1)
        {
            temp->quantity += newnode-> quantity;
            temp->price += newnode->price;
        }
        else
        {
            temp->next=newnode;
        }
    }

    return head_s;
}

void calculatetotsales()
{
    struct node *temp = headc;
    while(temp!=NULL)
    {
        head_s = totalsales(temp->data, temp->quantity);
        temp=temp->next;
    }
}

// deleting a node for user and admin linked list

struct node* delete(int data,struct node *head, struct node*tail)
{
    if(head==NULL)  // Checks if list is empty or not
    {
        printf("\n\t\t\t\t\t\t\tList is empty\n");
    }
    else
    {
        struct node* temp; 
        if(data==head->data)  // If head Node
        {
            temp = head;
            head = head->next;
            free(temp);
        }
        else if(data==tail->data)  // If tail Node
        {
            temp = tail;
            tail->next = NULL;
            free(temp);
        }
        else
        {
            temp = head;
            struct node* temp1 = temp;
            while(data!=temp->data)
            {
                temp1 = temp;
                temp = temp->next;
            }
            temp1->next = temp->next;
            free(temp);
        }
    }
    return head;
}

int deleteadmin()
{
    printf("\n\t\t\t\t\tEnter serial no. of the food item which is to be deleted: ");
    int num;
    scanf("%d",&num);

    struct node* temp=heada;

    while(temp!=NULL)
    {
        if (temp->data == num)
        {
            heada = delete(num, heada, taila);
            return 1;
        }
        temp=temp->next;
    }

    return 0;
}

int deletecustomer()
{
    printf("\n\t\t\t\t\tEnter serial no. of the food item which is to be deleted: ");
    int num;
    scanf("%d",&num);

    struct node* temp=headc;
    while(temp!=NULL)
    {
        if (temp->data == num)
        {
            headc = delete(num, headc, tailc);
            return 1;
        }
        temp=temp->next;
    }

    return 0;
}

void displaybill()
{
    displayList(headc);
    struct node *temp = headc;
    float total_price = 0;
    while (temp!=NULL)
    {
        total_price +=(temp->quantity)*(temp->price);
        temp = temp->next;
    }

    printf("\t\t\t\t\t\t\tTotal price: %0.02f\n",total_price);

}

struct node* deleteList(struct node* head)
{
    if(head==NULL)
    {
        return NULL;
    }
    else
    {
        struct node* n, *temp=head;
        while(temp->next!=0)
        {
            n = temp->next;
            free(temp);
        }
        free(temp);
        head = NULL;
    }

    return head;
}

void mainnenu()
{
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("\n                                 **************************************************************************\n");
    printf("                                                     WELCOME TO RESTAURANT BILLING SYSTEM\n");
    printf("                                 **************************************************************************\n\n\n");
    printf("\t\t\t\t\t\t\t1. ADMIN SECTION--> \n");
    printf("\t\t\t\t\t\t\t2. CUSTOMER SECTION--> \n");
    printf("\t\t\t\t\t\t\t3. Exit--> \n\n");
    printf("\t\t\t\t\t\t\tEnter Your Choice --->");
}

// Admin menu Function

void adminmenu()
{
    printf("\n\t\t\t\t\t\t\t1. View total sales\n");
    printf("\t\t\t\t\t\t\t2. Add new items in the order menu\n");
    printf("\t\t\t\t\t\t\t3. Delete items from the order menu\n");
    printf("\t\t\t\t\t\t\t4. Display order menu\n");
    printf("\t\t\t\t\t\t\t5. Back To Main Menu \n\n");
    printf("\t\t\t\t\t\t\t   Enter Your Choice --->");
}


void admin()
{
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("\n\t\t\t\t\t   ----------------------------------------------\n");
    printf("\t\t\t\t\t\t\t    ADMIN SECTION\n");
    printf("\t\t\t\t\t   ----------------------------------------------\n");
    while(1)
    {
        adminmenu();

        int opt;
        scanf("%d",&opt);

        if(opt==5)
            break;

        switch (opt)
        {
            case 1:
                displayList(head_s);
                break;
            case 2:

                printf("\n\t\t\t\t\t\t\tEnter serial no. of the food item: ");
                int num,flag = 0;
                char name[50];
                float price;
                scanf("%d",&num);

                struct node *temp = heada;

                while(temp!=NULL)
                {
                    if(temp->data==num)
                    {
                        printf("\n\t\t\t\t\t\tFood item with given serial number already exists!!\n\n");
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                if(flag==1)
                    break;

                printf("\t\t\t\t\t\t\tEnter food item name: ");
                scanf("%s",name);
                printf("\t\t\t\t\t\t\tEnter price: ");
                scanf("%f",&price);
                heada = createadmin(heada, num, name, price);
                printf("\n\t\t\t\t\t\t\tNew food item added to the list!!\n\n");
                break;
            case 3:
                if(deleteadmin())
                {
                    printf("\n\t\t\t\t\t\t### Updated list of food items menu ###\n");
                    displayList(heada);
                }
                else
                    printf("\n\t\t\t\t\t\tFood item with given serial number doesn't exist!\n\n");

                break;
            case 4:
                printf("\n\t\t\t\t\t\t\t   ### Order menu ###\n");
                displayList(heada);
                break;

            default:
                printf("\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n");
                break;
        }
    }
}


// Customer menu Function

void customermenu()
{
    printf("\n\t\t\t\t\t\t\t1. Place your order\n");
    printf("\t\t\t\t\t\t\t2. View your ordered items\n");
    printf("\t\t\t\t\t\t\t3. Delete an item from order\n");
    printf("\t\t\t\t\t\t\t4. Display final bill\n");
    printf("\t\t\t\t\t\t\t5. Back To Main Menu \n\n");
    printf("\t\t\t\t\t\t\t   Enter Your Choice --->");
}


void customer()
{
    int flag=0,j=1;
    char ch;
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("\n\t\t\t\t\t   ----------------------------------------------\n");
    printf("\t\t\t\t\t\t\t    CUSTOMER SECTION\n");
    printf("\t\t\t\t\t   ----------------------------------------------\n");
    while(1)
    {
        customermenu();

        int opt;
        scanf("%d",&opt);

        if(opt==5)
            break;

        switch (opt)
        {
            case 1:
                displayList(heada);
                printf("\n\t\t\t\t\t\tEnter number corresponding to the item you want to order: ");
                int n;
                scanf("%d",&n);
                printf("\t\t\t\t\t\tEnter quantity: ");
                int quantity;
                scanf("%d",&quantity);
                headc = createcustomer(headc, n, quantity);
                break;
            case 2:
                printf("\n\t\t\t\t\t\t\t  ### List of ordered items ###\n");
                displayList(headc);
                break;
            case 3:
                if(deletecustomer())
                {
                    printf("\n\t\t\t\t\t\t### Updated list of your ordered food items ###\n");
                    displayList(headc);
                }
                else
                    printf("\n\t\t\t\t\t\tFood item with given serial number doesn't exist!!\n");
                break;
            case 4:
                calculatetotsales();
                printf("\n\t\t\t\t\t\t\t  ### Final Bill ###\n");
                displaybill();
                headc = deleteList(headc);
                printf("\n\t\t\t\t\t\tPress any key to return to main menu:\n\t\t\t\t\t\t");
                fflush(stdin);
                ch=fgetc(stdin);
                flag=1;
                break;

            default:
                printf("\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n");
                break;
        }
        if(flag==1)
            break;
    }
}


int main()
{
    heada = createadmin(heada,1,"Egg Shakshauka",50);
    heada = createadmin(heada,2,"Half Fried Omlette",40);
    heada = createadmin(heada,3,"Spanish Omlette",120);
    heada = createadmin(heada,4,"Chesse cake",180);
    heada = createadmin(heada,5,"Mango Jelly Pudding",150);

    while(1)
    {
        mainnenu();
        int choice;
        scanf("%d",&choice);

        if(choice==3)
        {
            printf("\n\n\t\t\t\t\t\t\t**********Thank you!!**********\n");
            break;
        }

        switch (choice)
        {
            case 1:
                admin();
                break;
            case 2:
                customer();
                break;
            case 3:
                break;

            default:
                printf("\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n");
                break;
        }
    }
}