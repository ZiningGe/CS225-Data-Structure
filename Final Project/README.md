# Final Project - Open Flights

  Group Name: REMS
  
  Group Members: Simon Ge, Rubin Zou, Mazer Xu, Erin Wang
  
  
  
# Introduction
  This project uses the Open Flight dataset to construct an undirected weighted graph, and offers three algorithms:
  
  - BFS traversal to traverse all airports
  - Delta-stepping SSSP to find the shortest path between two airports given by user, and the corresponding distance
  - Force-directed graph to visualize location of airports in a clearer and more straight-forward way



# Code Organization
  Major Code: 
  
    - main.cpp: The main function to call BFS, delta-stepping SSSP, and force-directed graph
    
    - graph.cpp graph.h: The basic undirected weighted graph data structure, BFS, and SSSP functions
    
    - Vertex.cpp Vertex.h: The vertex class and corresponding functions
    
    - Edge.cpp Edge.h: The edge class and corresponding functions
    
    - fileio.cpp fileio.h: Read the input txt files and convert them into corresponding data type
    
    - Layout.cpp Layout.h: Construction and visualization of force-directed graph
    
    - Earth.cpp Earth.h : Visualization of shortest path from SSSP
    
    - cs225/* : files to draw graph and output PNG
    
    - test/* : test files

  Data:
  
    - airport.txt: The input data for each airport. [airport ID] [longitude] [latitude]
    
    - routes.txt: The input data for each route. [source airport] [destination airport]
    
  Results:
  
    - ./result/BFS.txt: Output file for BFS traversal
    
    - ./result/SSSP.txt: Output file for SSSP
    
# How to use our program

  To download our program, please copy and paste this line to your terminal:
  
    git clone https://github-dev.cs.illinois.edu/cs225-fa21/mingzex2-yiranw8-ziningg2-jiaruz2.git
    
  To build our program, please run:
  
    make
    
  The executable created is called mosaics. You can run it as follows:
  
    ./main [input_airport_file] [input_routes_file] [output_dir] [delta] [number_of_buckets] [source_ID] [des_ID]
    
  [input_airport_file]: The input airport file in format as mentioned
  
  [input_routes_file]: The input route file in format as mentioned
  
  [output_dir]: The output folder where BFS.txt and SSSP.txt are located, the recomended output dir is ./test/
  
  [delta]: The parameter for delta-stepping SSSP, 10 is recomended
  
  [number_of_buckets]: The parameter for delta-stepping SSSP, 15000 is recomended
  
  [source_ID]: The ID of the souce airport
  
  [des_ID]: The ID of the destination airport
  
  # How to interprete our result
   ./result/BFS.txt: 
   
   This is the output file for BFS traversal, including the total number of airport that has been traversed, and a sequence of airports
   
   
   ![image](https://media.github-dev.cs.illinois.edu/user/9738/files/1af5944b-835e-4f9e-a3b8-2c1aec9ad10e)
   
   ./result/SSSP.txt
   
   This is the output file for SSSP, including the shortest path between two airports given by user, and the corresponding distance
   
   
   ![image](https://media.github-dev.cs.illinois.edu/user/9738/files/a812c23c-eb72-483b-98e3-92eb7a3b1173)
   
   # How to test our program
   
   We have provide some test cases to test the functionality of our program. You can compile the unit tests with the following command:
   
    make test
    
   This will create an executable named test which you can execute with the following command to run tests:
   
    ./test
   
   Summary:

- "Test_ADJ_Graph1": tests whether any two vertices on the graph are adjacent.

- "Test_IncidentEdge_Graph1": tests all the adjacent edges of a certain vertex while checking the distance of each edge.

- "Test_DuplicatedEdge_Graph1": tests whether we save duplicated edges on our graph which we shouldn't.

- "Test_BFS_Graph1": tests Breath First Traversal on a connected graph.

- "Test_BFS_Disconnected_Graph": tests Breath First Traversal on a disconnected graph; should have all vertex traversed.

- "Test_SSSP_Graph1": tests the shortest path and the minimum distance between any two vertices on a connected graph.

- "Test_SSSP_Disconnected_Graph1": tests the shortest path and the minimum distance between any two vertices that belong to different connected components; should have infinite distance.

- "Test_SSSP_S2S_Graph1": tests the shortest path from source to source airport

- "Test_SSSP_Complicated_Graph1": tests the shortest path on a complicated graph

@yiranw8
   


    
    
    
    
