import random
import sys
from collections import deque

# Set the grid size (must be odd for maze generation)
grid_size = 32  # Changed from 32 to 31 for maze generation

# Create an empty grid filled with walls (`#`)
grid = [['#' for _ in range(grid_size)] for _ in range(grid_size)]

def generate_maze(grid, grid_size):
    """
    Generates a maze within the grid using the Recursive Backtracker algorithm.
    Walls are represented by '#', and paths by '.'.
    """
    def is_valid(cell):
        x, y = cell
        return 0 <= x < grid_size and 0 <= y < grid_size

    def get_neighbors(cell):
        x, y = cell
        directions = [(-2, 0), (2, 0), (0, -2), (0, 2)]
        neighbors = []
        for dx, dy in directions:
            nx, ny = x + dx, y + dy
            if is_valid((nx, ny)) and grid[nx][ny] == '#':
                neighbors.append((nx, ny))
        return neighbors

    def carve_passages_from(cx, cy):
        grid[cx][cy] = '.'  # Mark the current cell as a path
        neighbors = get_neighbors((cx, cy))
        random.shuffle(neighbors)
        for nx, ny in neighbors:
            if grid[nx][ny] == '#':
                wall_x, wall_y = cx + (nx - cx) // 2, cy + (ny - cy) // 2
                grid[wall_x][wall_y] = '.'  # Remove the wall between
                carve_passages_from(nx, ny)

    # Start maze generation from a random odd cell
    start_x, start_y = random.choice(range(1, grid_size, 2)), random.choice(range(1, grid_size, 2))
    carve_passages_from(start_x, start_y)

def add_random_letters(grid, grid_size, num_letters=100):
    """
    Adds a specified number of random letters ('C', 'c', 'd', 'B') to random path positions in the grid.
    Ensures that letters are placed only on paths ('.').
    """
    letters = ["C", "c", "d", "B"]
    added = 0
    attempts = 0
    max_attempts = num_letters * 10  # Prevent infinite loop

    while added < num_letters and attempts < max_attempts:
        x, y = random.randint(1, grid_size - 2), random.randint(1, grid_size - 2)
        if grid[x][y] == '.':
            grid[x][y] = random.choice(letters)
            added += 1
        attempts += 1

    if added < num_letters:
        print(f"Warning: Only added {added} letters out of {num_letters} requested.", file=sys.stderr)

def print_grid(grid, grid_size):
    """
    Prints the grid to the console.
    """
    for row in grid:
        print(''.join(row))

def save_grid_to_file(grid, grid_size, filename="testEventMap3.txt"):
    """
    Saves the grid to a specified filename.
    """
    try:
        with open(filename, 'w', encoding='utf-8') as f:
            for row in grid:
                f.write(''.join(row) + '\n')
        print(f"Map successfully saved to {filename}.")
    except IOError as e:
        print(f"Error saving map to {filename}: {e}", file=sys.stderr)

if __name__ == "__main__":
    # Generate the maze
    generate_maze(grid, grid_size)

    # Add random letters to the maze
    num_letters = 100  # Change this as needed
    add_random_letters(grid, grid_size, num_letters)

    # Print the grid to the console
    print_grid(grid, grid_size)

    # Save the grid to a file
    save_grid_to_file(grid, grid_size, "testEventMap3.txt")