# Word Dictionary Using Binary Search Tree (BST) and GTK+

This project is a graphical **Word Dictionary** application built in **C**. It utilizes a **Binary Search Tree (BST)** as its core data structure for efficient word storage and retrieval, and the **GTK+** library to provide a user-friendly Graphical User Interface (GUI). 

This `README` is intended to provide a comprehensive explanation of the project's logic, concepts, and functions. It is structured to help you easily extract points for a PowerPoint Presentation (PPT).

---

## 1. Core Concept: Why a Binary Search Tree?

A **Binary Search Tree (BST)** is a node-based binary tree data structure where each node has at most two child nodes (left and right). For this dictionary application, the BST provides significantly faster operations than a simple array or linked list. 

**BST Rules used in this project:**
- The left subtree of a node contains only words that are **alphabetically smaller** than the node's word.
- The right subtree of a node contains only words that are **alphabetically greater** than the node's word.
- This sorting is achieved using the `strcmp()` function in C.

**Advantages of BST for a Dictionary (PPT Points):**
* **Fast Search:** Instead of checking every word, the search space is halved at each step (O(log n) time complexity).
* **Sorted Retrieval:** An *In-Order Traversal* automatically retrieves the words in perfect alphabetical order.
* **Dynamic Sizing:** Memory is allocated dynamically as words are added, unlike arrays with a fixed size.

---

## 2. Structure of the Project

The code represents two main sections working together:
1.  **The Backend (Data Structure):** Core C logic handling the BST operations (`insert`, `search`, `inorder`).
2.  **The Frontend (GUI):** The graphical interface allowing the user to interact with the backend using buttons and text fields via GTK+.

---

## 3. Important Functions & Logic (Detailed Explanation)

### A. The Data Structure Definitions
```c
struct Node {
    char word[50];
    struct Node *left;
    struct Node *right;
};
```
*   **Concept:** This defines a single block (or node) in the tree.
*   **Components:** 
    *   `word[50]`: Stores the string (maximum 49 characters + null terminator).
    *   `*left`: Pointer to the left child (alphabetically preceding words).
    *   `*right`: Pointer to the right child (alphabetically succeeding words).

### B. Core BST Functions

#### 1. `createNode(char word[])`
*   **Purpose:** Initializes a brand new node.
*   **Logic:** It uses `malloc` to request memory for one node. It copies the given string into the node's `word` attribute, sets both left and right pointers to `NULL` (meaning it has no children yet), and returns the new node.

#### 2. `insert(struct Node* root, char word[])`
*   **Purpose:** Adds a new word to the BST in its correct alphabetical position.
*   **Logic:** 
    *   **Base Case:** If the tree (or current subtree) is empty (`!root`), it calls `createNode()` and places the new word there.
    *   **Recursive Step:** It compares the new word to the current node's word using `strcmp()`.
        *   If `strcmp < 0` (new word comes strictly *before* the current word alphabetically), it travels down the **left** subtree.
        *   If `strcmp > 0` (new word comes *after*), it travels down the **right** subtree.
    *   By doing this recursively, the pointer travels the tree until it finds an empty spot (`NULL`) to plant the new node.

#### 3. `search(struct Node* root, char word[])`
*   **Purpose:** Checks if a word exists in the dictionary.
*   **Logic:**
    *   **Base Case 1:** If the pointer reaches `NULL` (`!root`), the word is not in the tree; returns `0` (False).
    *   **Base Case 2:** If `strcmp() == 0`, the exact word is found; returns `1` (True).
    *   **Recursive Step:** Similar to insert, if the word to find is alphabetically smaller, it recursively searches the `left` subtree. If larger, it searches the `right` subtree.

#### 4. `inorder(struct Node* root, GtkTextBuffer *buffer)`
*   **Purpose:** Displays all words in alphabetical order on the GUI.
*   **Logic:** An *in-order traversal* visits nodes in the following sequence: **Left Subtree → Root Node → Right Subtree**.
    *   By going extremely far left first, it grabs the words covering 'A', then 'B', working its way up to 'Z'.
    *   Instead of printing to a console (`printf`), it uses `gtk_text_buffer_insert_at_cursor` to write the word and a newline directly into the GUI's text display.

---

### C. The Graphical User Interface (GUI) Callbacks

In GTK+, when a user clicks a button, a "signal" triggers a "callback function". 

#### 1. `on_insert_clicked`
*   **Trigger:** User clicks the "Insert" button.
*   **Logic:** 
    1. Grabs the text typed into the `entry` (text box).
    2. Checks if the user actually typed something (`strlen > 0`).
    3. Calls the backend `insert()` function, updating the global `root` of the tree.
    4. Updates the text buffer to display a success message ("Word inserted.").

#### 2. `on_search_clicked`
*   **Trigger:** User clicks the "Search" button.
*   **Logic:**
    1. Grabs the text from the `entry` box.
    2. Passes the word to the backend `search()` function.
    3. If `search()` returns `1`, prints `"Word found."`. Otherwise, prints `"Word not found."`.

#### 3. `on_display_clicked`
*   **Trigger:** User clicks the "Display Dictionary" button.
*   **Logic:**
    1. Clears the current text screen (`gtk_text_buffer_set_text(text_buffer, "", -1)`).
    2. Calls the backend `inorder()` function, which systematically fills the text screen with all saved words in A-Z order.

---

## 4. Main Function (`main()`)

The `main` function is exclusively responsible for painting the application window and assembling the UI blocks .

*   **Initialization (`gtk_init`):** Bootstraps the GTK windowing environment.
*   **Window Creation:** Generates a 400x300 pixel window titled "Word Dictionary (BST)".
*   **Vertical Box (`vbox`):** A container layout that stacks elements on top of each other vertically.
*   **Widgets:** Creates the input field (`gtk_entry_new`), three buttons (`gtk_button_new_with_label`), and a large text viewing area for displaying results (`gtk_text_view_new`).
*   **Signal Connections:** Hooks up the physical mouse clicks to the C logic (e.g., binds the Insert button to `on_insert_clicked`).
*   **Event Loop (`gtk_main`):** This command freezes the console application from exiting, instead letting it sit idly waiting for the user to interact with the visual interface.

---

## Slide Ideas for your PPT Presentation

If you are using this README to build a PowerPoint, here is a suggested flow:

1.  **Title Slide:** Word Dictionary Application Implementation.
2.  **Introduction:** Overcoming traditional array limitations with dynamic memory and non-linear data structures.
3.  **Concept - The BST:** Visual diagram of a Binary Search Tree. Explaining Left (<) vs Right (>). Explain O(log n) time complexity.
4.  **Backend - Insertion Logic:** How words find their place. Mention recursion.
5.  **Backend - Search Logic:** Tracing down the tree to look for matches.
6.  **Backend - In-order Traversal:** The trick to getting A-Z alphabetical sorting automatically.
7.  **Frontend - GTK+ Integration:** Showing screenshots of the GUI. Explaining event-driven programming (Signals & Callbacks).
8.  **Architecture:** A visual representation showing the GUI Text Box -> Button Click (Signal) -> Update the core C `struct Node` tree.
9.  **Conclusion:** Summarization of how algorithms visually interact with user interfaces in C.
