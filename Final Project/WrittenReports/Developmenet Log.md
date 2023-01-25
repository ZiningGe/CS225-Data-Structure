Week One 11.07 - 11.13

For the first week, our team firstly looked through all of the information of CS225 final projects including grading rubrics and project requirements. Then, through brainstorming on the first meeting, we decided to focus on the area of shortest path of airports with its usualization. Then, we followed the instruction in course website to complete the project proposals and set time schedules for each group member. In addition, we started to look through the website to search for the proper datasets and finally found two datasets: one is the flight route for each airport, the other is the specific location for each air station. We downloaded the datasets from the website and used the data cleaning method in Excel to clean the dirty data and refresh the data suitable for our future use. 
*The data set is found here*: https://openflights.org/data.html

Week Two 11.14 - 11.20

For the second week, we kept focusing on processing the data related to the flight and also started to build the basic data structure for the graph. Firstly, we created two pair vectors representing the value in two datasets in the main function: distance and coordinate. Then we write the I/O in c++ to transfer the data from txt format into the format of vector, so that we can use this collected data for building our graph. Additionally, to build the basic graph, we created three classes - vertex, graph, and edge. Each class includes the basic variables and functions to implement the graph. 

Week Three 11.21 - 11.27

For the third week, we kept improving and finalizing graph structure. Also, our team members start to search and learn the algorithm of delta-stepping through wiki and other academic websites. 
The reference website is here: https://en.m.wikipedia.org/wiki/Parallel_single-source_shortest_path_algorithm
We also found a graphic tool for us to virtualize such algorithm, which is here:https://cs.iupui.edu/~fgsong/LearnHPC/sssp/deltaStep.html

Week Four 11.29 - 12.4

For the fourth week, we finalized graph structure and finished delta stepping SSSP and BFS in the graph class. Furthermore, we added test folder, debugged every single function in the graph class, finished makefile, and updated main.cpp so that we can adjust input data in one command line. Finally, we added cs225 directory for its PNG and pixel files. We are almost done Force Directed Layout, except the output function. We will be working on the output function and debugging Force Directed Layout in the next two days.

Week Five 12.5 - 12.11

In the last week, we finished Force Directed Layout. However, we realized that in order to fulfill our leading question in the proposal, we had to implement another visualization that could demonstrate the shortest path between any two airports. Hence, we added and finished Earth class. Finally, we integrated all our results in "result" folder, finished written reports, and recorded final presentation for this project. 
