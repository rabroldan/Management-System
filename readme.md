**Project Overview:**

The project involves the creation of an assembly line system with distinct workstations, each equipped with specific stock items. The workflow is overseen by a line manager who guides customer orders through the line, ensuring completion at each station. The project is organized into three milestones, with a focus on different modules.

**Utilities and Station Classes Module:**

*Utilities Module:*
- Parse input files into tokens using the Utilities class.
- Define `setFieldWidth`, `getFieldWidth`, and `extractToken` functions.
- Use a common delimiter for all Utilities objects.

*Station Module:*
- Implement the Station class to manage information about a station.
- Create a custom 1-argument constructor, getters, and modifiers.
- Display station information based on specified conditions.

*CustomerOrder Module:*
- Manage single orders on the assembly line.
- Implement a structure Item within the CustomerOrder class.
- Define a custom constructor, destructor, and display function.
- Prevent copy operations and use move semantics.

**Workstation and LineManager Modules:**

*Workstation Module:*
- Define the Workstation class as an active station on the assembly line.
- Manage order processing for a single item.
- Implement `fill`, `attemptToMoveOrder`, `setNextStation`, and `display` functions.

*LineManager Module:*
- Manage an assembly line of active stations.
- Configure workstations and move orders along the line.
- Implement the LineManager class with functions like `reorderStations`, `run`, and `display`.