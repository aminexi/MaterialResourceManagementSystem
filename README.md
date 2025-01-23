# Material Resource Management System

## Overview
The Material Resource Management System is designed to help organizations efficiently manage their material inventory, track material requests, perform repairs and maintenance, and ensure the optimal use of available resources. It offers a set of features that allow users to manage materials, requests, users, and stock levels in an efficient and scalable way.

## Features
- **Material Management**: Add, modify, delete, and search materials.
- **User Management**: Create users, assign departments, and configure access rights.
- **Inventory Management**: Display the complete inventory or by department.
- **Material Request Management**: Track pending requests and add new ones.
- **Repairs and Maintenance Management**: Record maintenance interventions.
- **Stock Management**: Monitor stock levels and critical stock notifications.

## Design
The system uses object-oriented programming with the following core classes:
- **Material**: Represents a material with name, reference, type, and quantity.
- **Department**: Represents a department with a list of materials.
- **User**: Represents a user with name, identifier, department, and access rights.
- **Request**: Represents a material request with user info, description, and priority.
- **Maintenance**: Represents a maintenance intervention with description and date.
- **StockMaterial**: Inherits from Material and adds the `thresholdCritical` attribute to manage stock levels.

## Technologies Used
- **Language**: C++
- **Programming Paradigm**: Object-Oriented Programming (OOP)
