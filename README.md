# Sorting Algorithm Visualization Program

## 1. Introduction
### 1.1 Background and Significance
After mastering basic C programming concepts and learning about sorting algorithms, we've advanced to understand graphical programming this semester. With the ability to create simple animations and graphical representations, our teacher assigned us a significant project: to develop a program showcasing sorting algorithms. Among the options, we chose "Sorting Algorithm Visualization" due to its relative simplicity. The aim is to elucidate sorting principles dynamically, making it accessible even to beginners without programming experience. Moreover, it can serve as a practical tool for sorting tasks when necessary.

### 1.2 Objectives
The main objectives of our program include implementing three sorting algorithms: Bubble Sort, Selection Sort, and Merge Sort. We aim not only to visualize these algorithms dynamically but also to enable automatic and step-by-step execution, data input from files, support for process saving and retrieval, and real-time addition, deletion, and modification of data for new sorting.

### 1.3 Glossary
- **libgraphics:** Library for graphics operations.
- **simpleGUI:** A simple graphical user interface library.
- **Head Files:** Customized headers containing necessary declarations and definitions for our program.
- **Global Variables:** Variables accessible and modifiable across the entire program for ease of programming.

## 2. Requirements Analysis
### 2.1 Business Requirements
The program is primarily designed for educational purposes, aiming to demonstrate the principles of Bubble Sort, Selection Sort, and Merge Sort, primarily for teachers in information technology courses.

### 2.2 Functional Requirements
- Dynamic visualization of sorting algorithms.
- Support for integer, float, and double data types.
- Data input from files in a specific format.
- Process saving and retrieval.
- Real-time addition, deletion, and modification of data.

### 2.3 Data Requirements
The data for sorting must be numerical and should support integer, float, and double data types. It should be readable from files in a specific format, and the program should support process saving and retrieval.

## 3. Program Development Design
### 3.1 Overall Architecture
Our program consists of modules for data management, sorting algorithms, and process handling. It relies on graphical libraries and custom functions to ensure smooth operation.

### 3.2 Functional Module Design
- **Data Module:** Responsible for generating, inserting, deleting, clearing, opening, and importing data.
- **Sorting Module:** Includes Bubble Sort, Selection Sort, and Merge Sort algorithms.
- **Process Handling Module:** Manages snapshot generation and restoration.

### 3.3 Data Structure Design
Arrays primarily serve as the data structure for our program, facilitating efficient data handling and manipulation.

### 3.4 Source Code File Organization Design
The program includes several files, each serving distinct purposes:
- `main.c`: Entry point and main program logic.
- `main.h`, `our_data.c`, `our_data.h`, `our_histogram.c`, `our_histogram.h`, `our_option.c`, `our_option.h`: Customized files containing functions for various operations and interfaces.

## 4. Function Design Description
### `main.c`:
The `display()` function orchestrates various sub-functions to present the main program interface.

### `our_data.c`:
1. **Save Data Function:** Generates a binary snapshot file.
2. **Restore Data Function:** Restores data from a binary snapshot file.
3. **Import Data Function:** Imports data from a text file.

### `our_histogram.c`:
1. **Initialization Function:** Initializes the sorting interface.
2. **Draw Mask Function:** Masks the interface during sorting.
3. **Move Histogram Function:** Moves the histogram during dynamic sorting.
4. **Set Location Function:** Sets the positions of elements in the histogram.
5. **Add Data Button Function:** Adds buttons for data manipulation.
6. **Max Value Function:** Computes the maximum value from data.

### `our_option.c`:
1. **Restart Function:** Restarts the sorting process.
2. **Menu Function:** Displays the data import/export menu.
3. **Button Function:** Draws and implements various buttons.
4. **Stepwise Bubble Function:** Executes Bubble Sort step by step.
5. **Stepwise Selection Function:** Executes Selection Sort step by step.
6. **Stepwise Merge Function:** Executes Merge Sort step by step.

The program architecture is designed for clear organization and ease of modification, ensuring smooth execution and maintenance.

## 4. Deployment, Execution, and Usage Instructions

### 4.1 Compilation and Installation
As mentioned above, after extracting the compressed package, navigate to the folder, open the `tutorialsDevC` directory, then the `0-emptywindow` folder, and finally open the `step0.dev` project file. Select a compiler suitable for your computer configuration, choose "Run" -> "Recompile All," and after compilation is complete, select "Run" to execute the program successfully.

### 4.2 Running Tests
Upon running the program, the following interface should appear, indicating that the program has started successfully. Test each program functionality, and if all functions properly, the program is correct.

### 4.3 Usage Instructions
Upon opening the executable file, the data editing interface appears.

By default, 20 random numbers are generated, and a histogram is generated accordingly. Starting from the top-left corner, the first functionality is to generate a specified number of random numbers, where you can input the data amount and generate it with a single click. The second function is to add new specified data to the end of the histogram. Input the data, and it will be added. The third function is to delete specified data. Currently, two different deletion methods are implemented: you can input the data value to delete specific data, or you can input the position to delete data at a specific location.

Next, let's introduce the top-right corner. In the menu bar, the "Generate Snapshot" function temporarily saves the current data, allowing quick data recovery after restarting the program through the "Restore Snapshot" function. The "Export Data" function opens a specified txt file and writes the data type and all data values into it. The "Import Data" function allows data import based on this txt file. The "Clear" button in the top-right corner clears all data with a single click, while the "Sort" button adds a dynamic sorting display interface.

Upon entering the dynamic sorting display interface, data cannot be modified, only sorted. We have implemented three sorting methods: Bubble Sort, Selection Sort, and Merge Sort. Each sorting method has single-step execution, automatic execution, and full execution functions. Single-step execution performs one dynamic sorting operation; automatic execution performs all dynamic sorting operations automatically; Merge Sort completes all sorting at once and displays the final result. During dynamic sorting, the interface displays "Sorting" and prohibits operations, which can be exited by the cancel button. After sorting, a "Sorting Completed" prompt is displayed. In this interface, you can return to the data editing interface at any time through the "Exit Sorting" button, and the current data will be preserved.

## 5. Team Collaboration

### 5.1 Task Division
We divided tasks based on functions and corresponding functionalities.

- **Yiyang Liu**: Responsible for implementing Bubble Sort, data editing functionality, and specific implementations of sorting buttons and responses, as well as histogram drawing functionality.
- **Chuang Wu**: Responsible for implementing Merge Sort, program parameter settings, and debugging.
- **Renxiang Zhang**: Responsible for implementing Selection Sort, batch data import functionality, and specific implementations of binary file import/export functionality.

In actual writing, some tasks were completed collaboratively by multiple team members, rather than independently.

### 5.2 Development Plan
We formulated a development plan during our first discussion. The development plan is as follows:
- April 16: Project initiation.
- April 17: Preparation and knowledge review writing.
- May 8: After multiple discussions, the topic is finally determined.
- May 14: Unified offline meeting, discussion on task allocation and function tables; end of knowledge preparation phase, start of programming phase 1.
- May 19: Main program and all function files are set up, synchronizing progress of phase 1.
- May 20: Unified online meeting, standardized the global variables used in writing.
- May 21: Unified offline meeting, followed by another unified online meeting later in the day, focusing on tackling the high-difficulty points of phase 1 collectively.
- May 27: Phase 1 compilation passes, simulated operation meets functional requirements, start writing phase 2.
- May 28: Unified offline meeting, determining phase 2 writing tasks and specific deadlines.
- May 29: Program code optimization, resolution of some known bugs.
- June 2: Program code continues optimization, resolution of some known bugs.
- June 6: Unified offline meeting, collective discussion on the key points of phase 2 programming, reassignment of tasks.
- June 11: All code writing is completed and compiled, simulated operation meets functional requirements.

### 5.3 Coding Standards
We adopted unified C language programming standards.

### 5.4 Collaboration Summary
- April 21, 2021: Determination of files, functions, global variables, task division, start of sorting function writing.
- May 15, 2021: Second discussion; misunderstanding of variables discovered; leader explanation; members revised the program.
- June 1, 2021: Third discussion; collective tackling of merge function.
- June 14, 2021: Presentation, PPT video recording.

### 5.5 Reflections
#### Chuang Wu:
Throughout the collaboration on this large program, I realized the challenges and importance of teamwork. Initially, there might be communication issues among team members, but when encountering a problem one cannot solve alone, three minds together might solve it. During the process, I gained a clearer understanding of my learning situation this semester, identified many knowledge blind spots, and realized my limitations. I also learned that practice leads to true understanding. Many theoretical concepts in class need practical application to be truly mastered. In this project, my contribution was minimal due to my limited knowledge. I appreciate the support from my team members, especially the team leader, who devoted a lot of effort not only to complete his tasks but also to help us afterward. Thanks to all team members' efforts, we achieved success in this project.

#### Yiyang Liu:
"Theory without practice is as pale as a paper." There's a significant gap between textbook knowledge and practical application. Although I have a certain foundation in C language programming, introducing a new library posed a challenge for me. Time for programming is limited, and it's necessary to quickly familiarize oneself with the functions in the library. I used two methods: reading open-source original functions, which provides comprehensive knowledge but might lead to information overload, and studying existing examples, which offers quick understanding of important functions but with limitations. During this project, I quickly learned how to use a function by watching examples. However, when the knowledge gained from examples became limited, I revisited the original functions for targeted knowledge. This project broadened my computer thinking, enhanced my teamwork and communication skills, and brought many gains!

#### Renxiang Zhang:
First, I would like to thank my teammates Chuang Wu and Yiyang Liu for their help and support. During the entire process of writing the program, many tasks needed to be integrated with others, and sometimes, if the integration wasn't smooth, it hindered progress. However, after multiple communications within the team, this issue improved, and we successfully completed the project. Chuang Wu tried his best in writing his part, often discussing within the team, and finally completed his task successfully. Yiyang Liu, as the team leader, not only undertook a large part of the tasks and built the main framework of the program
