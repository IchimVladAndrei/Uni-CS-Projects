# 💻 Assignment 08
## Requirements
- Provide a menu-driven console-based user interface. Implementation details are up to you
- Employ layered architecture and classes
- Have at least 20 procedurally generated items in your application at startup
- Provide specifications and **PyUnit test cases** for all non-UI classes and methods for the first functionality
- Implement and use your own exception classes.
- Deadline is **week 12**, with the exception of the undo-redo bonus.

## Bonus possibility (0.1p, deadline week 12)
- 95% unit test code coverage for all modules except the UI (use *PyCharm Professional*, the *[coverage](https://coverage.readthedocs.io/en/coverage-5.3/)* or other modules)

## Bonus possibility (0.2p, deadline week 12)
- Implement a graphical user interface, in addition to the required menu-driven UI
- The program can be started with either UI

## Bonus possibility (0.2p, deadline week 14)
- Unlimited undo/redo functionality. Each step will undo/redo the previous operation performed by the user. Undo/redo operations must cascade and have a memory-efficient implementation (no superfluous list copying) based on the [command design pattern](https://refactoring.guru/design-patterns/command)

## Problem Statements

### 3. Movie Rental
Write an application for movie rentals. The application will store:
- **Movie**: `movie_id`, `title`, `description`, `genre`
- **Client**: `client_id`, `name`
- **Rental**: `rental_id`, `movie_id`, `client_id`, `rented_date`, `due_date`, `returned_date`

Create an application which allows to:
1. Manage clients and movies. The user can add, remove, update, and list both clients and movies.
2. Rent or return a movie. A client can rent a movie until a given date, as long as they have no rented movies that passed their due date for return. A client can return a rented movie at any time.
3. Search for clients or movies using any one of their fields (e.g. movies can be searched for using id, title, description or genre). The search must work using case-insensitive, partial string matching, and must return all matching items.
4. Create statistics:
    - Most rented movies. This will provide the list of movies, sorted in descending order of the number of days they were rented.
    - Most active clients. This will provide the list of clients, sorted in descending order of the number of movie rental days they have (e.g. having 2 rented movies for 3 days each counts as 2 x 3 = 6 days).
    - Late rentals. All the movies that are currently rented, for which the due date for return has passed, sorted in descending order of the number of days of delay.

### 4. Library
