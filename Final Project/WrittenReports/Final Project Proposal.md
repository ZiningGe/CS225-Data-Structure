**CS225 Final Project Proposal**


**Leading Question:**

We are using OpenFlight datasets. From this final project, we are planning to learn from the airport locations (by latitude and longitude) and the possible airline routes to find the ideal shortest path between any two airports. Furthermore, we hope to produce a general search tool to allocate the start airport and the destination, from where we start collecting routes related to those two airports. We define a ‘successful’ project as a graph drawn with all possible routes within the areas between the two airports while having the shortest path visualized.

**Dataset Acquisition and Processing:**

We will apply two datasets about worldwide airports and flight routes on OpenFlights (https://openflights.org/data.html). An adjacent graph data structure will be implemented. In the airports dataset, each airport’s unique numerical ID and its coordinates will be obtained for identification and location. This set of information will be stored as vertices. From the second dataset, we will collect routes as edges. The vertex of the source airport and the vertex of the destination airport will be connected by the corresponding edge, and a calculated distance will be stored in that edge. Our implementation will neglect the altitudes of airports, and the distance between two airports will be calculated based on the Euclidean distance between the coordinates of the two airports. Some airports or routes could have missing information. If we encounter errors with missing data, we will manually complete the dataset by searching the corresponding airport.

**Graph Algorithms:**

We will implement BFS, Delta-stepping SSSP, Force-directed graph drawing to find the shortest path between any two airports. Based on our graph data structure, the location in terms of longitude and latitude, and a unique ID is stored in each vertex, and distance between two airports are stored in corresponding edges. In our traversal algorithm, we will input the graph, and return an array of vertice (airports) of traversal to verify our graph with run time of O(n). Given the pointer to source and destination vertice using the search algorithm, we will feed them into the Delta-stepping SSSP algorithm, and will return an array of vertice that constitute the shortest path, and the shortest distance. The run time of the Delta-stepping SSSP would be O(d^2Llog^2(n)), where d denotes the maximum degree of the graph and L denotes the maximum shortest path weight. The force-directed graph will visualize the shortest distances among airports. The input will be weighted edges with distances. The run time of the force-directed graph is O(n^3), where n is the number of nodes of the input graph.

**Timeline:**

11.8 - 11.14 

— Searching available Data set      
— Data acquisition, processing, and cleaning   
— Contacting mentors for accessibility of the final project

11.15 - 11.28 

— Building basic graph structure for datasets   	     
— Completing each individual algorithm, 
Including:BFS TraversalDelta-stepping SSSP Force-directed graph drawing

11.29 - 12.1 

— Mid-Project Checking with mentors

11.29 - 12.07 

— Development of test cases
— Starting on Final Project Deliverables		     
— Completion of functional code-base

12.08 - 12.11 

— Finishing up written report and PowerPoint for presentation
