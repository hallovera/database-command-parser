# Database Command Parser
A C++ command parser to interact with a simple linked list-based database. The database is implemented using linked lists, and is currently used to store "Shape" objects.

## Available commands

### shape
Creates a new shape ```name```, with type ```type```, cartesian x-location ```xloc``` and y-location ```yloc```, and x-length ```xsize``` and y-length ```ysize```.  
**Syntax**: ```shape name type xloc yloc xsize ysize```  
**Output**:  ```name: type xloc yloc xsize ysize```. Shape will be created and placed in the main group ```pool```.  

### group
Creates a new group ```name```, used to organize and store shapes. The default group (where new shapes are placed) is called ```pool```.  
**Syntax**: ```group name```    
**Output**: ```name: group```. A group with name ```name``` will be created.  

### draw
Lists the properties of all shapes in the database. (Actual drawing not implemented)  
**Syntax**: ```draw```  
**Output**:  ``` drawing:``` followed by a list of all shapes in the database and their properties. The shapes are not actually drawn.

### move
Move shape from one group ```name1``` to another ```name2```.  
**Syntax**: ```move name1 name2```  
**Output**: ```Moved name1 to name2```. The shape will be moved from group ```name1``` to group ```name2```.

### delete
Deletes a shape or group ```name```.  
**Syntax**: ```delete name```  
**Output**: ```name: deleted```. The shape or group ```name``` will be deleted from the database.  

## Parameters
```name```: A string for the shape/group name. Cannot be a reserved word (```pool```, ```ellipse```, ```rectangle```, ```triangle```, or any command name).  
```type```: The type of the shape. Can be ```ellipse```, ```rectangle``` or ```triangle```.  
```xloc``` and ```yloc```: Cartesian x and y position of the shape. Must be positive integers or zero.  
```xsize``` and ```ysize```: The size of the shape in the x and y directions. Must be positive integers or zero.

