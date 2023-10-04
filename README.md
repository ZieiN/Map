# Map

Sometimes you want to declare a dynamic 2d array. If you declare it as *`int **`* or *`vector<vector<int>>`* then you may lose the feature of fast access to elements (as the elements are not stored in one line in memory, and therefore not the whole array is copied to cache each time). If you declare it as one array *`int *`*, then you need some helper function to access the elements in convinent way as *`get`* by *`(x,y)`*, or check whether some indecis are inside the map.

Here is a **Map** class to help you do this.

It is planned to provide it with some helper functions. 

Currently provided functions:
* Function *`isThereLineOfSite(x0,y0,x1,y1)`* to check if an obstacle exists along a line segment. It implements fast and precise *Amanatides and Woo* algorithm (*Fast Voxel Traversal* Algorithm). The function considers the following: if the line touches (or near by value *eps*-inside the code) the edges of a cell, then it consider the cell is located on the line. See `res.pdf` for an example. You can also use `main.cpp` to generate the cells along a specific line, and use `python3 draw.py` to draw them.