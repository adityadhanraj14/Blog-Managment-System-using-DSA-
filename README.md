# Blog Managment System
Basically here we made a blog managment system using concept of DSA called linked list.
In this project we are using concept of array of linked list, which means for each user we have a head of linked list whenever user post blog it's add in his linked list respectively. 
Using linked list we can easily preview the blog and give acess to change and delete his own blog. 
you can use this project in your pbl for you college.
Special features: It not losts there data when you terminate the program it's stroe the data in file. whenever you re compile it, it fetch the data and display all the content. Fot this we use file handling and we are storing the data in csv file i.e comma seperated value which help us to track the data.

## Features

- **User Authentication:** Users can sign up and log in to the system.
- **Linked List Structure:** Each user has their own linked list of blogs, allowing for efficient insertion, deletion, and traversal of their posts.
- **Persistent Data Storage:** User data and blog posts are stored in CSV files (`userdata.csv` and `blog.csv`). The system retrieves data from these files upon startup, ensuring that blogs are not lost when the program terminates.
- **Blog Management:** Users can add, delete, and view their blogs. They can also view blogs of all users.
- **File Handling:** Uses file handling to store and retrieve user and blog data, ensuring persistence across sessions.

## Demo

### Signup
![Signup](assets/signup)

### Authentication
![Authentication](assets/Authentication)

### Login
![Login](assets/Login)

### Adding Blog
![Adding Blog](assets/Addingblog)

### Displaying Blog
![Displaying Blog](assets/DisplayBLog)

### Deleting Blog
![Deleting Blog](assets/DeletingBlog)


## How It Works

### Data Structure
- An array of linked lists is used, where each index of the array represents a user, and each linked list contains the blogs of that user.
- The linked list nodes contain the following fields:
  - `sno`: Serial number of the blog
  - `username`: Username of the blog author
  - `tittle`: Title of the blog
  - `blog`: Content of the blog
  - `link`: Pointer to the next blog node

### User Flow

1. **Sign Up / Login:**  
   - Users can sign up by providing a username and password, which are stored in the `userdata.csv` file.
   - Users can log in using their credentials. If the login is successful, they can manage their blogs.
   
2. **Blog Management:**  
   - **Add Blog:** Users can add a new blog post, which is inserted into their linked list and saved to `blog.csv`.
   - **Delete Blog:** Users can delete a blog by specifying its serial number. The linked list and the CSV file are updated accordingly.
   - **View Blogs:** Users can view their own blogs or all blogs from other users.

3. **Data Persistence:**  
   - Upon startup, the program reads data from the CSV files to populate the linked lists, ensuring that all previous data is loaded.

## Code Overview

- **Main Functions:**
  - `main()`: The main function to drive the program, handling user input for signing up, logging in, and managing blogs.
  - `get_node()`: Creates a new blog node with user input.
  - `insert_blog()`: Adds a new blog to the user's linked list.
  - `delete_blog()`: Removes a blog from the user's linked list and updates the file.
  - `display()`, `display_all()`, `display_node()`: Functions to display blogs.
  - `writeCSV()`, `savetofile()`, `getfromfile()`, `updateFileAfterDelete()`: Functions for file handling to save and retrieve data.

- **File Storage:**
  - `userdata.csv`: Stores usernames and passwords.
  - `blog.csv`: Stores blog posts with associated user data.

## Special Features

- **Data Persistence:** All user and blog data is stored in CSV files (`userdata.csv` and `blog.csv`). The program retrieves this data when it starts, ensuring that no data is lost between sessions.
- **Efficient Blog Management:** Using an array of linked lists makes it easy to manage blogs for each user individually.

 ## Getting Started

 ### Prerequisites
- C compiler (e.g., GCC)
- Basic understanding of linked lists and file handling in C

### Running the Program

1. Open a terminal and navigate to the directory containing `main.c`.

2. Compile the program:
   ```bash
   gcc main.c
   ./a.out
 

