# CS225 Final Project Results


 In this project, our team uses the Open Flight dataset to construct an undirected weighted graph, and successfully implemented the following algorithms: 
 Breadth First Search Traversal(BFS), Delta-Stepping Single Source Shortest Path(SSSP), and Force-Directed Graph. 

 We started by setting up the basic structure of the graph. In the Vertex class, airports are stored as vertices with their IDs, latitudes, and longitudes. Whereas in Edge class, the routes between airports are stored with their distances, which are great-circle distances between two points on Earth that are calculated by the Haversine formula. With Vertex and Edge classes established, we then started building the structure of our Graph class.

Main functions in Graph class are applied: insertVertex, insertEdge, incidentEdges, areAdjacent, BFS, and SSSP.  

In test cases Test_ADJ_Graph1 and Test_IncidentEdge_Graph1, functions insertVertex, insertEdge, incidentEdges, and areAdjacent were tested and they all worked as intended. We also included Test_DuplicatedEdge_Graph1 to test whether we save duplicated edges on our graph which we shouldn't.


# BFS
The primary function that BFS should be accounted for should be that all vertices on the graph are successfully traversed, no matter the graph is connected or disconnected. From file ./result/BFS.txt, one can also find the BFS traversal output of all airports, including the total number of the airport that has been traversed and a sequence of airports represented by their IDs. The run time of BFS is O(n).
   
"Test_BFS_Disconnected_Graph":

<img width="510" alt="Screen Shot 2021-12-08 at 12 18 10 AM" src="https://media.github-dev.cs.illinois.edu/user/12066/files/5d09eaf2-136a-4fbf-94c1-ebbcad6d4227">

"Test_SSSP_Simple_Graph1": 

<img width="520" alt="Screen Shot 2021-12-08 at 12 18 22 AM" src="https://media.github-dev.cs.illinois.edu/user/12066/files/a7b31595-f04c-49a4-9bac-e13353d1ae9d">

./result/BFS.txt
![image](https://media.github-dev.cs.illinois.edu/user/9738/files/1af5944b-835e-4f9e-a3b8-2c1aec9ad10e)
   


# SSSP
For the shortest path, we used Delta-Stepping SSSP which could find the shortest path and the minimum distance between any two vertices. 

Similar to BFS, we had done the test both on connected and disconnected graphs. Test_SSSP_Simple_Graph1 tests on the shortest path and minimum distance between two adjacent vertices; Test_SSSP_S2S_Graph1 verifies that the shortest path from a vertex to itself should have zero distance; Test_SSSP_Complicated_Graph1 checks that the shortest path and distance between two non-adjacent vertices outputted correctly; and Test_SSSP_Disconnected_Graph1 testifies that the shortest path of a 
<<<<<<< HEAD
disconnected vertex returns just itself, and its distance is infinity. 
Finally, file ./result/SSSP.txt provides the shortest path between two airports given by user and their corresponding minimum distance. The run time of our Dealta-Stepping SSSP is roughly O(n+m).

=======
disconnected vertex returns just itself, and its distance is infinity. In Earth class, we successfully visualized all airports around the world and drew the shortest path between two airports inputted by users. 
Finally, file ./result/SSSP.txt provides the shortest path between two airports given by user and their corresponding minimum distance. The run time of our Dealta-Stepping SSSP is roughly O(n+m).


>>>>>>> 5ac016328d6cb86ec18e02a2d5199e9881657585
code from "Test_SSSP_Simple_Graph1":

<img width="600" alt="Screen Shot 2021-12-08 at 2 50 38 PM" src="https://media.github-dev.cs.illinois.edu/user/12066/files/4eabe8c0-02af-4cfd-a646-ab070635325a">

code from "Test_SSSP_S2S_Graph1":

<img width="600" alt="Screen Shot 2021-12-08 at 2 51 48 PM" src="https://media.github-dev.cs.illinois.edu/user/12066/files/a4598068-a246-47da-83cc-7eb7252011d0">

code from "Test_SSSP_Complicated_Graph1":

<img width="600" alt="Screen Shot 2021-12-08 at 2 52 04 PM" src="https://media.github-dev.cs.illinois.edu/user/12066/files/5fbb26c6-93c2-4395-9b44-1db8f2add03c">

code from "Test_SSSP_Disconnected_Graph1":

<img width="600" alt="Screen Shot 2021-12-08 at 2 52 18 PM" src="https://media.github-dev.cs.illinois.edu/user/12066/files/ec4e3473-b998-4774-8d87-92665524f5e5">

./result/SSSP.txt

![image](https://media.github-dev.cs.illinois.edu/user/9738/files/a812c23c-eb72-483b-98e3-92eb7a3b1173)
<<<<<<< HEAD
=======

visualization of shortest path bewteen two airports:
![SSSP visualizationChampaign_Hangzhou](https://media.github-dev.cs.illinois.edu/user/12066/files/fd63fb6e-0b6f-4e68-87ae-2554d8bd663a)
>>>>>>> 5ac016328d6cb86ec18e02a2d5199e9881657585


# Force-Directed Graph
To visualize our Graph, we create Layout class and performed Force-Directed Graph algorithm to draw the location of airports and the flight routes. By assigning forces among vertices and edges, the Force-Directed Graph helps draw the edges with similar lengths and possibly reduce cross edges. As shown by our output graph below, vertices with a greater radius indicate larger airports. The colors depict the size of the airports as well; they are colored as purple, red, orange, blue, cyan, and green, order from greatest to smallest. For instance, the big purple vertices represent the largest airports and the small green vertices represent the smallest airports. Furthermore, the brown vertex is the source vertex, and the graph draws the other ninety-nine airports with least number of connecting flights (since we only draws 100 airports for the sake of run time). The run time of Force-Directed Graph is roughly O(m * n^2).

ForceDirectedGraph_Output.png
![ForceDirectedGraph_OutputAt9](https://media.github-dev.cs.illinois.edu/user/12066/files/03536507-6ab7-483e-b82b-75f6829d4bb1)
![ForceDirectedGraph_OutputAt298](https://media.github-dev.cs.illinois.edu/user/12066/files/260ad858-c8c9-44bd-9bed-504af3562ae4)
![ForceDirectedGraph_OutputAt3400](https://media.github-dev.cs.illinois.edu/user/12066/files/aff842eb-e5e8-4c15-b006-353a4bbe956c)
![ForceDirectedGraph_OutputAt3448](https://media.github-dev.cs.illinois.edu/user/12066/files/1cd642d4-2743-4c27-97f1-742c811a3934)


# Final Thoughts
An interesting disovery that we found from Force-Directed Graph is that if we could draw out all the airports, we would find small clusters of airports away from the center that has only one to two airports connecting to the core airports. Hence, our graph can be improved in order to draw out all the airports and their flight routes. Another improvement can be done on Delta-Stepping SSSP algorithm. Our current delta size is 10 and the number of buckets is 15000. However, we could find the best optimized delta size and number of buckets to run our program more efficiently.
