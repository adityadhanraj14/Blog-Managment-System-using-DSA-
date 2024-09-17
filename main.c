#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct data
{
    int sno;
    char username[20];
    char tittle[100];
    char blog[1000];
    struct data *link;
};
typedef struct data *NODE;
int tno[100], k = 0;
NODE get_node(char[]);
NODE insert_blog(NODE[], char[], int );
NODE delete_blog(NODE[], int, int);
void updateFileAfterDelete(NODE [], int );
//NODE search_blog(NODE);
void display_node(NODE, int);
void display(NODE[], int);
void display_tittle(NODE[], int);
void display_all();
void writeCSV(char *, char[], char[], int );
int checkCredentials(char[], char[], char[], int *);
void savetofile(char *, char[], int , char[], char[]);
void getfromfile(char *, NODE [], char [], int *);
NODE insert_savedblog(NODE , char [], int , char [], char []);
void main()
{
    system("clear");
    NODE first[100];
    for (int i = 0; i < 100; i++)
    {
        first[i] = NULL;
    }
    for (int i = 0; i < 100; i++)
    {
        tno[i] = 1;
    }
    char filename[] = "userdata.csv";
    char filename1[] = "blog.csv";
    int choice, sno = 0;
    char username[20];
    char password[20];
    getfromfile(filename1, first, username, &k);
    sno = k;
    printf("\t\t\t\t\t\t\t\t\t\t👋 ======== WELCOME TO BLOGING SITE ======== 👋\n");
    while (1)
    {
    label1:
        printf("\t\t\t\t\t\t\t\t\t\t\t--------------------------------\n");
        //printf("\t\t\t\t\t\t\t\t\t\t\t\tChoose an option: \n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t1. Sign up\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t2. Login\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t3. Exit\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t--------------------------------\n");
        printf("\t\t\t\t\t\t\t\t\t\t\tEnter your choice:");
        scanf(" %d", &choice);
        getchar();

        switch (choice)
        {
        case 1: // Sign up
            printf("\n\t\t\t\t\t\t\t\t\t\t\tEnter username: ");
            scanf("%s", username);

            printf("\t\t\t\t\t\t\t\t\t\t\tEnter password: ");
            scanf("%s", password);
            writeCSV(filename, username, password, k);
            k++;
            printf("\n\t\t\t\t\t\t\t\t\t\t\t    🚀Signup successful!🚀\n\n");
            break;

        case 2: // Login
            printf("\n\t\t\t\t\t\t\t\t\t\t\tEnter username: ");
            scanf("%s", username);

            printf("\t\t\t\t\t\t\t\t\t\t\tEnter password: ");
            scanf("%s", password);

            if (checkCredentials(filename, username, password, &sno))
            {
                printf("\n\t\t\t\t\t\t\t\t\t\t\t    🚀Login successful!🚀\n");
                // printf("your sno: %d\n", sno);
                printf("\n\t\t\t\t\t\t\t\t\t\t\t======== Welcome %s =========\n", username);
                while (1)
                {
                    printf("\t\t\t\t\t\t\t\t\t\t\t-----------------------------\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t\t1. Add blog📝 \n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t\t2. Delete blog🚮\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t\t3. Display blogs📄\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t\t4. Logout📤\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t-----------------------------\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\tEnter your choice: ");
                    scanf(" %d", &choice);
                    getchar();
                    switch (choice)
                    {
                    case 1:
                        first[sno] = insert_blog(first, username, sno);
                        first[sno]->sno = tno[sno]++;
                        savetofile(filename1, username, sno, first[sno]->tittle, first[sno]->blog);
                        break;
                    case 2:
                        display_tittle(first, sno);
                        printf("\t\t\t\t\t\t\t\t\t\t\tEnter sno. you want to delete: ");
                        scanf("%d", &choice);
                        getchar();
                        delete_blog(first, sno, choice);
                        break;
                    case 3:
                        printf("\n\t\t\t\t\t\t\t\t\t\t\t1. Your blog\n\t\t\t\t\t\t\t\t\t\t\t2. All blogs\n");
                        printf("\n\t\t\t\t\t\t\t\t\t\t\tEnter your choice:");
                        scanf("%d", &choice);
                        getchar();
                        if (choice == 1)
                        {
                            display(first, sno);
                            break;
                        }
                        else if (choice == 2)
                            display_all(first);
                        break;
                    case 4:
                        goto label1;
                    }
                }
            }
            else
            {
                printf("\n\t\t\t\t\t\t\t\t\t\t    ⚠️ Invalid username or password. Login failed.⚠️ \n\n");
                break;
            }
        case 3:exit(0);

        default:
            printf("\t\t\t\t\t\t\t\t\t\t\tInvalid choice\n\n");
        }
        
        
    }
}
void writeCSV(char *filename, char *username, char *password, int k)
{
    FILE *file = fopen(filename, "a");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s,%s,%d\n", username, password, k);

    fclose(file);
}
void savetofile(char *filename, char username[], int k, char tittle[], char blog[])
{
    FILE *file = fopen(filename, "a");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Remove newline characters from tittle and blog
    size_t tittle_length = strlen(tittle);
    if (tittle_length > 0 && tittle[tittle_length - 1] == '\n')
    {
        tittle[tittle_length - 1] = '\0';
    }

    size_t blog_length = strlen(blog);
    if (blog_length > 0 && blog[blog_length - 1] == '\n')
    {
        blog[blog_length - 1] = '\0';
    }
    fprintf(file, "%s,%d,%s,%s\n", username, k, tittle, blog);
    
    fclose(file);
}

int checkCredentials(char *filename, char *username, char *password, int *sno)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[50]; // Adjust the size based on your actual data

    while (fgets(line, sizeof(line), file) != NULL)
    {
        char storedUsername[20];
        char storedPassword[20];
        int stored_sno;

        sscanf(line, "%[^,],%[^,],%d", storedUsername, storedPassword, &stored_sno);

        if (strcmp(storedUsername, username) == 0 && strcmp(storedPassword, password) == 0)
        {
            fclose(file);
            *sno = stored_sno;
            return 1; // Credentials match
        }
    }

    fclose(file);
    return 0; // Credentials do not match
}
void getfromfile(char *filename1, NODE first[], char username[], int *sno)
{
    FILE *file = fopen(filename1, "r");
    if (file == NULL)
    {
        return;
    }

    char line[1000];

    while (fgets(line, sizeof(line), file) != NULL)
    {
        char storedUsername[20];
        int stored_sno;
        char storedtittle[100];
        char storedblog[1000];
        sscanf(line, "%[^,],%d,%[^,],%[^\n]", storedUsername, &stored_sno, storedtittle, storedblog);
        first[stored_sno] = insert_savedblog(first[stored_sno], storedUsername, stored_sno, storedtittle, storedblog);
        if (stored_sno >= *sno)
        {
            *sno = (stored_sno + 1);
        }
    }
    fclose(file);
}

NODE get_node(char username[])
{
    NODE temp;
    temp = (NODE)malloc(sizeof(struct data));
    printf("\t\t\t\t\t\t\t\t\t\t\tEnter your title: ");
    fgets(temp->tittle, 100, stdin);
    printf("\t\t\t\t\t\t\t\t\t\t\tEnter your Blog: ");
    fgets(temp->blog, 1000, stdin);
    strcpy(temp->username, username);
    temp->link = NULL;
    return temp;
}
NODE insert_blog(NODE first[], char username[], int sno)
{
    NODE temp;
    temp = get_node(username);
    if (first[sno] == NULL)
    {
        printf("\n\t\t\t\t\t\t\t\t\t\t\t    \U0001F389 Blog posted succesfully \U0001F389\n");
        return temp;
    }
    temp->link = first[sno];
    printf("\n\t\t\t\t\t\t\t\t\t\t\t    \U0001F389 Blog posted succesfully \U0001F389\n");
    return temp;
}
NODE insert_savedblog(NODE head, char username[], int sno, char tittle[], char blog[])
{
    NODE temp;
    temp = (NODE)malloc(sizeof(struct data));
    if (temp == NULL)
    {
        printf("\t\t\t\t\t\t\t\t\t\t\tMemory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    temp->sno = tno[sno]++;
    strcpy(temp->tittle, tittle);
    strcpy(temp->blog, blog);
    strcpy(temp->username, username);
    temp->link = head;

    return temp;
}
NODE delete_blog(NODE first[], int sno, int choice)
{
    NODE temp, prev;
    temp = first[sno];

    // Special case: deleting the first node
    if (temp != NULL && temp->sno == choice)
    {
        first[sno] = temp->link;
        printf("\n\t\t\t\t\t\t\t\t\t\t     ✔️The title '%s' is deleted successfully ✔️\n\n", temp->tittle);
        free(temp);
    }
    else
    {
        // General case: traverse the list to find the node to delete
        prev = temp;
        temp = temp->link;
        while (temp != NULL)
        {
            if (temp->sno == choice)
            {
                prev->link = temp->link;
                printf("\t\t\t\t\t\t\t\t\t\t   ✔️ The title '%s' is deleted successfully ✔️\n\n", temp->tittle);
                free(temp);
                break;
            }
            prev = temp;
            temp = temp->link;
        }

        // Node with the given choice not found
        if (temp == NULL)
        {
            printf("\n\t\t\t\t\t\t\t\t\t\t\t    ❌ Node with sno %d not found.❌\n",choice);
        }
    }

    // Update the file after deleting the blog
    updateFileAfterDelete(first, sno);

    return first[sno];
}

void updateFileAfterDelete(NODE first[], int sno)
{
    FILE *file = fopen("blog.csv", "w");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i <= k; i++)
    {
        NODE temp = first[i];
        while (temp != NULL)
        {
            fprintf(file, "%s,%d,%s,%s\n", temp->username, i, temp->tittle, temp->blog);
            temp = temp->link;
        }
    }

    fclose(file);
    // printf("File updated successfully after deleting the blog.\n");
}

void display_node(NODE temp, int sno)
{
    printf("\t\t\t\t\t\t\t\t\t\t\t%d Title: %s\n\t\t\t\t\t\t\t\t\t\t\t\tBlog: %s\n",temp->sno,temp->tittle, temp->blog);
    //printf("Sl.no of this tittle is %d\n", temp->sno);
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\twritten by - %s\n\n", temp->username);
    return;
}
void display(NODE first[1], int sno)
{
    if (first[sno] == NULL)
    {
        printf("\n\t\t\t\t\t\t\t\t\t\t\t    🚫 NO BLOGS PRESENT 🚫 \n");
        return;
    }
    NODE temp;
    int count = 0;
    temp = first[sno];
    printf("\n\t\t\t\t\t\t\t\t\t\t    ========= Your Blogs =========\n");
    printf("\t\t\t\t\t\t\t\t\t\t    ╔══════════════════════════════════════════════════════════════════════════════════╗\n");
    while (temp != NULL)
    {
        display_node(temp, sno);
        temp = temp->link;
        count++;
        if (temp != NULL)
                printf("\t\t\t\t\t\t\t\t\t\t      ╠═══════════════════════════════════════════════════╣\n");
    }
        printf("\t\t\t\t\t\t\t\t\t\t    ╚══════════════════════════════════════════════════════════════════════════════════╝\n");
}
void display_tittle(NODE first[], int sno)
{

    if (first[sno] == NULL)
    {
        printf("\n\t\t\t\t\t\t\t\t\t\t\t    🚫 NO BLOG PRSENT 🚫\n");
        return;
    }
    NODE temp;
    temp = first[sno];
    for (int i = 1; i < tno[sno]; i++)
    {
        printf("\n\t\t\t\t\t\t\t\t\t\t\t%d. %s\n", temp->sno, temp->tittle);
        temp = temp->link;
    }
}

/*NODE search_blog(NODE first){
    return NULL;06
}*/
void display_all(NODE first[])
{
    printf("\n\t\t\t\t\t\t\t\t\t\t    ========= All Blogs =========\n");
    int i, count = 0;

    for (i = 0; i < k; i++)
    {
        NODE temp = first[i];
        if (temp != NULL)
        {
            printf("\t\t\t\t\t\t\t\t\t\t    ╔══════════════════════════════════════════════════════════════════════════════════╗\n");
            printf("\n\t\t\t\t\t\t\t\t\t\t\tUser: %s\n", temp->username);
            while (temp != NULL)
            {
                display_node(temp, i);
                temp = temp->link;
                count++;
                if (temp != NULL)
                    printf("\t\t\t\t\t\t\t\t\t\t      ╠═══════════════════════════════════════════════════╣\n");
            }
            printf("\t\t\t\t\t\t\t\t\t\t    ╚══════════════════════════════════════════════════════════════════════════════════╝\n");
        }
    }

    if (count == 0)
    {
        printf("\t\t\t\t\t\t\t\t\t\t\tNo blogs found.\n");
    }
}
